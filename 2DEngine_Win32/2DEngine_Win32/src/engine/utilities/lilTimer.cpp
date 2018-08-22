//
//  2DEngine
//  lilTimer.cpp
//  Eric Fleming
//  4/2/2018
//

#include "lilTimer.h"

laTimer* laTimer::s_Instance = 0;

laTimer* laTimer::Instance()
{
	if (!s_Instance)
		s_Instance = new laTimer();

	return s_Instance;
}

bool laTimer::Initialize()
{
	m_IsStarted = false;

	m_TimeSinceStart = 0;
	m_CurrentTime = SDL_GetTicks();

	m_AccumulatedTime = 0.0f;
	m_DeltaTime = 0.0f;

	m_Frames = 0;
	m_FPS = 0;

	return true;
}

void laTimer::Start()
{
	if (!m_IsStarted)
	{
		m_TimeSinceStart += SDL_GetTicks() - m_CurrentTime;
		m_CurrentTime = SDL_GetTicks();
		m_AccumulatedTime = 0.0f;
		m_DeltaTime = 0.0f;
		m_Frames = 0;
		m_FPS = 0;
		m_IsStarted = true;
	}
}

void laTimer::Stop()
{
	if (m_IsStarted)
	{
		m_AccumulatedTime = 0.0f;
		m_DeltaTime = 0.0f;
		m_Frames = 0;
		m_FPS = 0;
		m_IsStarted = false;
	}
}

void laTimer::Update()
{
	if (m_IsStarted)
	{
		m_DeltaTime = (float(SDL_GetTicks() - m_CurrentTime)) / 1000.0f;
		++m_Frames;
	}

	m_TimeSinceStart += SDL_GetTicks() - m_CurrentTime;
	m_CurrentTime = SDL_GetTicks();

	m_AccumulatedTime += m_DeltaTime;
	if (m_AccumulatedTime >= 1.0f)
	{
		m_FPS = m_Frames;
		m_Frames = 0;
		m_AccumulatedTime = 0.0f;
	}
}

