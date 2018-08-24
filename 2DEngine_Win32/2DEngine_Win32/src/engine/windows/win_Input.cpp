//
//  2DEngine
//  win_Input.cpp
//  Eric Fleming
//  4/2/2018
//

#include "win_Input.h"
#include "../renderer/lilGLRenderer.h"
#include "../core/lilCore.h"

lilInputAbstractionLayer::lilInputAbstractionLayer()
{
	mMouse = 0;
	mKeyboard = 0;

	for (int i = 0; i < MAX_GAME_CONTROLLERS; ++i)
		mGameControllers[i] = 0;

	mNumberOfControllers = 0;
}

bool lilInputAbstractionLayer::Initialize(int screenWidth, int screenHeight)
{
	m_ScreenWidth = screenWidth;
	m_ScreenHeight = screenHeight;

	mMouse = new lilMouse();
	if (!mMouse->Initialize())
	{
		SDL_Log("ERROR: Mouse Failed To Initialize %s %d", __FILE__, __LINE__);
		return false;
	}

	mKeyboard = new lilKeyboard();
	if (!mKeyboard->Initialize())
	{
		SDL_Log("ERROR: Keyboard Failed To Initialize %s %d", __FILE__, __LINE__);
		return false;
	}

	if (!SDL_WasInit(SDL_INIT_GAMECONTROLLER))
		SDL_InitSubSystem(SDL_INIT_GAMECONTROLLER);

	if (SDL_NumJoysticks() > 0)
	{
		for (int i = 0; i < SDL_NumJoysticks() && i < MAX_GAME_CONTROLLERS; ++i)
		{
			if (SDL_IsGameController(i))
			{
				SDL_GameController* controller = SDL_GameControllerOpen(i);
				if (controller)
				{
					lilGameController* gameController = new lilGameController();
					gameController->Initialize(controller);
					mGameControllers[i] = gameController;
					mNumberOfControllers = (unsigned)i + 1u;
				}
			}
		}
	}

	return true;
}

void lilInputAbstractionLayer::Update()
{
	// Update input devices
	mKeyboard->Update();
	mMouse->Update();
	for (unsigned i = 0; i < mNumberOfControllers; ++i)
		mGameControllers[i]->Update();

	// Update input device states
	while (SDL_PollEvent(&mEvent))
	{
		switch (mEvent.type)
		{
		case SDL_QUIT:
			lilEngine->Quit();
			break;

		case SDL_WINDOWEVENT:
			switch (mEvent.window.event)
			{
			case SDL_WINDOWEVENT_RESIZED:
			case SDL_WINDOWEVENT_SIZE_CHANGED:
				lilGLRenderer->ResizeViewport(mEvent.window.data1, mEvent.window.data2);
				break;
			}
			break;

		case SDL_KEYDOWN:
			mKeyboard->UpdateKeyDown(&mEvent);
			break;

		case SDL_KEYUP:
			mKeyboard->UpdateKeyUp(&mEvent);
			break;

		case SDL_MOUSEBUTTONDOWN:
			mMouse->UpdateButtonDown(&mEvent);
			break;

		case SDL_MOUSEBUTTONUP:
			mMouse->UpdateButtonUp(&mEvent);
			break;

		case SDL_MOUSEWHEEL:
			mMouse->SetWheel((float)mEvent.wheel.y);
			break;

		case SDL_MOUSEMOTION:
			mMouse->SetPosition((float)mEvent.motion.x, (float)(m_ScreenHeight - mEvent.motion.y));
			mMouse->SetRelativePosition((float)mEvent.motion.xrel, (float)(-mEvent.motion.yrel));
			break;
		}
	}
}

void lilInputAbstractionLayer::Shutdown()
{
	delete mMouse;
	mMouse = 0;

	delete mKeyboard;
	mKeyboard = 0;

	for (unsigned i = 0; i < mNumberOfControllers; ++i)
	{
		mGameControllers[i]->Shutdown();
		delete mGameControllers[i];
		mGameControllers[i] = 0;
	}
}

