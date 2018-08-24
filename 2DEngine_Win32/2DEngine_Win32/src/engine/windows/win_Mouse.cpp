//
//  2DEngine
//  win_Mouse.cpp
//  Eric Fleming
//  4/2/2018
//

#include <SDL.h>

#include "win_Mouse.h"
#include "../renderer/lilGLWindow.h"

bool lilMouse::Initialize()
{
	for (int i = 0; i < NUMBER_OF_MOUSE_BUTTONS; ++i)
	{
		mButtons[i].pressed = false;
		mButtons[i].down = false;
	}

	mWheel = 0.0f;

	int x = 0;
	int y = 0;
	SDL_PumpEvents();
	SDL_GetMouseState(&x, &y);

	mX = float(x);
	mY = float(y);
	mRelX = 0.0f;
	mRelY = 0.0f;

	return true;
}

void lilMouse::Update()
{
	for (int i = 0; i < NUMBER_OF_MOUSE_BUTTONS; ++i)
		mButtons[i].pressed = false;

	mRelX = 0.0f;
	mRelY = 0.0f;

	mWheel = 0.0f;
}

void lilMouse::UpdateButtonDown(SDL_Event* input)
{
	switch (input->button.button)
	{
	case SDL_BUTTON_LEFT: SetButton(MB_LEFT, true); break;
	case SDL_BUTTON_MIDDLE: SetButton(MB_MIDDLE, true); break;
	case SDL_BUTTON_RIGHT: SetButton(MB_RIGHT, true); break;
	case SDL_BUTTON_X1: SetButton(MB_X1, true); break;
	case SDL_BUTTON_X2: SetButton(MB_X2, true); break;
	}
}

void lilMouse::UpdateButtonUp(SDL_Event* input)
{
	switch (input->button.button)
	{
	case SDL_BUTTON_LEFT: SetButton(MB_LEFT, false); break;
	case SDL_BUTTON_MIDDLE: SetButton(MB_MIDDLE, false); break;
	case SDL_BUTTON_RIGHT: SetButton(MB_RIGHT, false); break;
	case SDL_BUTTON_X1: SetButton(MB_X1, false); break;
	case SDL_BUTTON_X2: SetButton(MB_X2, false); break;
	}
}

void lilMouse::SetButton(MouseButton button, bool state)
{
	if (state)
	{
		if (!mButtons[button].down)
		{
			mButtons[button].pressed = true;
			mButtons[button].down = true;
		}
	}

	else
	{
		mButtons[button].pressed = false;
		mButtons[button].down = false;
	}
}

bool lilMouse::GetButton(MouseButton button)
{
	if (button >= 0 && button < NUMBER_OF_MOUSE_BUTTONS)
	{
		return mButtons[button].down;
	}

	return false;
}

bool lilMouse::GetButtonDown(MouseButton button)
{
	if (button >= 0 && button < NUMBER_OF_MOUSE_BUTTONS)
	{
		return mButtons[button].pressed;
	}

	return false;
}

void lilMouse::SetPosition(float x, float y)
{
	mX = x;
	mY = y;
}

void lilMouse::SetRelativePosition(float x, float y)
{
	mRelX = x;
	mRelY = y;
}

void lilMouse::SetWheel(float value)
{
	mWheel = value;
}

void lilMouse::RelativeMode(bool value)
{
	if (value)
	{
		lilGLWindow->ShowCursor(false);
		SDL_SetRelativeMouseMode(SDL_TRUE);
	}

	else
	{
		lilGLWindow->ShowCursor(true);
		SDL_SetRelativeMouseMode(SDL_FALSE);
	}
}
