//
//  2DEngine
//  lilGame.cpp
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
	mLevelManager = 0;
}

bool lilGame::Initialize()
{
	mLevelManager = new laLevelManager();
	mLevelManager->Create("data/scenes/default.lvl");

	return true;
}

void lilGame::Update()
{
	mLevelManager->Update();

	if (mLevelManager->loadNewScene)
	{
		std::string newScene = mLevelManager->nextSceneFilename;
		mLevelManager->Destroy();
		mLevelManager->Create(newScene.c_str());
	}
}

void lilGame::CleanUp()
{
	mLevelManager->Destroy();
	delete mLevelManager;
	mLevelManager = 0;
}

