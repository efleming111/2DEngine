//
//  2DEngine
//  win_GameController.cpp
//  Eric Fleming
//  5/7/2018
//

#include "win_GameController.h"

bool lilGameController::Initialize(SDL_GameController* controller)
{
	mController = controller;
	if (!mController)
		return false;

	SetDeadZone(1000);

	for (int i = 0; i < NUMBER_OF_JOYSTICK_BUTTONS; ++i)
	{
		mButtons[i].pressed = false;
		mButtons[i].down = false;
	}

	return true;
}

void lilGameController::Update()
{
	for (int i = 0; i < NUMBER_OF_JOYSTICK_BUTTONS; ++i)
		mButtons[i].pressed = false;

	for (int i = 0; i < NUMBER_OF_JOYSTICK_BUTTONS; ++i)
		SetButton((JoystickButton)i, SDL_GameControllerGetButton(mController, (SDL_GameControllerButton)i));
}

void lilGameController::Shutdown()
{
	SDL_GameControllerClose(mController);
}

void lilGameController::SetDeadZone(int deadZone)
{
	if (deadZone > MAX_AXIS_ZONE)
		mDeadZone = MAX_AXIS_ZONE;

	else if (deadZone <= 0.0f)
		mDeadZone = 0;

	else
		mDeadZone = deadZone;
}

float lilGameController::GetAxis(JoystickAxis axis)
{
	int result = (int)SDL_GameControllerGetAxis(mController, (SDL_GameControllerAxis)axis);

	if (abs(result) > mDeadZone)
		return (float)result / (float)MAX_AXIS_ZONE;

	return  0.0f;
}

void lilGameController::SetButton(JoystickButton button, bool isPressed)
{
	if (isPressed)
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

bool lilGameController::GetButton(JoystickButton button)
{
	if (button > 0 && button < NUMBER_OF_JOYSTICK_BUTTONS)
		return mButtons[button].down;

	return false;
}

bool lilGameController::GetButtonDown(JoystickButton button)
{
	if (button > 0 && button < NUMBER_OF_JOYSTICK_BUTTONS)
		return mButtons[button].pressed;

	return false;
}

