//
//  2DEngine
//  win_Input.h
//  Eric Fleming
//  4/2/2018
//

#pragma once

#include <string>
#include <map>
#include <vector>

#include <SDL.h>

#include "win_Mouse.h"
#include "win_Keyboard.h"
#include "win_GameController.h"

const int MAX_CURSOR_VALUES = 10;
const int MAX_GAME_CONTROLLERS = 4;

struct UserDefinedInput
{
	std::vector<KeyCode> keyboardCodes;
	MouseButton mouseButtonCode;
	JoystickButton joystickButtonCode;
	JoystickAxis joystickAxisCode;
	float joystickAxisMultiplier;
};

struct CursorPosition
{
	float x;
	float y;
};

class lilInputAbstractionLayer
{
public:
	lilInputAbstractionLayer();

	// Creates input system
	bool Initialize();

	// Updates input system
	void Update();

	// Closes all input devices and cleans up input system
	void Shutdown();

	// Get input state
	bool GetButton(std::string inputName, int gameControllerIndex);
	bool GetButtonDown(std::string inputName, int gameControllerIndex);

	void GetCursorPositions(CursorPosition* cursorPositions, int* numberOfCursors);
	void GetCursorRelativePositions(CursorPosition* cursorRelativePositions, int* numberOfCursors);

	float GetValue(std::string inputName, int gameControllerIndex);


private:
	std::map<std::string, UserDefinedInput> mUserInput;
	CursorPosition mCursorPositions[MAX_CURSOR_VALUES];
	CursorPosition mCursorRelativePositions[MAX_CURSOR_VALUES];

	SDL_Event mEvent;

	lilMouse* mMouse;
	lilKeyboard* mKeyboard;
	lilGameController* mGameControllers[MAX_GAME_CONTROLLERS];
	unsigned mNumberOfControllers;

	int mScreenWidth;
	int mScreenHeight;

private:
	bool LoadData();

	// No copying
	lilInputAbstractionLayer(const lilInputAbstractionLayer& input) {}
	void operator=(const lilInputAbstractionLayer& input) {}
};

