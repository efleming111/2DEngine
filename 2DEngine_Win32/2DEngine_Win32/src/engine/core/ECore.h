//
//  2DEngine
//  ECore.h
//  Eric Fleming
//  4/2/2018
//

#pragma once

#include <vector>
#include <string>

#include <SDL.h>

#include "EGame.h"

#define lilEngine ECore::Instance()

class ECore
{
public:
	// Returns only instance of class
	static ECore* Instance();

	// Initialize all subsystems of the engine and main game file
	bool Initialize();

	// Loads the main game code
	// @ game - Pass in the main game object, derived from EGame
	void LoadGame(EGame* game);

	// Runs the game loop, updating all subsystems
	// Calls update on the main game
	void Run();

	// Cleans up all subsystems and main game file
	void ShutDown();

	// Exits main game loop
	void Quit();

	// Stores the arguments passed to the game for later use
	// @ numOfArgs - Pass in number of arguments passed into main
	// @ args - The arguments passed into main
	void HandleCommandArgs(int numOfArgs, char* args[]);

	// Returns if and argument exists
	// @ command - The command client is queuing for
	bool IsCommandActive(std::string command);

private:
	static ECore* s_Instance;

	std::vector<std::string> m_CommandLineArgs;

	bool m_Running;

	EGame* m_Game;

private:
#ifdef __ANDROID__
	static int AndoridLifeCycleEvents(void* userData, SDL_Event* event);
#endif

	// Only one instance of class and no copying
	ECore() {}
	~ECore() {}
	ECore(const ECore& core) {}
	void operator=(const ECore& core) {}
};

#ifdef __ANDROID__
int AndroidLifeCycleEvents(void* userData, SDL_Event* event);
#endif

