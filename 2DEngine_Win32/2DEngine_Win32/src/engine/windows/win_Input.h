//
//  2DEngine
//  win_Input.h
//  Eric Fleming
//  4/2/2018
//

#pragma once

#include <SDL.h>

#include "win_Mouse.h"
#include "win_Keyboard.h"
#include "win_GameController.h"

const int MAX_GAME_CONTROLLERS = 4;

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
	bool Initialize(int screenWidth, int screenHeight);

	// Updates input system
	void Update();

	// Closes all input devices and cleans up input system
	void Shutdown();

	// Get input state
	bool GetButton(std::string inputName);
	bool GetButtonDown(std::string inputName);
	CursorPosition* GetCursorPosition(std::string inputName);
	CursorPosition* GetCursorRelativePosition(std::string inputName);
	float GetValue(std::string inputName);


private:
	SDL_Event mEvent;

	lilMouse* mMouse;
	lilKeyboard* mKeyboard;
	lilGameController* mGameControllers[MAX_GAME_CONTROLLERS];
	unsigned mNumberOfControllers;

	int m_ScreenWidth;
	int m_ScreenHeight;

private:
	// No copying
	lilInputAbstractionLayer(const lilInputAbstractionLayer& input) {}
	void operator=(const lilInputAbstractionLayer& input) {}
};

