//
//  lil Knight
//  lilScene.cpp
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
#include "../gameobjects/lilHUD.h"
#include "../../engine/utilities/EFileIO.h"

float tempPixPerGU = 50.0f;

void lilScene::Create(const char* filename)
{
	loadNewScene = false;

	char* xmlFile = lilFileIO::ReadFile(filename, "r");

	TiXmlDocument xmlDoc;
	xmlDoc.Parse(xmlFile);

	delete[] xmlFile;
	xmlFile = 0;

	TiXmlElement* rootElement = xmlDoc.RootElement();
	if (!rootElement)
		return;

	LoadRenderableResources(rootElement->FirstChildElement("resources"));
	GameObjectFactory(rootElement->FirstChildElement("scene"));

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
	lilGLRenderer->FreeRenderer();
	lilShaderManager->FreeShaders();
	lilMeshManager->FreeMeshes();
	lilTextureManager->FreeTextures();
}

void lilScene::LoadRenderableResources(TiXmlElement* resources)
{
	// TODO: Add new type of resource here
	for (TiXmlElement* asset = resources->FirstChildElement(); asset; asset = asset->NextSiblingElement())
	{
		std::string type = asset->Attribute("type");

		if (type.compare("Renderable") == 0)
			lilGLRenderer->AddRenderable(asset, tempPixPerGU);
	}
}

void lilScene::GameObjectFactory(TiXmlElement* scene)
{
	// TODO: Add new game objects here
	for (TiXmlElement* gameObject = scene->FirstChildElement(); gameObject; gameObject = gameObject->NextSiblingElement())
	{
		std::string type = gameObject->Attribute("type");

		if (type.compare("Scene") == 0)
		{
			m_SceneObject = new SceneObject();
			m_SceneObject->Create(gameObject, tempPixPerGU);
			lilGameObjectManager->AddGameObject(m_SceneObject);
		}

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

		else if (type.compare("HUD") == 0)
		{
			HUD* hud;
			hud = new HUD();
			hud->Create(gameObject, tempPixPerGU);
			lilGameObjectManager->AddGameObject(hud);
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
