//
//  lil Knight
//  lilLevel.cpp
//  Eric Fleming
//  5/21/2018
//

#include "lilLevel.h"
#include "../engine/gameobjects/EGameObjectManager.h"
#include "../engine/components/ERigidbody.h"
#include "gameobjects/lilPlayer.h"
#include "gameobjects/lilLevelObject.h"
#include "gameobjects/lilCamera.h"
#include "../engine/utilities/EFileIO.h"

// TODO: For testing only
#include <SDL.h>
float tempPixPerGU = 50.0f;

void lilLevel::Create(const char* filename)
{
	//SDL_Log("Create Level, %s %d", __FILE__, __LINE__);
	// CREATES CAMERA
	Camera* camera;
	camera = new Camera();
	camera->Create("data/gameobjects/camera.gmo", tempPixPerGU);
	lilGameObjectManager->AddGameObject(camera);

	// CREATES PLAYER
	Player* player;
	player = new Player();
	player->Create("data/gameobjects/playertest.gmo", tempPixPerGU);
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
		LevelObject* block;
		block = new LevelObject();
		block->Create(levelObject, tempPixPerGU);
		lilGameObjectManager->AddGameObject(block);
	}
}

