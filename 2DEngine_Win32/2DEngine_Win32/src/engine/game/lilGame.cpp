//
//  2DEngine
//  lilGamecpp
//  Eric Fleming
//  5/17/2018
//

#include <sstream>
#include <iostream>

#include "lilGame.h"
#include "../../../thirdpartysrc/tinyxml/tinyxml.h"
#include "../utilities/lilFileIO.h"

lilGame::lilGame()
{
	m_Scene = 0;
}

bool lilGame::Initialize()
{
	m_Scene = new lilScene();
	// TODO: Change this to generic start scene from which the game is loaded
	m_Scene->Create("data/scenes/starterscene.scn");

	return true;
}

void lilGame::Update()
{
	m_Scene->Update();

	if (m_Scene->loadNewScene)
	{
		std::string newScene = m_Scene->nextSceneFilename;
		m_Scene->Destroy();
		m_Scene->Create(newScene.c_str());
	}
}

void lilGame::CleanUp()
{
	m_Scene->Destroy();
	delete m_Scene;
	m_Scene = 0;
}

