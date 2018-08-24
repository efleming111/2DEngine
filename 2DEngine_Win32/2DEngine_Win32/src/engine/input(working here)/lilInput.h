//
//  2DEngine
//  lilInput.h
//  Eric Fleming
//  4/2/2018
//

#pragma once

#ifdef _WIN32
#include "../windows/win_Input.h"
#endif

#ifdef __ANDROID__
#include "../android/and_Input.h"
#endif

#include <string>
#include <vector>

#include <SDL.h>

enum KeyCode {
	KC_NO_CODE,
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

enum MouseButton {
	NO_MB,
	MB_LEFT, MB_MIDDLE, MB_RIGHT,
	MB_X1, MB_X2,
	NUMBER_OF_MOUSE_BUTTONS
};

enum JoystickButton {
	NO_JB,
	JB_A = SDL_CONTROLLER_BUTTON_A,
	JB_B = SDL_CONTROLLER_BUTTON_B,
	JB_X = SDL_CONTROLLER_BUTTON_X,
	JB_Y = SDL_CONTROLLER_BUTTON_Y,
	JB_BACK = SDL_CONTROLLER_BUTTON_BACK,
	JB_GUIDE = SDL_CONTROLLER_BUTTON_GUIDE,
	JB_START = SDL_CONTROLLER_BUTTON_START,
	JB_LEFTSTICK = SDL_CONTROLLER_BUTTON_LEFTSTICK,
	JB_RIGHTSTICK = SDL_CONTROLLER_BUTTON_RIGHTSTICK,
	JB_LEFTSHOULDER = SDL_CONTROLLER_BUTTON_LEFTSHOULDER,
	JB_RIGHTSHOULDER = SDL_CONTROLLER_BUTTON_RIGHTSHOULDER,
	JB_DPADUP = SDL_CONTROLLER_BUTTON_DPAD_UP,
	JB_DPADDOWN = SDL_CONTROLLER_BUTTON_DPAD_DOWN,
	JB_DPADLEFT = SDL_CONTROLLER_BUTTON_DPAD_LEFT,
	JB_DPADRIGHT = SDL_CONTROLLER_BUTTON_DPAD_RIGHT,
	NUMBER_OF_JOYSTICK_BUTTONS = 15,
	JB_INVALID = SDL_CONTROLLER_BUTTON_INVALID
};

struct UserDefinedInput
{
	std::string name;
	std::vector<KeyCode> keyboardCodes;
	MouseButton mouseButtonCode;
	JoystickButton joystickButtonCode;
};

#define lilInput laInput::Instance()

class laInput
{
public:
	// Return only instance of class
	static laInput* Instance();

	// Creates input system
	bool Initialize();

	// Updates input system
	void Update();

	// Closes all input devices and cleans up input system
	void Shutdown();

private:
	static laInput* s_Instance;

	SDL_Event m_Event;

	int m_ScreenWidth;
	int m_ScreenHeight;

	std::vector<UserDefinedInput*> mUserInput;

private:
	bool LoadData();

	// Only one instance of class and no copying
	laInput();
	~laInput() {}
	laInput(const laInput& input) {}
	void operator=(const laInput& input) {}
};

