//
//  2DEngine
//  EGameController.cpp
//  Eric Fleming
//  5/7/2018
//

#include "EGameController.h"

bool EGameController::Initialize(SDL_GameController* controller)
{
	m_Controller = controller;
	if (!m_Controller)
		return false;

	SetDeadZone(1000);

	for (int i = 0; i < NUMBER_OF_JOYSTICK_BUTTONS; ++i)
	{
		m_Buttons[i].pressed = false;
		m_Buttons[i].down = false;
	}

	return true;
}

void EGameController::Update()
{
	for (int i = 0; i < NUMBER_OF_JOYSTICK_BUTTONS; ++i)
		m_Buttons[i].pressed = false;

	for (int i = 0; i < NUMBER_OF_JOYSTICK_BUTTONS; ++i)
		SetButton((JoystickButton)i, SDL_GameControllerGetButton(m_Controller, (SDL_GameControllerButton)i));
}

void EGameController::Shutdown()
{
	SDL_GameControllerClose(m_Controller);
}

void EGameController::SetDeadZone(int deadZone)
{
	if (deadZone > MAX_AXIS_ZONE)
		m_DeadZone = MAX_AXIS_ZONE;

	else if (deadZone <= 0.0f)
		m_DeadZone = 0;

	else
		m_DeadZone = deadZone;
}

float EGameController::GetAxis(JoystickAxis axis)
{
	int result = (int)SDL_GameControllerGetAxis(m_Controller, (SDL_GameControllerAxis)axis);

	if (abs(result) > m_DeadZone)
		return (float)result / (float)MAX_AXIS_ZONE;

	return  0.0f;
}

void EGameController::SetButton(JoystickButton button, bool isPressed)
{
	if (isPressed)
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

bool EGameController::GetButton(JoystickButton button)
{
	if (button >= 0 && button < NUMBER_OF_JOYSTICK_BUTTONS)
		return m_Buttons[button].down;

	return false;
}

bool EGameController::GetButtonDown(JoystickButton button)
{
	if (button >= 0 && button < NUMBER_OF_JOYSTICK_BUTTONS)
		return m_Buttons[button].pressed;

	return false;
}

