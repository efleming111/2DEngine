//
//  2DEngine
//  EKeyboard.h
//  Eric Fleming
//  4/2/2018
//

#pragma once

enum KeyCode {
	KC_ESCAPE, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_10, KC_11, KC_12,
	KC_BACKQUOTE, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINUS, KC_EQUALS, KC_BACKSPACE,
	KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LEFTBRACKET, KC_RIGHTBRACKET, KC_BACKSLASH,
	KC_CAPSLOCK, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SEMICOLON, KC_QUOTE, KC_ENTER,
	KC_LEFTSHIFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMMA, KC_PERIOD, KC_SLASH, KC_RIGHTSHIFT,
	KC_LEFTCONTROL, KC_LEFTALT, KC_SPACE, KC_RIGHTALT, KC_RIGHTCONTROL,
	KC_INSERT, KC_HOME, KC_PAGEUP, KC_DELETE, KC_END, KC_PAGEDOWN,
	KC_LEFTARROW, KC_UPARROW, KC_DOWNARROW, KC_RIGHTARROW,
	KC_NUMBERLOCK, KC_KEYPAD_DIVIDE, KC_KEYPAD_MULTIPLY, KC_KEYPAD_MINUS,
	KC_KEYPAD_7, KC_KEYPAD_8, KC_KEYPAD_9, KC_KEYPAD_PLUS,
	KC_KEYPAD_4, KC_KEYPAD_5, KC_KEYPAD_6,
	KC_KEYPAD_1, KC_KEYPAD_2, KC_KEYPAD_3, KC_KEYPAD_ENTER,
	KC_KEYPAD_0, KC_KEYPAD_PERIOD,
	KC_PRINTSCREEN, KC_SCROLLLOCK, KC_PAUSE,
	NUMBER_OF_KEYS
};

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

