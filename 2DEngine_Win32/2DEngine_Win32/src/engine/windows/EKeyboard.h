//
//  2DEngine
//  EKeyboard.h
//  Eric Fleming
//  4/2/2018
//

#pragma once



class EKeyboard
{
public:
	EKeyboard() {}
	~EKeyboard() {}

	// Sets up keyboard
	bool Initialize();

	// Updates frame of key press
	void Update();

	// Set state of key
	// @ keycode - key code of the key being set
	// @ isPressed - true when key is pressed
	void SetKey(KeyCode keyCode, bool isPressed);

	// Returns state of key
	// @ keyCode - key being queried
	bool GetKey(KeyCode keyCode) const;

	// Returns true during frame key is pressed
	// @ keyCode - key being queried
	bool GetKeyDown(KeyCode keyCode) const;

private:
	struct Key
	{
		bool pressed;
		bool down;
	};

	Key m_Keys[NUMBER_OF_KEYS];

private:
	// No copying
	EKeyboard(const EKeyboard& keyboard) {}
	EKeyboard& operator=(const EKeyboard& keyboard) {}
};

