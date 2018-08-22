//
//  2DEngine
//  lilCore.h
//  Eric Fleming
//  4/2/2018
//

#pragma once

#include <list>
#include <string>

#include <SDL.h>

#include "../game/lilGame.h"

#define lilEngine ECore::Instance()

class laCore
{
public:
	// Returns only instance of class
	static laCore* Instance();

	// Initialize all subsystems of the engine and main game file
	bool Initialize();

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
	static laCore* s_Instance;

	std::list<std::string> m_CommandLineArgs;

	bool m_Running;

	lilGame* m_Game;

private:
	//TODO: move this to android file
#ifdef __ANDROID__
	static int AndoridLifeCycleEvents(void* userData, SDL_Event* event);
#endif

	// Only one instance of class and no copying
	laCore() {}
	~laCore() {}
	laCore(const laCore& core) {}
	void operator=(const laCore& core) {}
};

#ifdef __ANDROID__
int AndroidLifeCycleEvents(void* userData, SDL_Event* event);
#endif

