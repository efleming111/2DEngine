//
//  lil Knight
//  lilScene.cpp
//  Eric Fleming
//  5/21/2018
//

#include "laLevelManager.h"
#include "../../engine/gameobjects/lilGameObjectManager.h"
#include "../../engine/components/lilRigidbody.h"
#include "../../engine/renderer/lilGLRenderer.h"
#include "../../engine/renderer/lilGLWindow.h"
#include "../../engine/audio/lilAudio.h"
#include "../../engine/physics/lilPhysics.h"
#include "../../engine/utilities/lilFileIO.h"

#include "../gameobjects/laPlayer.h"
#include "../gameobjects/enemies/laZombie.h"
#include "../gameobjects/laLevelObject.h"
#include "../gameobjects/laCamera.h"
#include "../gameobjects/laHUD.h"
#include "../gameobjects/laButtonControls.h"


void laLevelManager::Create(const char* filename)
{
	loadNewScene = false;

	char* xmlFile = lilFileIO::ReadFile(filename, "r");

	TiXmlDocument xmlDoc;
	xmlDoc.Parse(xmlFile);

	delete[] xmlFile;
	xmlFile = 0;

	TiXmlElement* level = xmlDoc.RootElement();
	if (!level)
		return;

	int levelWidth, levelHeight;
	level->Attribute("width", &levelWidth);
	level->Attribute("height", &levelHeight);
	if (levelHeight == 0)
		levelHeight = 1;
	mPixelsPerGameUnit = (float)lilGLWindow->Height() / (float)levelHeight;

	for (TiXmlElement* go = level->FirstChildElement(); go; go = go->NextSiblingElement())
	{
		std::string goFilename = go->Attribute("filename");

		char* goFile = lilFileIO::ReadFile(goFilename.c_str(), "r");

		TiXmlDocument goDoc;
		goDoc.Parse(goFile);

		delete[] goFile;
		goFile = 0;

		TiXmlElement* rootElement = goDoc.RootElement();
		if (!rootElement)
			return;

		LoadRenderableResources(rootElement->FirstChildElement("resources"));
		GameObjectFactory(rootElement);
	}

	lilGameObjectManager->OnStart();
}

void laLevelManager::Update()
{
	lilGameObjectManager->Update();

	loadNewScene = mLevelController->ChangeScene();
	nextSceneFilename = mLevelController->GetNextScene();
}

void laLevelManager::Destroy()
{
	// This Order is important
	lilPhysics->DestroyBodies();
	lilAudio->FreeMusic();
	lilAudio->FreeSounds();
	lilGameObjectManager->FreeGameObjects();
	lilGLRenderer->ClearRenderer();
}

void laLevelManager::LoadRenderableResources(TiXmlElement* resources)
{
	// TODO: Add new type of resource here
	for (TiXmlElement* asset = resources->FirstChildElement(); asset; asset = asset->NextSiblingElement())
	{
		std::string type = asset->Attribute("type");

		if (type.compare("Renderable") == 0)
			lilGLRenderer->AddRenderable(asset, mPixelsPerGameUnit);
	}
}

void laLevelManager::GameObjectFactory(TiXmlElement* rootElement)
{
	// TODO: Add new game objects here
	for (TiXmlElement* gameObject = rootElement->FirstChildElement("gameobject"); gameObject; gameObject = gameObject->NextSiblingElement())
	{
		std::string type = gameObject->Attribute("type");

		if (type.compare("Scene") == 0)
		{
			mLevelController = new laLevelController();
			mLevelController->Create(gameObject, mPixelsPerGameUnit);
			lilGameObjectManager->AddGameObject(mLevelController);
		}

		if (type.compare("Camera") == 0)
		{
			Camera* camera;
			camera = new Camera();
			camera->Create(gameObject, m_PixelsPerGameUnit);
			lilGameObjectManager->AddGameObject(camera);
		}

		else if (type.compare("Player") == 0)
		{
			Player* player;
			player = new Player();
			player->Create(gameObject, m_PixelsPerGameUnit);
			lilGameObjectManager->AddGameObject(player);
		}

		else if (type.compare("Zombie") == 0)
		{
			Zombie* zombie;
			zombie = new Zombie();
			zombie->Create(gameObject, m_PixelsPerGameUnit);
			lilGameObjectManager->AddGameObject(zombie);
		}

		else if (type.compare("HUD") == 0)
		{
			HUD* hud;
			hud = new HUD();
			hud->Create(gameObject, m_PixelsPerGameUnit);
			lilGameObjectManager->AddGameObject(hud);
		}

		else if (type.compare("LevelObject") == 0)
		{
			LevelObject* levelObject;
			levelObject = new LevelObject();
			levelObject->Create(gameObject, m_PixelsPerGameUnit);
			lilGameObjectManager->AddGameObject(levelObject);
		}

		else if (type.compare("ButtonControls") == 0)
		{
			ButtonControls* buttonControls = new ButtonControls();
			buttonControls->Create(gameObject, m_PixelsPerGameUnit);
			lilGameObjectManager->AddGameObject(buttonControls);
		}
	}
}

