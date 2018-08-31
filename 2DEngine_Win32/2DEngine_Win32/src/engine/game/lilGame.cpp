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
	mScene = 0;
}

bool lilGame::Initialize()
{
	mScene = new lilScene();
	// TODO: Change this to generic start scene from which the game is loaded
	mScene->Create("data/scenes/starterscene.scn");

	return true;
}

void lilGame::Update()
{
	mScene->Update();

	if (mScene->loadNewScene)
	{
		std::string newScene = mScene->nextSceneFilename;
		mScene->Destroy();
		mScene->Create(newScene.c_str());
	}
}

void lilGame::CleanUp()
{
	mScene->Destroy();
	delete mScene;
	mScene = 0;
}

