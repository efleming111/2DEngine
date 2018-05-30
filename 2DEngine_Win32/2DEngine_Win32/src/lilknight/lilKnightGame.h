//
//  lil Knight
//  lilKnightGame.h
//  Eric Fleming
//  5/17/2018
//

#pragma once

#include <string>

#include "../engine/core/EGame.h"
#include "scenes/lilScene.h"

class lilKnightGame : public EGame
{
public:
	// Constructor
	lilKnightGame();

	// Destructor
	virtual ~lilKnightGame() {}

	// Initializes game, sets starting level state
	bool Initialize();

	// Updates the current game level
	// Checks if new level is to be loaded
	void Update();

	// Cleans up all open levels
	void CleanUp();

private:
	std::string m_CurrentLoadedSceneName;

	lilScene* m_CurrentScene;
	lilScene* m_NextScene;

private:
	// No copying of class
	lilKnightGame(const lilKnightGame& game) {}
	void operator=(const lilKnightGame& game) {}

	// Check current scene to see if new scene is to be loaded
	bool CheckForSceneChange();

	// Loads file name of first scene
	void LoadFirstSceneFilename();

	// Creates and loads a scene object
	lilScene* LoadScene();
};

