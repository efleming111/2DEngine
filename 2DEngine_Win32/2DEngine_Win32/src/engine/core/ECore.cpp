//
//  2DEngine
//  ECore.cpp
//  Eric Fleming
//  4/2/2018
//

#include "ECore.h"
#include "../renderer/EGLWindow.h"
#include "../renderer/EGLRenderer.h"
#include "../input/EInput.h"
#include "../utilities/ETimer.h"
#include "../audio/EAudio.h"
#include "../physics/EPhysics.h"


ECore* ECore::s_Instance = 0;

ECore* ECore::Instance()
{
	if (!s_Instance)
		s_Instance = new ECore();

	return s_Instance;
}

bool ECore::Initialize()
{
	m_Running = true;

#ifdef __ANDROID__
	SDL_SetEventFilter(AndroidLifeCycleEvents, 0);
#endif

	if (!lilGLWindow->Initialize())
		return false;

	if (!lilGLRenderer->Initialize())
		return false;

	if (!lilInput->Initialize())
		return false;

	if (!lilTimer->Initialize())
		return false;

	if (!lilAudio->Initialize())
		return false;

	if (!lilPhysics->Initialize(0.0f, -10.0f))
		return false;

	m_Game = new EGame();
	if (!m_Game->Initialize())
	{
		SDL_Log("ERROR: Game Failed To Initialize, %s %d", __FILE__, __LINE__);
		m_Running = false;
	}

	return true;
}

void ECore::Run()
{
	lilTimer->Start();
	while (m_Running)
	{
		// Update core systems
		lilTimer->Update();
		lilInput->Update();
		lilPhysics->Update();

		// Update game
		m_Game->Update();

		// Renderer
		lilGLRenderer->DrawFrame();

		// TODO: Erase after testing
		if(lilTimer->FPS() < 30)
			SDL_Log("LOW FPS: %d, %s %d", lilTimer->FPS(), __FILE__, __LINE__);
	}
}

void ECore::ShutDown()
{
	m_Game->CleanUp();
	delete m_Game;
	m_Game = 0;

	lilPhysics->Shutdown();
	lilAudio->Shutdown();
	lilInput->Shutdown();
	lilGLWindow->Shutdown();
}

void ECore::Quit()
{
	m_Running = false;
}

void ECore::HandleCommandArgs(int numOfArgs, char* args[])
{
	for (int i = 0; i < numOfArgs; ++i)
	{
		std::string arg = args[i];
		m_CommandLineArgs.push_back(arg);
	}
}

bool ECore::IsCommandActive(std::string command)
{
	bool temp = false;

	for (std::list<std::string>::iterator it = m_CommandLineArgs.begin(); it != m_CommandLineArgs.end(); it++)
		if ((*it).compare(command) == 0)
			return true;

	return false;
}

// TODO: Handle Android callbacks
#ifdef __ANDROID__
int AndroidLifeCycleEvents(void * userData, SDL_Event * event)
{
	// SDL_Log("Life Cycle Event, %s %d", __FILE__, __LINE__);
	switch (event->type)
	{
	case SDL_APP_LOWMEMORY:
		SDL_Log("SDL_APP_LOWMEMORY, %s %d", __FILE__, __LINE__);
		break;

	case SDL_APP_TERMINATING:
		SDL_Log("SDL_APP_TERMINATING, %s %d", __FILE__, __LINE__);
		break;

	case SDL_APP_WILLENTERBACKGROUND:
		SDL_Log("SDL_APP_WILLENTERBACKGROUND, %s %d", __FILE__, __LINE__);
		break;

	case SDL_APP_DIDENTERBACKGROUND:
		SDL_Log("SDL_APP_DIDENTERBACKGROUND, %s %d", __FILE__, __LINE__);
		break;

	case SDL_APP_WILLENTERFOREGROUND:
		SDL_Log("SDL_APP_WILLENTERFOREGROUND, %s %d", __FILE__, __LINE__);
		break;

	case SDL_APP_DIDENTERFOREGROUND:
		SDL_Log("SDL_APP_DIDENTERFOREGROUND, %s %d", __FILE__, __LINE__);
		break;
	}

	return 1;
}
#endif