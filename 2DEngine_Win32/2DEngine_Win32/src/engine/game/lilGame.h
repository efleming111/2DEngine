//
//  2DEngine
//  lilGame.h
//  Eric Fleming
//  5/17/2018
//

#pragma once

#include <string>

// TODO: Change this to Scene.h
#include "../../lilknight/scenes/lilScene.h"

class lilGame
{
public:
	// Constructor
	lilGame();

	// Destructor
	~lilGame() {}

	// Initializes game, sets starting level state
	bool Initialize();

	// Updates the current game level
	// Checks if new level is to be loaded
	void Update();

	// Cleans up all open levels
	void CleanUp();

private:
	// TODO: Change this to Scene.h
	lilScene* m_Scene;

private:
	// No copying of class
	lilGame(const lilGame& game) {}
	void operator=(const lilGame& game) {}
};

