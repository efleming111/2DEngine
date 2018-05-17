//
//  2DEngine
//  EMouse.cpp
//  Eric Fleming
//  4/2/2018
//

#include <SDL.h>

#include "EMouse.h"
#include "../renderer/EGLWindow.h"

bool EMouse::Initialize()
{
	for (int i = 0; i < NUMBER_OF_MOUSE_BUTTONS; ++i)
	{
		m_Buttons[i].pressed = false;
		m_Buttons[i].down = false;
	}

	m_Wheel = 0.0f;

	int x = 0;
	int y = 0;
	SDL_PumpEvents();
	SDL_GetMouseState(&x, &y);

	m_X = float(x);
	m_Y = float(y);
	m_RelX = 0.0f;
	m_RelY = 0.0f;

	return true;
}

void EMouse::Update()
{
	for (int i = 0; i < NUMBER_OF_MOUSE_BUTTONS; ++i)
		m_Buttons[i].pressed = false;

	m_RelX = 0.0f;
	m_RelY = 0.0f;

	m_Wheel = 0.0f;
}

void EMouse::SetButton(MouseButton button, bool state)
{
	if (state)
	{
		if (!m_Buttons[button].down)
		{
			m_Buttons[button].pressed = true;
			m_Buttons[button].down = true;
		}
	}

	else
	{
		m_Buttons[button].pressed = false;
		m_Buttons[button].down = false;
	}
}

bool EMouse::GetButton(MouseButton button)
{
	if (button >= 0 && button < NUMBER_OF_MOUSE_BUTTONS)
	{
		return m_Buttons[button].down;
	}

	return false;
}

bool EMouse::GetButtonDown(MouseButton button)
{
	if (button >= 0 && button < NUMBER_OF_MOUSE_BUTTONS)
	{
		return m_Buttons[button].pressed;
	}

	return false;
}

void EMouse::SetPosition(float x, float y)
{
	m_X = x;
	m_Y = y;
}

void EMouse::SetRelativePosition(float x, float y)
{
	m_RelX = x;
	m_RelY = y;
}

void EMouse::SetWheel(float value)
{
	m_Wheel = value;
}

void EMouse::RelativeMode(bool value)
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
