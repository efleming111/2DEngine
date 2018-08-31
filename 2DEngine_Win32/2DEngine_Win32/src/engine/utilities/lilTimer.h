//
//  2DEngine
//  lilTimer.h
//  Eric Fleming
//  4/2/2018
//

#pragma once

#include <SDL.h>

#define lilTimer laTimer::Instance()

class laTimer
{
public:
	// Returns only instance of time
	static laTimer* Instance();

	// Creates timer
	bool Initialize();

	// Starts timer
	void Start();

	// Stops timer but not game time
	void Stop();

	// Updates timer
	void Update();

	// Returns time since last frame
	float DeltaTime() { return mDeltaTime; }

	// Returns time since game loop started
	float GameTime() { return (float)mTimeSinceStart; }

	// Returns current frames per second
	int FPS() { return mFPS; }

private:
	static laTimer* sInstance;

	Uint32 mCurrentTime;
	Uint32 mTimeSinceStart;

	float mAccumulatedTime;
	float mDeltaTime;

	bool mIsStarted;

	int mFrames;
	int mFPS;

private:
	// Only one instance of class and no copying
	laTimer() {}
	~laTimer() {}
	laTimer(const laTimer& timer) {}
	void operator=(const laTimer& timer) {}
};

