//
//  2DEngine
//  EMouse.h
//  Eric Fleming
//  4/2/2018
//

#pragma once




class EMouse
{
public:
	EMouse() {}
	~EMouse() {}

	// Sets up mouse
	bool Initialize();

	// Updates frame of button press
	void Update();

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
	float X() const { return m_X; }

	// Returns the y position of the mouse
	float Y() const { return m_Y; }

	// Returns the x relative position of the mouse
	float RelX() const { return m_RelX; }

	// Returns the y relative position of the mouse
	float RelY() const { return m_RelY; }

	// Sets the wheel movement value
	void SetWheel(float value);

	// Returns the current value of the mouse wheel
	float Wheel() const { return m_Wheel; }

	// Sets if mouse input will be read after mouse leaves window
	// If this is set to true, mouse cursor is hidden
	void RelativeMode(bool value);

private:
	struct Button
	{
		bool pressed;
		bool down;
	};

	Button m_Buttons[NUMBER_OF_MOUSE_BUTTONS];

	float m_Wheel;

	float m_X;
	float m_Y;
	float m_RelX;
	float m_RelY;

private:
	// No copying
	EMouse(const EMouse& mouse) {}
	EMouse& operator=(const EMouse& mouse) {}
};

