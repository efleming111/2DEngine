//
//  lil Knight
//  lilKnightGame.cpp
//  Eric Fleming
//  5/17/2018
//

#include <sstream>
#include <iostream>

#include "lilKnightGame.h"
#include "../../thirdpartysrc/tinyxml/tinyxml.h"
#include "../engine/utilities/EFileIO.h"

lilKnightGame::lilKnightGame()
{
	m_CurrentScene = 0;
	m_NextScene = 0;
}

bool lilKnightGame::Initialize()
{
	LoadFirstSceneFilename();
	m_CurrentScene = LoadScene();

	return true;
}

void lilKnightGame::Update()
{
	m_CurrentScene->Update();

	if (CheckForSceneChange())
	{
		m_NextScene = LoadScene();
		m_CurrentScene->Destroy();
		delete m_CurrentScene;
		m_CurrentScene = m_NextScene;
		m_NextScene = 0;
	}
}

void lilKnightGame::CleanUp()
{
	if (m_CurrentScene)
	{
		m_CurrentScene->Destroy();
		delete m_CurrentScene;
		m_CurrentScene = 0;
	}

	if (m_NextScene)
	{
		m_NextScene->Destroy();
		delete m_NextScene;
		m_NextScene = 0;
	}
}

bool lilKnightGame::CheckForSceneChange()
{
	if (m_CurrentScene->sceneChangeRequest)
	{
		m_CurrentLoadedSceneName = m_CurrentScene->nextSceneToLoad;
		return true;
	}

	return false;
}

void lilKnightGame::LoadFirstSceneFilename()
{
	char* xmlFile = lilFileIO::ReadFile("data/scenes/gamestart.gme", "r");

	TiXmlDocument xmlDoc;
	xmlDoc.Parse(xmlFile);

	delete[] xmlFile;
	xmlFile = 0;

	TiXmlElement* rootElement = xmlDoc.RootElement();

	m_CurrentLoadedSceneName =  rootElement->Attribute("startscene");
}

lilScene* lilKnightGame::LoadScene()
{
	lilScene* level = new lilScene();
	level->Create(m_CurrentLoadedSceneName.c_str());

	return level;
}

