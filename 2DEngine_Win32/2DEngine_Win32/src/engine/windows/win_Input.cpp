//
//  2DEngine
//  win_Input.cpp
//  Eric Fleming
//  4/2/2018
//

#include "win_Input.h"
#include "../renderer/lilGLWindow.h"
#include "../renderer/lilGLRenderer.h"
#include "../core/lilCore.h"
#include "../utilities/lilFileIO.h"

lilInputAbstractionLayer::lilInputAbstractionLayer()
{
	mMouse = 0;
	mKeyboard = 0;

	for (int i = 0; i < MAX_GAME_CONTROLLERS; ++i)
		mGameControllers[i] = 0;

	mNumberOfControllers = 0;
}

bool lilInputAbstractionLayer::Initialize()
{
	mScreenWidth = lilGLWindow->Width();
	mScreenHeight = lilGLWindow->Height();

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

	return LoadData();
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
			mMouse->SetPosition((float)mEvent.motion.x, (float)(mScreenHeight - mEvent.motion.y));
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

bool lilInputAbstractionLayer::GetButton(std::string inputName, int gameControllerIndex)
{
	bool result = false;

	if (gameControllerIndex >= 0)
	{
		result = mGameControllers[gameControllerIndex]->GetButton(mUserInput[inputName].joystickButtonCode);
		if (result)
			return result;
	}

	else
	{
		result = mMouse->GetButton(mUserInput[inputName].mouseButtonCode);
		if (result)
			return result;
		for (int i = 0; i < mUserInput[inputName].keyboardCodes.size(); ++i)
		{
			result = mKeyboard->GetKey(mUserInput[inputName].keyboardCodes[i]);
			if (result)
				return result;
		}
	}

	return result;
}

bool lilInputAbstractionLayer::GetButtonDown(std::string inputName, int gameControllerIndex)
{
	bool result = false;

	if (gameControllerIndex >= 0)
	{
		result = mGameControllers[gameControllerIndex]->GetButtonDown(mUserInput[inputName].joystickButtonCode);
		if (result)
			return result;
	}

	else
	{
		result = mMouse->GetButtonDown(mUserInput[inputName].mouseButtonCode);
		if (result)
			return result;
		for (int i = 0; i < mUserInput[inputName].keyboardCodes.size(); ++i)
		{
			result = mKeyboard->GetKeyDown(mUserInput[inputName].keyboardCodes[i]);
			if (result)
				return result;
		}
	}

	return result;
}

void lilInputAbstractionLayer::GetCursorPositions(CursorPosition* cursorPositions, int* numberOfCursors)
{
	mCursorPositions[0].x = mMouse->X();
	mCursorPositions[0].y = mMouse->Y();

	cursorPositions = mCursorPositions;
	*numberOfCursors = 1;
}

void lilInputAbstractionLayer::GetCursorRelativePositions(CursorPosition* cursorRelativePositions, int* numberOfCursors)
{
	mCursorRelativePositions[0].x = mMouse->RelX();
	mCursorRelativePositions[0].y = mMouse->RelY();

	cursorRelativePositions = mCursorRelativePositions;
	*numberOfCursors = 1;
}

float lilInputAbstractionLayer::GetValue(std::string inputName, int gameControllerIndex)
{
	bool result = false;

	if (gameControllerIndex >= 0)
	{
		result = mGameControllers[gameControllerIndex]->GetButton(mUserInput[inputName].joystickButtonCode);
		if (result)
			return result;

		float gameControllerAxis = mGameControllers[gameControllerIndex]->GetAxis(mUserInput[inputName].joystickAxisCode);
		if (gameControllerAxis != 0.0)
			return gameControllerAxis * mUserInput[inputName].joystickAxisMultiplier;
	}

	else
	{
		result = mMouse->GetButton(mUserInput[inputName].mouseButtonCode);
		if (result)
			return 1.0f;
		for (int i = 0; i < mUserInput[inputName].keyboardCodes.size(); ++i)
		{
			result = mKeyboard->GetKey(mUserInput[inputName].keyboardCodes[i]);
			if (result)
				return 1.0f;
		}
	}

	return 0.0f;
}

bool lilInputAbstractionLayer::LoadData()
{
	char* xmlFile = lilFileIO::ReadFile("data/Input.xml", "r");

	TiXmlDocument xmlDoc;
	xmlDoc.Parse(xmlFile);

	delete[] xmlFile;
	xmlFile = 0;

	TiXmlElement* rootElement = xmlDoc.RootElement();
	if (!rootElement)
		return false;

	for (TiXmlElement* input = rootElement->FirstChildElement(); input; input = input->NextSiblingElement())
	{
		std::string inputName;
		std::vector<KeyCode> keyboardCodes;
		MouseButton mouseButtonCode;
		JoystickButton joystickButtonCode;
		int joystickAxisCode;
		double joystickAxisMultiplier;

		TiXmlElement* name = input->FirstChildElement("name");
		inputName = name->Attribute("name");

		TiXmlElement* keyboard = input->FirstChildElement("keyboard");
		for (TiXmlAttribute* key = keyboard->FirstAttribute(); key; key = key->Next())
			keyboardCodes.push_back((KeyCode)key->IntValue());

		TiXmlElement* mouse = input->FirstChildElement("mouse");
		mouseButtonCode = (MouseButton)mouse->FirstAttribute()->IntValue();

		TiXmlElement* joystick = input->FirstChildElement("joystickbutton");
		joystickButtonCode = (JoystickButton)joystick->FirstAttribute()->IntValue();
		joystick->Attribute("axis", &joystickAxisCode);
		joystick->Attribute("axismultiplier", &joystickAxisMultiplier);

		mUserInput[inputName].keyboardCodes = keyboardCodes;
		mUserInput[inputName].mouseButtonCode = mouseButtonCode;
		mUserInput[inputName].joystickButtonCode = joystickButtonCode;
		mUserInput[inputName].joystickAxisCode = (JoystickAxis)joystickAxisCode;
		mUserInput[inputName].joystickAxisMultiplier = joystickAxisMultiplier;
	}

	return true;
}

