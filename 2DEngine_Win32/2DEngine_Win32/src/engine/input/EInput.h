//
//  2DEngine
//  EInput.h
//  Eric Fleming
//  4/2/2018
//

#pragma once

#include <vector>

#include <SDL.h>

#ifdef _WIN32
#include "EMouse.h"
#include "EKeyboard.h"
#include "EGameController.h"

#define lilInput EInput::Instance()
#define lilMouse EInput::Instance()->GetMouse()
#define lilKeyboard EInput::Instance()->GetKeyboard()
#define lilGameController EInput::Instance()->GetController()
#endif

#ifdef __ANDROID__
#include "ETouch.h"

#define lilInput EInput::Instance()
#define liltouch EInput::Instance()->Gettouch()
#endif



class EInput
{
public:
	// Return olny instance of class
	static EInput* Instance();

	// Creates input system
	bool Initialize();

	// Updates input system
	void Update();

	// Closes all input devices and cleans up input system
	void Shutdown();

#ifdef _WIN32
	EKeyboard* GetKeyboard() { return m_Keyboard; }
	EMouse* GetMouse() { return m_Mouse; }
	EGameController* GetController(unsigned index);
#endif

	// TODO: Test touch input
#ifdef __ANDROID__
	// Returns the touch manager
	ETouch* GetTouch() { return m_Touch; }
#endif

private:
	static EInput* s_Instance;

	SDL_Event m_Event;

#ifdef _WIN32
	EMouse* m_Mouse;
	EKeyboard* m_Keyboard;
	std::vector<EGameController*> m_GameControllers;
#endif

#ifdef __ANDROID__
	ETouch* m_Touch;
#endif

	int m_ScreenWidth;
	int m_ScreenHeight;

private:
	// Only one instance of class and no copying
	EInput();
	~EInput() {}
	EInput(const EInput& input) {}
	void operator=(const EInput& input) {}
};

