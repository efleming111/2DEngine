//
//  2DEngine
//  ETouch.h
//  Eric Fleming
//  4/2/2018
//

#pragma once

#include <SDL.h>

const int MAX_FINGER_TOUCHES = 10;

struct Finger
{
	SDL_FingerID fingerID;

	bool isTouching;

	float x;
	float y;

	float xNormalized;
	float yNormalized;
};

class ETouch
{
public:
	ETouch() {}
	~ETouch() {}

	// Initializes touch manager
	bool Initialize();

	// Sets the touch state of one finger
	// @ fingerID - id of the finger being set
	// @ isTouching - true if the finger is touching
	// @ x - x position of the touch normalized 0 to 1
	// @ y - y position of the touch normalized 0 to 1
	void SetFingerTouch(SDL_FingerID fingerID, bool isTouching, float x = 0.0f, float y = 0.0f);

	// Returns array of finger touches
	Finger* GetTouches();

private:
	float m_ScreenWidth;
	float m_ScreenHeight;

	Finger m_Touches[MAX_FINGER_TOUCHES];

private:
	ETouch(const ETouch& touch) {}
	void operator=(const ETouch& touch) {}
};

