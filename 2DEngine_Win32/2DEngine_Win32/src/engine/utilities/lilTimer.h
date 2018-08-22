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
	float DeltaTime() { return m_DeltaTime; }

	// Returns time since game loop started
	float GameTime() { return (float)m_TimeSinceStart; }

	// Returns current frames per second
	int FPS() { return m_FPS; }

private:
	static laTimer* s_Instance;

	Uint32 m_CurrentTime;
	Uint32 m_TimeSinceStart;

	float m_AccumulatedTime;
	float m_DeltaTime;

	bool m_IsStarted;

	int m_Frames;
	int m_FPS;

private:
	// Only one instance of class and no copying
	laTimer() {}
	~laTimer() {}
	laTimer(const laTimer& timer) {}
	void operator=(const laTimer& timer) {}
};

