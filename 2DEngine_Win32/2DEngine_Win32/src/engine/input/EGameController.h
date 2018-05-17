//
//  2DEngine
//  EGameController.h
//  Eric Fleming
//  5/7/2018
//

#pragma once

#include <SDL.h>

enum JoystickAxis {
	JSA_LEFTX = SDL_CONTROLLER_AXIS_LEFTX,
	JSA_LEFTY = SDL_CONTROLLER_AXIS_LEFTY,
	JSA_RIGHTX = SDL_CONTROLLER_AXIS_RIGHTX,
	JSA_RIGHTY = SDL_CONTROLLER_AXIS_RIGHTY,
	JSA_TRIGGERLEFT = SDL_CONTROLLER_AXIS_TRIGGERLEFT,
	JSA_TRIGGERRIGHT = SDL_CONTROLLER_AXIS_TRIGGERRIGHT,
	JOYSTICK_AXIS_INVALID = SDL_CONTROLLER_AXIS_INVALID
};

enum JoystickButton {
	JB_ABUTTON = SDL_CONTROLLER_BUTTON_A,
	JB_BBUTTON = SDL_CONTROLLER_BUTTON_B,
	JB_XBUTTON = SDL_CONTROLLER_BUTTON_X,
	JB_YBUTTON = SDL_CONTROLLER_BUTTON_Y,
	JB_BACKBUTTON = SDL_CONTROLLER_BUTTON_BACK,
	JB_GUIDEBUTTON = SDL_CONTROLLER_BUTTON_GUIDE,
	JB_STARTBUTTON = SDL_CONTROLLER_BUTTON_START,
	JB_LEFTSTICKBUTTON = SDL_CONTROLLER_BUTTON_LEFTSTICK,
	JB_RIGHTSTICKBUTTON = SDL_CONTROLLER_BUTTON_RIGHTSTICK,
	JB_LEFTSHOULDERBUTTON = SDL_CONTROLLER_BUTTON_LEFTSHOULDER,
	JB_RIGHTSHOULDERBUTTON = SDL_CONTROLLER_BUTTON_RIGHTSHOULDER,
	JB_DPADUP = SDL_CONTROLLER_BUTTON_DPAD_UP,
	JB_DPADDOWN = SDL_CONTROLLER_BUTTON_DPAD_DOWN,
	JB_DPADLEFT = SDL_CONTROLLER_BUTTON_DPAD_LEFT,
	JB_DPADRIGHT = SDL_CONTROLLER_BUTTON_DPAD_RIGHT,
	NUMBER_OF_JOYSTICK_BUTTONS = 15,
	JB_BUTTON_INVALID = SDL_CONTROLLER_BUTTON_INVALID
};

class EGameController
{
public:
	EGameController() {}
	~EGameController() {}

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

	SDL_GameController* m_Controller;

	int m_DeadZone;

	Button m_Buttons[NUMBER_OF_JOYSTICK_BUTTONS];

private:
	// No copying
	EGameController(const EGameController& controller) {}
	void operator=(const EGameController& controller) {}
};

