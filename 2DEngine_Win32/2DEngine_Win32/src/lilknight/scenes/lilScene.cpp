//
//  lil Knight
//  lilScene.cpp
//  Eric Fleming
//  5/21/2018
//

#include "lilScene.h"
#include "../../engine/gameobjects/EGameObjectManager.h"
#include "../../engine/components/ERigidbody.h"
#include "../../engine/renderer/EGLRenderer.h"
#include "../../engine/renderer/EGLWindow.h"
#include "../../engine/audio/EAudio.h"
#include "../../engine/physics/EPhysics.h"
#include "../gameobjects/lilPlayer.h"
#include "../gameobjects/lilLevelObject.h"
#include "../gameobjects/lilCamera.h"
#include "../gameobjects/lilHUD.h"
#include "../../engine/utilities/EFileIO.h"

void lilScene::Create(const char* filename)
{
	loadNewScene = false;

	char* xmlFile = lilFileIO::ReadFile(filename, "r");

	TiXmlDocument xmlDoc;
	xmlDoc.Parse(xmlFile);

	delete[] xmlFile;
	xmlFile = 0;

	TiXmlElement* scene = xmlDoc.RootElement();
	if (!scene)
		return;

	int sceneWidth, sceneHeight;
	scene->Attribute("width", &sceneWidth);
	scene->Attribute("height", &sceneHeight);
	if (sceneHeight == 0)
		sceneHeight = 1;
	m_PixelsPerGameUnit = (float)lilGLWindow->Height() / (float)sceneHeight;
	SDL_Log("Pixels Per %d, %s %d", (int)m_PixelsPerGameUnit, __FILE__, __LINE__);

	for (TiXmlElement* gob = scene->FirstChildElement(); gob; gob = gob->NextSiblingElement())
	{
		std::string gobFilename = gob->Attribute("filename");

		char* gobFile = lilFileIO::ReadFile(gobFilename.c_str(), "r");

		TiXmlDocument gobDoc;
		gobDoc.Parse(gobFile);

		delete[] gobFile;
		gobFile = 0;

		TiXmlElement* rootElement = gobDoc.RootElement();
		if (!rootElement)
			return;

		LoadRenderableResources(rootElement->FirstChildElement("resources"));
		GameObjectFactory(rootElement);
	}

	lilGameObjectManager->OnStart();

	nextSceneFilename = m_SceneObject->GetNextScene();
}

void lilScene::Update()
{
	lilGameObjectManager->Update();

	loadNewScene = m_SceneObject->ChangeScene();
}

void lilScene::Destroy()
{
	// This Order is important
	lilPhysics->DestroyBodies();
	lilAudio->FreeMusic();
	lilAudio->FreeSounds();
	lilGameObjectManager->FreeGameObjects();
	lilGLRenderer->ClearRenderer();
}

void lilScene::LoadRenderableResources(TiXmlElement* resources)
{
	// TODO: Add new type of resource here
	for (TiXmlElement* asset = resources->FirstChildElement(); asset; asset = asset->NextSiblingElement())
	{
		std::string type = asset->Attribute("type");

		if (type.compare("Renderable") == 0)
			lilGLRenderer->AddRenderable(asset, m_PixelsPerGameUnit);
	}
}

void lilScene::GameObjectFactory(TiXmlElement* rootElement)
{
	// TODO: Add new game objects here
	for (TiXmlElement* gameObject = rootElement->FirstChildElement("gameobject"); gameObject; gameObject = gameObject->NextSiblingElement())
	{
		std::string type = gameObject->Attribute("type");

		if (type.compare("Scene") == 0)
		{
			m_SceneObject = new SceneObject();
			m_SceneObject->Create(gameObject, m_PixelsPerGameUnit);
			lilGameObjectManager->AddGameObject(m_SceneObject);
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
	}
}

