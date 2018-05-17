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
	m_CurrentLevel = 0;
	m_NextLevel = 0;
}

bool lilKnightGame::Initialize()
{
	LoadAllLevelFilenames();
	m_CurrentLevel = LoadLevel();

	return true;
}

void lilKnightGame::Update()
{
	m_CurrentLevel->Update();

	if (CheckForLevelChange())
	{
		m_NextLevel = LoadLevel();
		m_CurrentLevel->Destroy();
		delete m_CurrentLevel;
		m_CurrentLevel = m_NextLevel;
		m_NextLevel = 0;
	}
}

void lilKnightGame::CleanUp()
{
	if (m_CurrentLevel)
	{
		m_CurrentLevel->Destroy();
		delete m_CurrentLevel;
		m_CurrentLevel = 0;
	}

	if (m_NextLevel)
	{
		m_NextLevel->Destroy();
		delete m_NextLevel;
		m_NextLevel = 0;
	}
}

bool lilKnightGame::CheckForLevelChange()
{
	if (m_CurrentLoadedLevelIndex != m_CurrentLevel->m_CurrentLevelIndex)
	{
		m_CurrentLoadedLevelIndex = m_CurrentLevel->m_CurrentLevelIndex;
		return true;
	}

	return false;
}

void lilKnightGame::LoadAllLevelFilenames()
{
	char* xmlFile = lilFileIO::ReadFile("data/levels/gamelevels.gme", "r");

	TiXmlDocument xmlDoc;
	xmlDoc.Parse(xmlFile);

	delete[] xmlFile;
	xmlFile = 0;

	TiXmlElement* rootElement = xmlDoc.RootElement();

	int size = 0;
	rootElement->Attribute("size", &size);
	rootElement->Attribute("startIndex", &m_CurrentLoadedLevelIndex);

	std::string str = rootElement->GetText();
	std::stringstream levelNames(str, std::ios_base::in);
	for (int i = 0; i < size; ++i)
	{
		std::string levelName;
		char discard;
		levelNames >> levelName;
		levelNames >> discard;
		m_LevelFilenames.push_back(levelName);
	}
}

lilLevel* lilKnightGame::LoadLevel()
{
	lilLevel* level = new lilLevel();
	level->Create(m_LevelFilenames[m_CurrentLoadedLevelIndex].c_str());

	return level;
}

