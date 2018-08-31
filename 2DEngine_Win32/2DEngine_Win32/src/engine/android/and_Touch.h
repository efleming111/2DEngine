//
//  2DEngine
//  ETouch.h
//  Eric Fleming
//  4/2/2018
//

#pragma once

#include <SDL.h>

const int MAX_FINGER_TOUCHES = 10;

struct lilButton
{
	float x;
	float y;
	float width;
	float height;
};

struct Finger
{
	SDL_FingerID fingerID;

	bool isTouching;

	float x;
	float y;

	float xNormalized;
	float yNormalized;
};

class lilTouch
{
public:
	lilTouch() {}
	~lilTouch() {}

	// Initializes touch manager
	bool Initialize();

	void Update();

	// Sets the touch state of one finger
	// @ fingerID - id of the finger being set
	// @ isTouching - true if the finger is touching
	// @ x - x position of the touch normalized 0 to 1
	// @ y - y position of the touch normalized 0 to 1
	void SetFingerTouch(SDL_FingerID fingerID, bool isTouching, float x = 0.0f, float y = 0.0f);

	// Returns array of finger touches
	Finger* GetTouches();

private:
	float mScreenWidth;
	float mScreenHeight;

	Finger mTouches[MAX_FINGER_TOUCHES];

private:
	lilTouch(const lilTouch& touch) {}
	void operator=(const lilTouch& touch) {}
};

