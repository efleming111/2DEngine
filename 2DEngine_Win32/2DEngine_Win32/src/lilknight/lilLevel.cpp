//
//  lil Knight
//  lilLevel.cpp
//  Eric Fleming
//  5/21/2018
//

#include "lilLevel.h"
#include "../engine/gameobjects/EGameObjectManager.h"
#include "../engine/components/ELogic.h"
#include "../engine/components/ERigidbody.h"
#include "logic/lilPlayerLogic.h"
#include "logic/lilLevelLogic.h"
#include "logic/lilCameraLogic.h"
#include "../engine/utilities/EFileIO.h"

// TODO: For testing only
#include <SDL.h>
float tempPixPerGU = 50.0f;

void lilLevel::Create(const char* filename)
{
	//SDL_Log("Create Level, %s %d", __FILE__, __LINE__);
	// CREATES CAMERA
	EGameObject* camera;
	camera = new EGameObject();
	camera->Create("data/gameobjects/camera.gmo", tempPixPerGU);
	ELogic* cameraLogicComponet = (ELogic*)camera->GetComponent("logic");
	if (cameraLogicComponet)
		cameraLogicComponet->SetLogicObject(new CameraLogic());
	lilGameObjectManager->AddGameObject(camera);

	// CREATES PLAYER
	EGameObject* player;
	player = new EGameObject();
	player->Create("data/gameobjects/playertest.gmo", tempPixPerGU);
	ELogic* playerLogicComponet = (ELogic*)player->GetComponent("logic");
	if (playerLogicComponet)
		playerLogicComponet->SetLogicObject(new PlayerLogic());
	ERigidbody* playerPhysicsComponent = (ERigidbody*)player->GetComponent("rigidbody");
	if (playerPhysicsComponent)
		playerPhysicsComponent->SetContactLogicFunction(PlayerBeginContact, PlayerEndContact);
	lilGameObjectManager->AddGameObject(player);


	// CREATES LEVEL BLOCK
	LoadLevel(filename);

	lilGameObjectManager->OnStart();
}

void lilLevel::Update()
{
	//SDL_Log("Update Level, %s %d", __FILE__, __LINE__);
	lilGameObjectManager->Update();
}

void lilLevel::Destroy()
{
	//SDL_Log("Destroy Level, %s %d", __FILE__, __LINE__);
	
	lilGameObjectManager->FreeGameObjects();
	// TODO: clear textures
	// TODO: clear renderer
	// TODO: clear shaders
	// TODO: free audio
	// TODO: clear physic engine
}

void lilLevel::LoadLevel(const char* filename)
{
	char* xmlFile = lilFileIO::ReadFile(filename, "r");

	TiXmlDocument xmlDoc;
	xmlDoc.Parse(xmlFile);

	delete[] xmlFile;
	xmlFile = 0;

	TiXmlElement* rootElement = xmlDoc.RootElement();
	if (!rootElement)
		return;

	for (TiXmlElement* levelObject = rootElement->FirstChildElement(); levelObject; levelObject = levelObject->NextSiblingElement())
	{
		EGameObject* block;
		block = new EGameObject();
		block->Create(levelObject, tempPixPerGU);
		ERigidbody* blockPhysicsComponent = (ERigidbody*)block->GetComponent("rigidbody");
		if (blockPhysicsComponent)
			blockPhysicsComponent->SetContactLogicFunction(BlockBeginContact, BlockEndContact);
		lilGameObjectManager->AddGameObject(block);
	}
}

