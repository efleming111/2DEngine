//
//  2DEngine
//  win_Keyboard.cpp
//  Eric Fleming
//  4/2/2018
//

#include "win_Keyboard.h"

bool lilKeyboard::Initialize()
{
	for (int i = 0; i < NUMBER_OF_KEYS; ++i)
	{
		mKeys[i].pressed = false;
		mKeys[i].down = false;
	}

	return true;
}

void lilKeyboard::Update()
{
	for (int i = 0; i < NUMBER_OF_KEYS; ++i)
		mKeys[i].pressed = false;
}

void lilKeyboard::UpdateKeyDown(SDL_Event* input)
{
	switch (input->key.keysym.sym)
	{
	case SDLK_0: SetKey(KC_0, true); break;
	case SDLK_1: SetKey(KC_1, true); break;
	case SDLK_2: SetKey(KC_2, true); break;
	case SDLK_3: SetKey(KC_3, true); break;
	case SDLK_4: SetKey(KC_4, true); break;
	case SDLK_5: SetKey(KC_5, true); break;
	case SDLK_6: SetKey(KC_6, true); break;
	case SDLK_7: SetKey(KC_7, true); break;
	case SDLK_8: SetKey(KC_8, true); break;
	case SDLK_9: SetKey(KC_9, true); break;
	case SDLK_a: SetKey(KC_A, true); break;
	case SDLK_QUOTE: SetKey(KC_QUOTE, true); break;
	case SDLK_b: SetKey(KC_B, true); break;
	case SDLK_BACKSLASH: SetKey(KC_BACKSLASH, true); break;
	case SDLK_BACKSPACE: SetKey(KC_BACKSPACE, true); break;
	case SDLK_c: SetKey(KC_C, true); break;
	case SDLK_CAPSLOCK: SetKey(KC_CAPSLOCK, true); break;
	case SDLK_COMMA: SetKey(KC_COMMA, true); break;
	case SDLK_d: SetKey(KC_D, true); break;
	case SDLK_DELETE: SetKey(KC_DELETE, true); break;
	case SDLK_DOWN: SetKey(KC_DOWNARROW, true); break;
	case SDLK_e: SetKey(KC_E, true); break;
	case SDLK_END: SetKey(KC_END, true); break;
	case SDLK_EQUALS: SetKey(KC_EQUALS, true); break;
	case SDLK_ESCAPE: SetKey(KC_ESCAPE, true); break;
	case SDLK_f: SetKey(KC_F, true); break;
	case SDLK_F1: SetKey(KC_F1, true); break;
	case SDLK_F10: SetKey(KC_10, true); break;
	case SDLK_F11: SetKey(KC_11, true); break;
	case SDLK_F12: SetKey(KC_12, true); break;
	case SDLK_F2: SetKey(KC_F2, true); break;
	case SDLK_F3: SetKey(KC_F3, true); break;
	case SDLK_F4: SetKey(KC_F4, true); break;
	case SDLK_F5: SetKey(KC_F5, true); break;
	case SDLK_F6: SetKey(KC_F6, true); break;
	case SDLK_F7: SetKey(KC_F7, true); break;
	case SDLK_F8: SetKey(KC_F8, true); break;
	case SDLK_F9: SetKey(KC_F9, true); break;
	case SDLK_g: SetKey(KC_G, true); break;
	case SDLK_BACKQUOTE: SetKey(KC_BACKQUOTE, true); break;
	case SDLK_h: SetKey(KC_H, true); break;
	case SDLK_HOME: SetKey(KC_HOME, true); break;
	case SDLK_i: SetKey(KC_I, true); break;
	case SDLK_INSERT: SetKey(KC_INSERT, true); break;
	case SDLK_j: SetKey(KC_J, true); break;
	case SDLK_k: SetKey(KC_K, true); break;
	case SDLK_KP_0: SetKey(KC_KEYPAD_0, true); break;
	case SDLK_KP_1: SetKey(KC_KEYPAD_1, true); break;
	case SDLK_KP_2: SetKey(KC_KEYPAD_2, true); break;
	case SDLK_KP_3: SetKey(KC_KEYPAD_3, true); break;
	case SDLK_KP_4: SetKey(KC_KEYPAD_4, true); break;
	case SDLK_KP_5: SetKey(KC_KEYPAD_5, true); break;
	case SDLK_KP_6: SetKey(KC_KEYPAD_6, true); break;
	case SDLK_KP_7: SetKey(KC_KEYPAD_7, true); break;
	case SDLK_KP_8: SetKey(KC_KEYPAD_8, true); break;
	case SDLK_KP_9: SetKey(KC_KEYPAD_9, true); break;
	case SDLK_KP_DIVIDE: SetKey(KC_KEYPAD_DIVIDE, true); break;
	case SDLK_KP_ENTER: SetKey(KC_KEYPAD_ENTER, true); break;
	case SDLK_KP_MINUS: SetKey(KC_KEYPAD_MINUS, true); break;
	case SDLK_KP_MULTIPLY: SetKey(KC_KEYPAD_MULTIPLY, true); break;
	case SDLK_KP_PERIOD: SetKey(KC_KEYPAD_PERIOD, true); break;
	case SDLK_KP_PLUS: SetKey(KC_KEYPAD_PLUS, true); break;
	case SDLK_l: SetKey(KC_L, true); break;
	case SDLK_LALT: SetKey(KC_LEFTALT, true); break;
	case SDLK_LCTRL: SetKey(KC_LEFTCONTROL, true); break;
	case SDLK_LEFT: SetKey(KC_LEFTARROW, true); break;
	case SDLK_LEFTBRACKET: SetKey(KC_LEFTBRACKET, true); break;
	case SDLK_LSHIFT: SetKey(KC_LEFTSHIFT, true); break;
	case SDLK_m: SetKey(KC_M, true); break;
	case SDLK_MINUS: SetKey(KC_MINUS, true); break;
	case SDLK_n: SetKey(KC_N, true); break;
	case SDLK_NUMLOCKCLEAR: SetKey(KC_NUMBERLOCK, true); break;
	case SDLK_o: SetKey(KC_O, true); break;
	case SDLK_p: SetKey(KC_P, true); break;
	case SDLK_PAGEDOWN: SetKey(KC_PAGEDOWN, true); break;
	case SDLK_PAGEUP: SetKey(KC_PAGEUP, true); break;
	case SDLK_PAUSE: SetKey(KC_PAUSE, true); break;
	case SDLK_PERIOD: SetKey(KC_PERIOD, true); break;
	case SDLK_PRINTSCREEN: SetKey(KC_PRINTSCREEN, true); break;
	case SDLK_q: SetKey(KC_Q, true); break;
	case SDLK_r: SetKey(KC_R, true); break;
	case SDLK_RALT: SetKey(KC_RIGHTALT, true); break;
	case SDLK_RCTRL: SetKey(KC_RIGHTCONTROL, true); break;
	case SDLK_RETURN: SetKey(KC_ENTER, true); break;
	case SDLK_RIGHT: SetKey(KC_RIGHTARROW, true); break;
	case SDLK_RIGHTBRACKET: SetKey(KC_RIGHTBRACKET, true); break;
	case SDLK_RSHIFT: SetKey(KC_RIGHTSHIFT, true); break;
	case SDLK_s: SetKey(KC_S, true); break;
	case SDLK_SCROLLLOCK: SetKey(KC_SCROLLLOCK, true); break;
	case SDLK_SEMICOLON: SetKey(KC_SEMICOLON, true); break;
	case SDLK_SLASH: SetKey(KC_SLASH, true); break;
	case SDLK_SPACE: SetKey(KC_SPACE, true); break;
	case SDLK_t: SetKey(KC_T, true); break;
	case SDLK_TAB: SetKey(KC_TAB, true); break;
	case SDLK_u: SetKey(KC_U, true); break;
	case SDLK_UP: SetKey(KC_UPARROW, true); break;
	case SDLK_v: SetKey(KC_V, true); break;
	case SDLK_w: SetKey(KC_W, true); break;
	case SDLK_x: SetKey(KC_X, true); break;
	case SDLK_y: SetKey(KC_Y, true); break;
	case SDLK_z: SetKey(KC_Z, true); break;
	}
}

void lilKeyboard::UpdateKeyUp(SDL_Event* input)
{
	switch (input->key.keysym.sym)
	{
	case SDLK_0: SetKey(KC_0, false); break;
	case SDLK_1: SetKey(KC_1, false); break;
	case SDLK_2: SetKey(KC_2, false); break;
	case SDLK_3: SetKey(KC_3, false); break;
	case SDLK_4: SetKey(KC_4, false); break;
	case SDLK_5: SetKey(KC_5, false); break;
	case SDLK_6: SetKey(KC_6, false); break;
	case SDLK_7: SetKey(KC_7, false); break;
	case SDLK_8: SetKey(KC_8, false); break;
	case SDLK_9: SetKey(KC_9, false); break;
	case SDLK_a: SetKey(KC_A, false); break;
	case SDLK_QUOTE: SetKey(KC_QUOTE, false); break;
	case SDLK_b: SetKey(KC_B, false); break;
	case SDLK_BACKSLASH: SetKey(KC_BACKSLASH, false); break;
	case SDLK_BACKSPACE: SetKey(KC_BACKSPACE, false); break;
	case SDLK_c: SetKey(KC_C, false); break;
	case SDLK_CAPSLOCK: SetKey(KC_CAPSLOCK, false); break;
	case SDLK_COMMA: SetKey(KC_COMMA, false); break;
	case SDLK_d: SetKey(KC_D, false); break;
	case SDLK_DELETE: SetKey(KC_DELETE, false); break;
	case SDLK_DOWN: SetKey(KC_DOWNARROW, false); break;
	case SDLK_e: SetKey(KC_E, false); break;
	case SDLK_END: SetKey(KC_END, false); break;
	case SDLK_EQUALS: SetKey(KC_EQUALS, false); break;
	case SDLK_ESCAPE: SetKey(KC_ESCAPE, false); break;
	case SDLK_f: SetKey(KC_F, false); break;
	case SDLK_F1: SetKey(KC_F1, false); break;
	case SDLK_F10: SetKey(KC_10, false); break;
	case SDLK_F11: SetKey(KC_11, false); break;
	case SDLK_F12: SetKey(KC_12, false); break;
	case SDLK_F2: SetKey(KC_F2, false); break;
	case SDLK_F3: SetKey(KC_F3, false); break;
	case SDLK_F4: SetKey(KC_F4, false); break;
	case SDLK_F5: SetKey(KC_F5, false); break;
	case SDLK_F6: SetKey(KC_F6, false); break;
	case SDLK_F7: SetKey(KC_F7, false); break;
	case SDLK_F8: SetKey(KC_F8, false); break;
	case SDLK_F9: SetKey(KC_F9, false); break;
	case SDLK_g: SetKey(KC_G, false); break;
	case SDLK_BACKQUOTE: SetKey(KC_BACKQUOTE, false); break;
	case SDLK_h: SetKey(KC_H, false); break;
	case SDLK_HOME: SetKey(KC_HOME, false); break;
	case SDLK_i: SetKey(KC_I, false); break;
	case SDLK_INSERT: SetKey(KC_INSERT, false); break;
	case SDLK_j: SetKey(KC_J, false); break;
	case SDLK_k: SetKey(KC_K, false); break;
	case SDLK_KP_0: SetKey(KC_KEYPAD_0, false); break;
	case SDLK_KP_1: SetKey(KC_KEYPAD_1, false); break;
	case SDLK_KP_2: SetKey(KC_KEYPAD_2, false); break;
	case SDLK_KP_3: SetKey(KC_KEYPAD_3, false); break;
	case SDLK_KP_4: SetKey(KC_KEYPAD_4, false); break;
	case SDLK_KP_5: SetKey(KC_KEYPAD_5, false); break;
	case SDLK_KP_6: SetKey(KC_KEYPAD_6, false); break;
	case SDLK_KP_7: SetKey(KC_KEYPAD_7, false); break;
	case SDLK_KP_8: SetKey(KC_KEYPAD_8, false); break;
	case SDLK_KP_9: SetKey(KC_KEYPAD_9, false); break;
	case SDLK_KP_DIVIDE: SetKey(KC_KEYPAD_DIVIDE, false); break;
	case SDLK_KP_ENTER: SetKey(KC_KEYPAD_ENTER, false); break;
	case SDLK_KP_MINUS: SetKey(KC_KEYPAD_MINUS, false); break;
	case SDLK_KP_MULTIPLY: SetKey(KC_KEYPAD_MULTIPLY, false); break;
	case SDLK_KP_PERIOD: SetKey(KC_KEYPAD_PERIOD, false); break;
	case SDLK_KP_PLUS: SetKey(KC_KEYPAD_PLUS, false); break;
	case SDLK_l: SetKey(KC_L, false); break;
	case SDLK_LALT: SetKey(KC_LEFTALT, false); break;
	case SDLK_LCTRL: SetKey(KC_LEFTCONTROL, false); break;
	case SDLK_LEFT: SetKey(KC_LEFTARROW, false); break;
	case SDLK_LEFTBRACKET: SetKey(KC_LEFTBRACKET, false); break;
	case SDLK_LSHIFT: SetKey(KC_LEFTSHIFT, false); break;
	case SDLK_m: SetKey(KC_M, false); break;
	case SDLK_MINUS: SetKey(KC_MINUS, false); break;
	case SDLK_n: SetKey(KC_N, false); break;
	case SDLK_NUMLOCKCLEAR: SetKey(KC_NUMBERLOCK, false); break;
	case SDLK_o: SetKey(KC_O, false); break;
	case SDLK_p: SetKey(KC_P, false); break;
	case SDLK_PAGEDOWN: SetKey(KC_PAGEDOWN, false); break;
	case SDLK_PAGEUP: SetKey(KC_PAGEUP, false); break;
	case SDLK_PAUSE: SetKey(KC_PAUSE, false); break;
	case SDLK_PERIOD: SetKey(KC_PERIOD, false); break;
	case SDLK_PRINTSCREEN: SetKey(KC_PRINTSCREEN, false); break;
	case SDLK_q: SetKey(KC_Q, false); break;
	case SDLK_r: SetKey(KC_R, false); break;
	case SDLK_RALT: SetKey(KC_RIGHTALT, false); break;
	case SDLK_RCTRL: SetKey(KC_RIGHTCONTROL, false); break;
	case SDLK_RETURN: SetKey(KC_ENTER, false); break;
	case SDLK_RIGHT: SetKey(KC_RIGHTARROW, false); break;
	case SDLK_RIGHTBRACKET: SetKey(KC_RIGHTBRACKET, false); break;
	case SDLK_RSHIFT: SetKey(KC_RIGHTSHIFT, false); break;
	case SDLK_s: SetKey(KC_S, false); break;
	case SDLK_SCROLLLOCK: SetKey(KC_SCROLLLOCK, false); break;
	case SDLK_SEMICOLON: SetKey(KC_SEMICOLON, false); break;
	case SDLK_SLASH: SetKey(KC_SLASH, false); break;
	case SDLK_SPACE: SetKey(KC_SPACE, false); break;
	case SDLK_t: SetKey(KC_T, false); break;
	case SDLK_TAB: SetKey(KC_TAB, false); break;
	case SDLK_u: SetKey(KC_U, false); break;
	case SDLK_UP: SetKey(KC_UPARROW, false); break;
	case SDLK_v: SetKey(KC_V, false); break;
	case SDLK_w: SetKey(KC_W, false); break;
	case SDLK_x: SetKey(KC_X, false); break;
	case SDLK_y: SetKey(KC_Y, false); break;
	case SDLK_z: SetKey(KC_Z, false); break;
	}
}

void lilKeyboard::SetKey(KeyCode keyCode, bool isPressed)
{
	if (isPressed)
	{
		if (!mKeys[keyCode].down)
		{
			mKeys[keyCode].pressed = true;
			mKeys[keyCode].down = true;
		}
	}

	else
	{
		mKeys[keyCode].pressed = false;
		mKeys[keyCode].down = false;
	}
}


bool lilKeyboard::GetKey(KeyCode keyCode) const
{
	if (keyCode >= 0 && keyCode < NUMBER_OF_KEYS)
	{
		return mKeys[keyCode].down;
	}

	return false;
}

bool lilKeyboard::GetKeyDown(KeyCode keyCode) const
{
	if (keyCode >= 0 && keyCode < NUMBER_OF_KEYS)
	{
		return mKeys[keyCode].pressed;
	}

	return false;
}

