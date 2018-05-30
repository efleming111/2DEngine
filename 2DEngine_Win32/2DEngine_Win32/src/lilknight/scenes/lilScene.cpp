//
//  lil Knight
//  lilLevel.cpp
//  Eric Fleming
//  5/21/2018
//

#include "lilScene.h"
#include "../../engine/gameobjects/EGameObjectManager.h"
#include "../../engine/components/ERigidbody.h"
#include "../../engine/components/subcomponents/EMeshManager.h"
#include "../../engine/components/subcomponents/EShaderManager.h"
#include "../../engine/components/subcomponents/ETextureManager.h"
#include "../../engine/renderer/EGLRenderer.h"
#include "../../engine/audio/EAudio.h"
#include "../../engine/physics/EPhysics.h"
#include "../gameobjects/lilPlayer.h"
#include "../gameobjects/lilLevelObject.h"
#include "../gameobjects/lilCamera.h"
#include "../../engine/utilities/EFileIO.h"

// TODO: For testing only
#include <SDL.h>
float tempPixPerGU = 50.0f;

void lilScene::Create(const char* filename)
{
	sceneChangeRequest = false;

	GameObjectFactory(filename);

	lilGameObjectManager->OnStart();
}

void lilScene::Update()
{
	lilGameObjectManager->Update();
}

void lilScene::Destroy()
{
	lilAudio->FreeMusic();
	lilAudio->FreeSounds();
	lilGameObjectManager->FreeGameObjects();
	lilGLRenderer->FreeSprites();
	lilShaderManager->FreeShaders();
	lilMeshManager->FreeMeshes();
	lilTextureManager->FreeTextures();
	lilPhysics->DestroyBodies();
}

void lilScene::GameObjectFactory(const char* filename)
{
	char* xmlFile = lilFileIO::ReadFile(filename, "r");

	TiXmlDocument xmlDoc;
	xmlDoc.Parse(xmlFile);

	delete[] xmlFile;
	xmlFile = 0;

	TiXmlElement* rootElement = xmlDoc.RootElement();
	if (!rootElement)
		return;

	// TODO: Add new game objects here
	for (TiXmlElement* gameObject = rootElement->FirstChildElement(); gameObject; gameObject = gameObject->NextSiblingElement())
	{
		std::string type = gameObject->Attribute("type");

		if (type.compare("Camera") == 0)
		{
			Camera* camera;
			camera = new Camera();
			camera->Create(gameObject, tempPixPerGU);
			lilGameObjectManager->AddGameObject(camera);
		}

		else if (type.compare("Player") == 0)
		{
			Player* player;
			player = new Player();
			player->Create(gameObject, tempPixPerGU);
			lilGameObjectManager->AddGameObject(player);
		}

		else if (type.compare("LevelObject") == 0)
		{
			LevelObject* levelObject;
			levelObject = new LevelObject();
			levelObject->Create(gameObject, tempPixPerGU);
			lilGameObjectManager->AddGameObject(levelObject);
		}
	}
}

