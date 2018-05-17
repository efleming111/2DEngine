//
//  lil Knight
//  lilKnightGame.h
//  Eric Fleming
//  5/17/2018
//

#pragma once

#include <vector>
#include <string>

#include "../engine/core/EGame.h"
#include "lilLevel.h"

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
	std::vector<std::string> m_LevelFilenames;

	int m_CurrentLoadedLevelIndex;

	lilLevel* m_CurrentLevel;
	lilLevel* m_NextLevel;

private:
	// No copying of class
	lilKnightGame(const lilKnightGame& game) {}
	void operator=(const lilKnightGame& game) {}

	// Check current level to see if new level is to be loaded
	bool CheckForLevelChange();

	// Loads file name of all levels for game
	void LoadAllLevelFilenames();

	// Creates and loads a level object
	lilLevel* LoadLevel();
};

