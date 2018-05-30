//
//  2DEngine
//  EGame.h
//  Eric Fleming
//  5/17/2018
//

#pragma once

#include <string>

#include "../../lilknight/scenes/lilScene.h"

class EGame
{
public:
	// Constructor
	EGame();

	// Destructor
	~EGame() {}

	// Initializes game, sets starting level state
	bool Initialize();

	// Updates the current game level
	// Checks if new level is to be loaded
	void Update();

	// Cleans up all open levels
	void CleanUp();

private:
	lilScene* m_Scene;

private:
	// No copying of class
	EGame(const EGame& game) {}
	void operator=(const EGame& game) {}
};

