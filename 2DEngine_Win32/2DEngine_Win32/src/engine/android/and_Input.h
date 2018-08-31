//
//  2DEngine
//  and_Input.h
//  Eric Fleming
//  4/2/2018
//

#pragma once

#include <vector>
#include <map>

#include <SDL.h>

#include "and_Touch.h"
#include "../input/lilInputDefines.h"

const int MAX_CURSOR_VALUES = 10;

struct UserDefinedInput
{
	lilButton button;
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

	float GetValue(std::string inputName, int gameControllerIndex) { return 0.0f; }

private:
	std::map<std::string, UserDefinedInput> mUserInput;
	CursorPosition mCursorPositions[MAX_CURSOR_VALUES];
	CursorPosition mCursorRelativePositions[MAX_CURSOR_VALUES];

	SDL_Event mEvent;

	lilTouch* mTouch;

	int mScreenWidth;
	int mScreenHeight;

private:
	bool LoadData();

	lilInputAbstractionLayer(const lilInputAbstractionLayer& input) {}
	void operator=(const lilInputAbstractionLayer& input) {}
};

