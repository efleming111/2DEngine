//
//  2DEngine
//  lilCore.cpp
//  Eric Fleming
//  4/2/2018
//

#include "lilCore.h"
#include "../renderer/lilGLWindow.h"
#include "../renderer/lilGLRenderer.h"
#include "../input/lilInput.h"
#include "../utilities/lilTimer.h"
#include "../audio/lilAudio.h"
#include "../physics/lilPhysics.h"


laCore* laCore::sInstance = 0;

laCore* laCore::Instance()
{
	if (!sInstance)
		sInstance = new laCore();

	return sInstance;
}

bool laCore::Initialize()
{
	mRunning = true;

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

	mGame = new lilGame();
	if (!mGame->Initialize())
	{
		SDL_Log("ERROR: Game Failed To Initialize, %s %d", __FILE__, __LINE__);
		mRunning = false;
	}

	return true;
}

void laCore::Run()
{
	lilTimer->Start();
	while (mRunning)
	{
		// Update core systems
		lilTimer->Update();
		lilInput->Update();
		lilPhysics->Update();

		// Update game
		mGame->Update();

		// Renderer
		lilGLRenderer->DrawFrame();

		// TODO: Erase after testing
		if(lilTimer->FPS() < 30)
			SDL_Log("LOW FPS: %d, %s %d", lilTimer->FPS(), __FILE__, __LINE__);
	}
}

void laCore::ShutDown()
{
	mGame->CleanUp();
	delete mGame;
	mGame = 0;

	lilPhysics->Shutdown();
	lilAudio->Shutdown();
	lilInput->Shutdown();
	lilGLWindow->Shutdown();
}

void laCore::Quit()
{
	mRunning = false;
}

void laCore::HandleCommandArgs(int numOfArgs, char* args[])
{
	for (int i = 0; i < numOfArgs; ++i)
	{
		std::string arg = args[i];
		mCommandLineArgs.push_back(arg);
	}
}

bool laCore::IsCommandActive(std::string command)
{
	bool temp = false;

	for (unsigned i = 0; i < mCommandLineArgs.size(); ++i)
		if (mCommandLineArgs[i].compare(command) == 0)
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