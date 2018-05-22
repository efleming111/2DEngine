//
//  lil Knight
//  lilLevel.cpp
//  Eric Fleming
//  5/21/2018
//

#include "lilLevel.h"
#include "../engine/components/ELogic.h"
#include "../engine/components/ERigidbody.h"
#include "logic/lilPlayerLogic.h"
#include "logic/lilLevelLogic.h"
#include "../engine/utilities/EFileIO.h"

// TODO: For testing only
#include <SDL.h>

void lilLevel::Create(const char* filename)
{
	//SDL_Log("Create Level, %s %d", __FILE__, __LINE__);
	// CREATES CAMERA
	EGameObject* camera;
	camera = new EGameObject();
	camera->Create("data/gameobjects/camera.gmo", 100.0f);
	m_GameObjects.push_back(camera);

	// CREATES PLAYER
	EGameObject* player;
	player = new EGameObject();
	player->Create("data/gameobjects/playertest.gmo", 100.0f);
	ELogic* playerLogicComponet = (ELogic*)player->GetComponent("logic");
	if (playerLogicComponet)
		playerLogicComponet->SetLogicObject(new PlayerLogic());
	ERigidbody* playerPhysicsComponent = (ERigidbody*)player->GetComponent("rigidbody");
	if (playerPhysicsComponent)
		playerPhysicsComponent->SetContactLogicFunction(PlayerBeginContact, PlayerEndContact);
	m_GameObjects.push_back(player);


	// CREATES LEVEL BLOCK
	LoadLevel(filename);
}

void lilLevel::Update()
{
	//SDL_Log("Update Level, %s %d", __FILE__, __LINE__);
	for (unsigned i = 0; i < m_GameObjects.size(); ++i)
		m_GameObjects[i]->Update();
}

void lilLevel::Destroy()
{
	//SDL_Log("Destroy Level, %s %d", __FILE__, __LINE__);
	for (unsigned i = 0; i < m_GameObjects.size(); ++i)
	{
		m_GameObjects[i]->Destroy();
		delete m_GameObjects[i];
	}

	m_GameObjects.clear();

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
		block->Create(levelObject, 100.0f);
		ERigidbody* blockPhysicsComponent = (ERigidbody*)block->GetComponent("rigidbody");
		if (blockPhysicsComponent)
			blockPhysicsComponent->SetContactLogicFunction(BlockBeginContact, BlockEndContact);
		m_GameObjects.push_back(block);
	}
}

