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

#include "lilInputDefines.h"

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

	// Get input state
	bool GetButton(std::string inputName, int gameControllerIndex = -1) { return mInputAbstractionLayer->GetButton(inputName, gameControllerIndex); }
	bool GetButtonDown(std::string inputName, int gameControllerIndex = -1) { return mInputAbstractionLayer->GetButtonDown(inputName, gameControllerIndex); }
	
	void GetCursorPositions(CursorPosition* cursorPositions, int* numberOfCursors) { return mInputAbstractionLayer->GetCursorPositions(cursorPositions, numberOfCursors); }
	void GetCursorRelativePositions(CursorPosition* cursorRelativePositions, int* numberOfCursors) { return mInputAbstractionLayer->GetCursorRelativePositions(cursorRelativePositions, numberOfCursors); }
	
	float GetValue(std::string inputName, int gameControllerIndex = -1) { return mInputAbstractionLayer->GetValue(inputName, gameControllerIndex); }

private:
	static laInput* sInstance;

	lilInputAbstractionLayer* mInputAbstractionLayer;

private:
	// Only one instance of class and no copying
	laInput() { mInputAbstractionLayer = 0; }
	~laInput() {}
	laInput(const laInput& input) {}
	void operator=(const laInput& input) {}
};

