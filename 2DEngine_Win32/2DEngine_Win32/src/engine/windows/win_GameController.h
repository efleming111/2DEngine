//
//  2DEngine
//  win_GameController.h
//  Eric Fleming
//  5/7/2018
//

#pragma once

#include <SDL.h>

#include "../input/lilInputDefines.h"

class lilGameController
{
public:
	lilGameController() {}
	~lilGameController() {}

	// Initializes joystick
	// @ controller - pointer to the controller 
	bool Initialize(SDL_GameController* controller);

	// Updates per frame of button press
	void Update();

	// Shuts down and cleans up joystick
	void Shutdown();

	// Sets the deadzone on the joystick sticks
	// @ deadZone - amount of dead zone
	void SetDeadZone(int deadZone);

	// Returns axis value of stick(in the range of -1 to 1)
	// @ axis - axis being queried
	float GetAxis(JoystickAxis axis);

	// Set weather this joystick's button is pressed
	// @ button - which button is being set
	// @ state - true if pressed
	void SetButton(JoystickButton button, bool isPressed);

	// Returns weather this joystick's button is pressed
	// @ button - which button is being queried
	bool GetButton(JoystickButton button);

	// Returns true in the frame in which the button was pressed
	// @ button - which button is being queried
	bool GetButtonDown(JoystickButton button);

private:
	const int MAX_AXIS_ZONE = 32767;

	struct Button
	{
		bool pressed;
		bool down;
	};

	SDL_GameController* mController;

	int mDeadZone;

	Button mButtons[NUMBER_OF_JOYSTICK_BUTTONS];

private:
	// No copying
	lilGameController(const lilGameController& controller) {}
	void operator=(const lilGameController& controller) {}
};

