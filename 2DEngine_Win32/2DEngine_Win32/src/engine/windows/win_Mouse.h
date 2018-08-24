//
//  2DEngine
//  win_Mouse.h
//  Eric Fleming
//  4/2/2018
//

#pragma once

#include "../input/lilInputDefines.h"

class lilMouse
{
public:
	lilMouse() {}
	~lilMouse() {}

	// Sets up mouse
	bool Initialize();

	// Updates frame of button press
	void Update();

	// Updates button press
	void UpdateButtonDown(SDL_Event* input);

	// Updates button release
	void UpdateButtonUp(SDL_Event* input);

	// Set weather a mouse button is pressed
	// @ whichButton - which button is being set
	// @ buttonState - true if pressed
	void SetButton(MouseButton button, bool state);

	// Returns weather a mouse button is pressed
	// @ button - which button is being queried
	bool GetButton(MouseButton button);

	// Returns true in the frame in which the button was pressed
	// @ button - which button is being queried
	bool GetButtonDown(MouseButton button);

	// Sets the current position of the mouse
	// @ x - current x position
	// @ y - current y position
	void SetPosition(float x, float y);

	// Sets the relative position of the mouse
	// @ x - x position relative to last frame
	// @ y - y position relative to last frame
	void SetRelativePosition(float x, float y);

	// Returns the x position of the mouse
	float X() const { return mX; }

	// Returns the y position of the mouse
	float Y() const { return mY; }

	// Returns the x relative position of the mouse
	float RelX() const { return mRelX; }

	// Returns the y relative position of the mouse
	float RelY() const { return mRelY; }

	// Sets the wheel movement value
	void SetWheel(float value);

	// Returns the current value of the mouse wheel
	float Wheel() const { return mWheel; }

	// Sets if mouse input will be read after mouse leaves window
	// If this is set to true, mouse cursor is hidden
	void RelativeMode(bool value);

private:
	struct Button
	{
		bool pressed;
		bool down;
	};

	Button mButtons[NUMBER_OF_MOUSE_BUTTONS];

	float mWheel;

	float mX;
	float mY;
	float mRelX;
	float mRelY;

private:
	// No copying
	lilMouse(const lilMouse& mouse) {}
	lilMouse& operator=(const lilMouse& mouse) {}
};

