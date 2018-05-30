//
//  2DEngine
//  EInput.cpp
//  Eric Fleming
//  4/2/2018
//

#include "EInput.h"
#include "../renderer/EGLWindow.h"
#include "../renderer/EGLRenderer.h"
#include "../core/ECore.h"

EInput* EInput::s_Instance = 0;

EInput* EInput::Instance()
{
	if (!s_Instance)
		s_Instance = new EInput();

	return s_Instance;
}

bool EInput::Initialize()
{
	m_ScreenWidth = lilGLWindow->Width();
	m_ScreenHeight = lilGLWindow->Height();

#ifdef _WIN32
	m_Mouse = new EMouse();
	if (!m_Mouse->Initialize())
	{
		SDL_Log("ERROR: Mouse Failed To Initialize %s %d", __FILE__, __LINE__);
		return false;
	}

	m_Keyboard = new EKeyboard();
	if (!m_Keyboard->Initialize())
	{
		SDL_Log("ERROR: Keyboard Failed To Initialize %s %d", __FILE__, __LINE__);
		return false;
	}

	if (!SDL_WasInit(SDL_INIT_GAMECONTROLLER))
		SDL_InitSubSystem(SDL_INIT_GAMECONTROLLER);

	if (SDL_NumJoysticks() > 0)
	{
		for (int i = 0; i < SDL_NumJoysticks() && i < MAX_GAME_CONTROLLERS; ++i)
		{
			if (SDL_IsGameController(i))
			{
				SDL_GameController* controller = SDL_GameControllerOpen(i);
				if (controller)
				{
					EGameController* gameController = new EGameController();
					gameController->Initialize(controller);
					m_GameControllers[i] = gameController;
					m_NumberOfControllers = (unsigned)i + 1u;
				}
			}
		}
	}
#endif

#ifdef __ANDROID__
	m_Touch = new ETouch();
	if (!m_Touch->Initialize())
	{
		SDL_Log("ERROR: Touch Failed To Initialize %s %d", __FILE__, __LINE__);
		return false;
	}
#endif

	return true;
}

void EInput::Update()
{
	// Update key and button press states
#ifdef _WIN32
	m_Keyboard->Update();
	m_Mouse->Update();
	for (unsigned i = 0; i < m_NumberOfControllers; ++i)
		m_GameControllers[i]->Update();
#endif

	while (SDL_PollEvent(&m_Event))
	{
		switch (m_Event.type)
		{
		case SDL_QUIT:
			lilEngine->Quit();
			break;

#ifdef _WIN32
		case SDL_WINDOWEVENT:
			switch (m_Event.window.event)
			{
			case SDL_WINDOWEVENT_RESIZED:
			case SDL_WINDOWEVENT_SIZE_CHANGED:
				lilGLRenderer->ResizeViewport(m_Event.window.data1, m_Event.window.data2);
				break;
			}
			break;

		case SDL_KEYDOWN:
			switch (m_Event.key.keysym.sym)
			{
			case SDLK_0: m_Keyboard->SetKey(KC_0, true); break;
			case SDLK_1: m_Keyboard->SetKey(KC_1, true); break;
			case SDLK_2: m_Keyboard->SetKey(KC_2, true); break;
			case SDLK_3: m_Keyboard->SetKey(KC_3, true); break;
			case SDLK_4: m_Keyboard->SetKey(KC_4, true); break;
			case SDLK_5: m_Keyboard->SetKey(KC_5, true); break;
			case SDLK_6: m_Keyboard->SetKey(KC_6, true); break;
			case SDLK_7: m_Keyboard->SetKey(KC_7, true); break;
			case SDLK_8: m_Keyboard->SetKey(KC_8, true); break;
			case SDLK_9: m_Keyboard->SetKey(KC_9, true); break;
			case SDLK_a: m_Keyboard->SetKey(KC_A, true); break;
			case SDLK_QUOTE: m_Keyboard->SetKey(KC_QUOTE, true); break;
			case SDLK_b: m_Keyboard->SetKey(KC_B, true); break;
			case SDLK_BACKSLASH: m_Keyboard->SetKey(KC_BACKSLASH, true); break;
			case SDLK_BACKSPACE: m_Keyboard->SetKey(KC_BACKSPACE, true); break;
			case SDLK_c: m_Keyboard->SetKey(KC_C, true); break;
			case SDLK_CAPSLOCK: m_Keyboard->SetKey(KC_CAPSLOCK, true); break;
			case SDLK_COMMA: m_Keyboard->SetKey(KC_COMMA, true); break;
			case SDLK_d: m_Keyboard->SetKey(KC_D, true); break;
			case SDLK_DELETE: m_Keyboard->SetKey(KC_DELETE, true); break;
			case SDLK_DOWN: m_Keyboard->SetKey(KC_DOWNARROW, true); break;
			case SDLK_e: m_Keyboard->SetKey(KC_E, true); break;
			case SDLK_END: m_Keyboard->SetKey(KC_END, true); break;
			case SDLK_EQUALS: m_Keyboard->SetKey(KC_EQUALS, true); break;
			case SDLK_ESCAPE: m_Keyboard->SetKey(KC_ESCAPE, true); break;
			case SDLK_f: m_Keyboard->SetKey(KC_F, true); break;
			case SDLK_F1: m_Keyboard->SetKey(KC_F1, true); break;
			case SDLK_F10: m_Keyboard->SetKey(KC_10, true); break;
			case SDLK_F11: m_Keyboard->SetKey(KC_11, true); break;
			case SDLK_F12: m_Keyboard->SetKey(KC_12, true); break;
			case SDLK_F2: m_Keyboard->SetKey(KC_F2, true); break;
			case SDLK_F3: m_Keyboard->SetKey(KC_F3, true); break;
			case SDLK_F4: m_Keyboard->SetKey(KC_F4, true); break;
			case SDLK_F5: m_Keyboard->SetKey(KC_F5, true); break;
			case SDLK_F6: m_Keyboard->SetKey(KC_F6, true); break;
			case SDLK_F7: m_Keyboard->SetKey(KC_F7, true); break;
			case SDLK_F8: m_Keyboard->SetKey(KC_F8, true); break;
			case SDLK_F9: m_Keyboard->SetKey(KC_F9, true); break;
			case SDLK_g: m_Keyboard->SetKey(KC_G, true); break;
			case SDLK_BACKQUOTE: m_Keyboard->SetKey(KC_BACKQUOTE, true); break;
			case SDLK_h: m_Keyboard->SetKey(KC_H, true); break;
			case SDLK_HOME: m_Keyboard->SetKey(KC_HOME, true); break;
			case SDLK_i: m_Keyboard->SetKey(KC_I, true); break;
			case SDLK_INSERT: m_Keyboard->SetKey(KC_INSERT, true); break;
			case SDLK_j: m_Keyboard->SetKey(KC_J, true); break;
			case SDLK_k: m_Keyboard->SetKey(KC_K, true); break;
			case SDLK_KP_0: m_Keyboard->SetKey(KC_KEYPAD_0, true); break;
			case SDLK_KP_1: m_Keyboard->SetKey(KC_KEYPAD_1, true); break;
			case SDLK_KP_2: m_Keyboard->SetKey(KC_KEYPAD_2, true); break;
			case SDLK_KP_3: m_Keyboard->SetKey(KC_KEYPAD_3, true); break;
			case SDLK_KP_4: m_Keyboard->SetKey(KC_KEYPAD_4, true); break;
			case SDLK_KP_5: m_Keyboard->SetKey(KC_KEYPAD_5, true); break;
			case SDLK_KP_6: m_Keyboard->SetKey(KC_KEYPAD_6, true); break;
			case SDLK_KP_7: m_Keyboard->SetKey(KC_KEYPAD_7, true); break;
			case SDLK_KP_8: m_Keyboard->SetKey(KC_KEYPAD_8, true); break;
			case SDLK_KP_9: m_Keyboard->SetKey(KC_KEYPAD_9, true); break;
			case SDLK_KP_DIVIDE: m_Keyboard->SetKey(KC_KEYPAD_DIVIDE, true); break;
			case SDLK_KP_ENTER: m_Keyboard->SetKey(KC_KEYPAD_ENTER, true); break;
			case SDLK_KP_MINUS: m_Keyboard->SetKey(KC_KEYPAD_MINUS, true); break;
			case SDLK_KP_MULTIPLY: m_Keyboard->SetKey(KC_KEYPAD_MULTIPLY, true); break;
			case SDLK_KP_PERIOD: m_Keyboard->SetKey(KC_KEYPAD_PERIOD, true); break;
			case SDLK_KP_PLUS: m_Keyboard->SetKey(KC_KEYPAD_PLUS, true); break;
			case SDLK_l: m_Keyboard->SetKey(KC_L, true); break;
			case SDLK_LALT: m_Keyboard->SetKey(KC_LEFTALT, true); break;
			case SDLK_LCTRL: m_Keyboard->SetKey(KC_LEFTCONTROL, true); break;
			case SDLK_LEFT: m_Keyboard->SetKey(KC_LEFTARROW, true); break;
			case SDLK_LEFTBRACKET: m_Keyboard->SetKey(KC_LEFTBRACKET, true); break;
			case SDLK_LSHIFT: m_Keyboard->SetKey(KC_LEFTSHIFT, true); break;
			case SDLK_m: m_Keyboard->SetKey(KC_M, true); break;
			case SDLK_MINUS: m_Keyboard->SetKey(KC_MINUS, true); break;
			case SDLK_n: m_Keyboard->SetKey(KC_N, true); break;
			case SDLK_NUMLOCKCLEAR: m_Keyboard->SetKey(KC_NUMBERLOCK, true); break;
			case SDLK_o: m_Keyboard->SetKey(KC_O, true); break;
			case SDLK_p: m_Keyboard->SetKey(KC_P, true); break;
			case SDLK_PAGEDOWN: m_Keyboard->SetKey(KC_PAGEDOWN, true); break;
			case SDLK_PAGEUP: m_Keyboard->SetKey(KC_PAGEUP, true); break;
			case SDLK_PAUSE: m_Keyboard->SetKey(KC_PAUSE, true); break;
			case SDLK_PERIOD: m_Keyboard->SetKey(KC_PERIOD, true); break;
			case SDLK_PRINTSCREEN: m_Keyboard->SetKey(KC_PRINTSCREEN, true); break;
			case SDLK_q: m_Keyboard->SetKey(KC_Q, true); break;
			case SDLK_r: m_Keyboard->SetKey(KC_R, true); break;
			case SDLK_RALT: m_Keyboard->SetKey(KC_RIGHTALT, true); break;
			case SDLK_RCTRL: m_Keyboard->SetKey(KC_RIGHTCONTROL, true); break;
			case SDLK_RETURN: m_Keyboard->SetKey(KC_ENTER, true); break;
			case SDLK_RIGHT: m_Keyboard->SetKey(KC_RIGHTARROW, true); break;
			case SDLK_RIGHTBRACKET: m_Keyboard->SetKey(KC_RIGHTBRACKET, true); break;
			case SDLK_RSHIFT: m_Keyboard->SetKey(KC_RIGHTSHIFT, true); break;
			case SDLK_s: m_Keyboard->SetKey(KC_S, true); break;
			case SDLK_SCROLLLOCK: m_Keyboard->SetKey(KC_SCROLLLOCK, true); break;
			case SDLK_SEMICOLON: m_Keyboard->SetKey(KC_SEMICOLON, true); break;
			case SDLK_SLASH: m_Keyboard->SetKey(KC_SLASH, true); break;
			case SDLK_SPACE: m_Keyboard->SetKey(KC_SPACE, true); break;
			case SDLK_t: m_Keyboard->SetKey(KC_T, true); break;
			case SDLK_TAB: m_Keyboard->SetKey(KC_TAB, true); break;
			case SDLK_u: m_Keyboard->SetKey(KC_U, true); break;
			case SDLK_UP: m_Keyboard->SetKey(KC_UPARROW, true); break;
			case SDLK_v: m_Keyboard->SetKey(KC_V, true); break;
			case SDLK_w: m_Keyboard->SetKey(KC_W, true); break;
			case SDLK_x: m_Keyboard->SetKey(KC_X, true); break;
			case SDLK_y: m_Keyboard->SetKey(KC_Y, true); break;
			case SDLK_z: m_Keyboard->SetKey(KC_Z, true); break;
			}
			break;

		case SDL_KEYUP:
			switch (m_Event.key.keysym.sym)
			{
			case SDLK_0: m_Keyboard->SetKey(KC_0, false); break;
			case SDLK_1: m_Keyboard->SetKey(KC_1, false); break;
			case SDLK_2: m_Keyboard->SetKey(KC_2, false); break;
			case SDLK_3: m_Keyboard->SetKey(KC_3, false); break;
			case SDLK_4: m_Keyboard->SetKey(KC_4, false); break;
			case SDLK_5: m_Keyboard->SetKey(KC_5, false); break;
			case SDLK_6: m_Keyboard->SetKey(KC_6, false); break;
			case SDLK_7: m_Keyboard->SetKey(KC_7, false); break;
			case SDLK_8: m_Keyboard->SetKey(KC_8, false); break;
			case SDLK_9: m_Keyboard->SetKey(KC_9, false); break;
			case SDLK_a: m_Keyboard->SetKey(KC_A, false); break;
			case SDLK_QUOTE: m_Keyboard->SetKey(KC_QUOTE, false); break;
			case SDLK_b: m_Keyboard->SetKey(KC_B, false); break;
			case SDLK_BACKSLASH: m_Keyboard->SetKey(KC_BACKSLASH, false); break;
			case SDLK_BACKSPACE: m_Keyboard->SetKey(KC_BACKSPACE, false); break;
			case SDLK_c: m_Keyboard->SetKey(KC_C, false); break;
			case SDLK_CAPSLOCK: m_Keyboard->SetKey(KC_CAPSLOCK, false); break;
			case SDLK_COMMA: m_Keyboard->SetKey(KC_COMMA, false); break;
			case SDLK_d: m_Keyboard->SetKey(KC_D, false); break;
			case SDLK_DELETE: m_Keyboard->SetKey(KC_DELETE, false); break;
			case SDLK_DOWN: m_Keyboard->SetKey(KC_DOWNARROW, false); break;
			case SDLK_e: m_Keyboard->SetKey(KC_E, false); break;
			case SDLK_END: m_Keyboard->SetKey(KC_END, false); break;
			case SDLK_EQUALS: m_Keyboard->SetKey(KC_EQUALS, false); break;
			case SDLK_ESCAPE: m_Keyboard->SetKey(KC_ESCAPE, false); break;
			case SDLK_f: m_Keyboard->SetKey(KC_F, false); break;
			case SDLK_F1: m_Keyboard->SetKey(KC_F1, false); break;
			case SDLK_F10: m_Keyboard->SetKey(KC_10, false); break;
			case SDLK_F11: m_Keyboard->SetKey(KC_11, false); break;
			case SDLK_F12: m_Keyboard->SetKey(KC_12, false); break;
			case SDLK_F2: m_Keyboard->SetKey(KC_F2, false); break;
			case SDLK_F3: m_Keyboard->SetKey(KC_F3, false); break;
			case SDLK_F4: m_Keyboard->SetKey(KC_F4, false); break;
			case SDLK_F5: m_Keyboard->SetKey(KC_F5, false); break;
			case SDLK_F6: m_Keyboard->SetKey(KC_F6, false); break;
			case SDLK_F7: m_Keyboard->SetKey(KC_F7, false); break;
			case SDLK_F8: m_Keyboard->SetKey(KC_F8, false); break;
			case SDLK_F9: m_Keyboard->SetKey(KC_F9, false); break;
			case SDLK_g: m_Keyboard->SetKey(KC_G, false); break;
			case SDLK_BACKQUOTE: m_Keyboard->SetKey(KC_BACKQUOTE, false); break;
			case SDLK_h: m_Keyboard->SetKey(KC_H, false); break;
			case SDLK_HOME: m_Keyboard->SetKey(KC_HOME, false); break;
			case SDLK_i: m_Keyboard->SetKey(KC_I, false); break;
			case SDLK_INSERT: m_Keyboard->SetKey(KC_INSERT, false); break;
			case SDLK_j: m_Keyboard->SetKey(KC_J, false); break;
			case SDLK_k: m_Keyboard->SetKey(KC_K, false); break;
			case SDLK_KP_0: m_Keyboard->SetKey(KC_KEYPAD_0, false); break;
			case SDLK_KP_1: m_Keyboard->SetKey(KC_KEYPAD_1, false); break;
			case SDLK_KP_2: m_Keyboard->SetKey(KC_KEYPAD_2, false); break;
			case SDLK_KP_3: m_Keyboard->SetKey(KC_KEYPAD_3, false); break;
			case SDLK_KP_4: m_Keyboard->SetKey(KC_KEYPAD_4, false); break;
			case SDLK_KP_5: m_Keyboard->SetKey(KC_KEYPAD_5, false); break;
			case SDLK_KP_6: m_Keyboard->SetKey(KC_KEYPAD_6, false); break;
			case SDLK_KP_7: m_Keyboard->SetKey(KC_KEYPAD_7, false); break;
			case SDLK_KP_8: m_Keyboard->SetKey(KC_KEYPAD_8, false); break;
			case SDLK_KP_9: m_Keyboard->SetKey(KC_KEYPAD_9, false); break;
			case SDLK_KP_DIVIDE: m_Keyboard->SetKey(KC_KEYPAD_DIVIDE, false); break;
			case SDLK_KP_ENTER: m_Keyboard->SetKey(KC_KEYPAD_ENTER, false); break;
			case SDLK_KP_MINUS: m_Keyboard->SetKey(KC_KEYPAD_MINUS, false); break;
			case SDLK_KP_MULTIPLY: m_Keyboard->SetKey(KC_KEYPAD_MULTIPLY, false); break;
			case SDLK_KP_PERIOD: m_Keyboard->SetKey(KC_KEYPAD_PERIOD, false); break;
			case SDLK_KP_PLUS: m_Keyboard->SetKey(KC_KEYPAD_PLUS, false); break;
			case SDLK_l: m_Keyboard->SetKey(KC_L, false); break;
			case SDLK_LALT: m_Keyboard->SetKey(KC_LEFTALT, false); break;
			case SDLK_LCTRL: m_Keyboard->SetKey(KC_LEFTCONTROL, false); break;
			case SDLK_LEFT: m_Keyboard->SetKey(KC_LEFTARROW, false); break;
			case SDLK_LEFTBRACKET: m_Keyboard->SetKey(KC_LEFTBRACKET, false); break;
			case SDLK_LSHIFT: m_Keyboard->SetKey(KC_LEFTSHIFT, false); break;
			case SDLK_m: m_Keyboard->SetKey(KC_M, false); break;
			case SDLK_MINUS: m_Keyboard->SetKey(KC_MINUS, false); break;
			case SDLK_n: m_Keyboard->SetKey(KC_N, false); break;
			case SDLK_NUMLOCKCLEAR: m_Keyboard->SetKey(KC_NUMBERLOCK, false); break;
			case SDLK_o: m_Keyboard->SetKey(KC_O, false); break;
			case SDLK_p: m_Keyboard->SetKey(KC_P, false); break;
			case SDLK_PAGEDOWN: m_Keyboard->SetKey(KC_PAGEDOWN, false); break;
			case SDLK_PAGEUP: m_Keyboard->SetKey(KC_PAGEUP, false); break;
			case SDLK_PAUSE: m_Keyboard->SetKey(KC_PAUSE, false); break;
			case SDLK_PERIOD: m_Keyboard->SetKey(KC_PERIOD, false); break;
			case SDLK_PRINTSCREEN: m_Keyboard->SetKey(KC_PRINTSCREEN, false); break;
			case SDLK_q: m_Keyboard->SetKey(KC_Q, false); break;
			case SDLK_r: m_Keyboard->SetKey(KC_R, false); break;
			case SDLK_RALT: m_Keyboard->SetKey(KC_RIGHTALT, false); break;
			case SDLK_RCTRL: m_Keyboard->SetKey(KC_RIGHTCONTROL, false); break;
			case SDLK_RETURN: m_Keyboard->SetKey(KC_ENTER, false); break;
			case SDLK_RIGHT: m_Keyboard->SetKey(KC_RIGHTARROW, false); break;
			case SDLK_RIGHTBRACKET: m_Keyboard->SetKey(KC_RIGHTBRACKET, false); break;
			case SDLK_RSHIFT: m_Keyboard->SetKey(KC_RIGHTSHIFT, false); break;
			case SDLK_s: m_Keyboard->SetKey(KC_S, false); break;
			case SDLK_SCROLLLOCK: m_Keyboard->SetKey(KC_SCROLLLOCK, false); break;
			case SDLK_SEMICOLON: m_Keyboard->SetKey(KC_SEMICOLON, false); break;
			case SDLK_SLASH: m_Keyboard->SetKey(KC_SLASH, false); break;
			case SDLK_SPACE: m_Keyboard->SetKey(KC_SPACE, false); break;
			case SDLK_t: m_Keyboard->SetKey(KC_T, false); break;
			case SDLK_TAB: m_Keyboard->SetKey(KC_TAB, false); break;
			case SDLK_u: m_Keyboard->SetKey(KC_U, false); break;
			case SDLK_UP: m_Keyboard->SetKey(KC_UPARROW, false); break;
			case SDLK_v: m_Keyboard->SetKey(KC_V, false); break;
			case SDLK_w: m_Keyboard->SetKey(KC_W, false); break;
			case SDLK_x: m_Keyboard->SetKey(KC_X, false); break;
			case SDLK_y: m_Keyboard->SetKey(KC_Y, false); break;
			case SDLK_z: m_Keyboard->SetKey(KC_Z, false); break;
			}
			break;

		case SDL_MOUSEBUTTONDOWN:
			switch (m_Event.button.button)
			{
			case SDL_BUTTON_LEFT: m_Mouse->SetButton(MOUSE_BUTTON_LEFT, true); break;
			case SDL_BUTTON_MIDDLE: m_Mouse->SetButton(MOUSE_BUTTON_MIDDLE, true); break;
			case SDL_BUTTON_RIGHT: m_Mouse->SetButton(MOUSE_BUTTON_RIGHT, true); break;
			case SDL_BUTTON_X1: m_Mouse->SetButton(MOUSE_BUTTON_X1, true); break;
			case SDL_BUTTON_X2: m_Mouse->SetButton(MOUSE_BUTTON_X2, true); break;
			}
			break;

		case SDL_MOUSEBUTTONUP:
			switch (m_Event.button.button)
			{
			case SDL_BUTTON_LEFT: m_Mouse->SetButton(MOUSE_BUTTON_LEFT, false); break;
			case SDL_BUTTON_MIDDLE: m_Mouse->SetButton(MOUSE_BUTTON_MIDDLE, false); break;
			case SDL_BUTTON_RIGHT: m_Mouse->SetButton(MOUSE_BUTTON_RIGHT, false); break;
			case SDL_BUTTON_X1: m_Mouse->SetButton(MOUSE_BUTTON_X1, false); break;
			case SDL_BUTTON_X2: m_Mouse->SetButton(MOUSE_BUTTON_X2, false); break;
			}
			break;

		case SDL_MOUSEWHEEL:
			m_Mouse->SetWheel((float)m_Event.wheel.y);
			break;

		case SDL_MOUSEMOTION:
			m_Mouse->SetPosition((float)m_Event.motion.x, (float)(m_ScreenHeight - m_Event.motion.y));
			m_Mouse->SetRelativePosition((float)m_Event.motion.xrel, (float)(-m_Event.motion.yrel));
			break;
#endif

#ifdef __ANDROID__
		case SDL_FINGERDOWN:
			m_Touch->SetFingerTouch(m_Event.tfinger.fingerId, true, m_Event.tfinger.x, m_Event.tfinger.y);
			break;

		case SDL_FINGERMOTION:
			m_Touch->SetFingerTouch(m_Event.tfinger.fingerId, true, m_Event.tfinger.x, m_Event.tfinger.y);
			break;

		case SDL_FINGERUP:
			m_Touch->SetFingerTouch(m_Event.tfinger.fingerId, false, m_Event.tfinger.x, m_Event.tfinger.y);
			break;
#endif
		}
	}
}

void EInput::Shutdown()
{
#ifdef _WIN32
	delete m_Mouse;
	m_Mouse = 0;

	delete m_Keyboard;
	m_Keyboard = 0;

	for (unsigned i = 0; i < m_NumberOfControllers; ++i)
	{
		m_GameControllers[i]->Shutdown();
		delete m_GameControllers[i];
		m_GameControllers[i] = 0;
	}
#endif

#ifdef __ANDROID__
	delete m_Touch;
	m_Touch = 0;
#endif
}

EGameController* EInput::GetController(unsigned index)
{
	if (index < m_NumberOfControllers)
		return m_GameControllers[index];

	return 0;
}

EInput::EInput()
{
#ifdef _WIN32
	m_Mouse = 0;
	m_Keyboard = 0;
#endif

#ifdef __ANDROID__
	m_Touch = 0;
#endif
}

