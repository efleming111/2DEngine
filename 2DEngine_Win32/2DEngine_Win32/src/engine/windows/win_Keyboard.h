//
//  2DEngine
//  win_Keyboard.h
//  Eric Fleming
//  4/2/2018
//

#pragma once

#include <SDL.h>

#include "../input/lilInputDefines.h"

class lilKeyboard
{
public:
	lilKeyboard() {}
	~lilKeyboard() {}

	// Sets up keyboard
	bool Initialize();

	// Updates frame of key press
	void Update();

	// Updates key press
	void UpdateKeyDown(SDL_Event* input);

	// Updates key release
	void UpdateKeyUp(SDL_Event* input);

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

	Key mKeys[NUMBER_OF_KEYS];

private:
	// No copying
	lilKeyboard(const lilKeyboard& keyboard) {}
	lilKeyboard& operator=(const lilKeyboard& keyboard) {}
};

