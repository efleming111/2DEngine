//
//  2DEngine
//  ETouch.cpp
//  Eric Fleming
//  4/2/2018
//

#include "ETouch.h"
#include "../renderer/EGLWindow.h"

bool ETouch::Initialize()
{
	m_ScreenWidth = (float)lilGLWindow->Width();
	m_ScreenHeight = (float)lilGLWindow->Height();

	for (int i = 0; i < MAX_FINGER_TOUCHES; ++i)
	{
		m_Touches[i].fingerID = 0;
		m_Touches[i].isTouching = false;
		m_Touches[i].x = 0.0f;
		m_Touches[i].y = 0.0f;
		m_Touches[i].xNormalized = 0.0f;
		m_Touches[i].yNormalized = 0.0f;
	}

	return true;
}

void ETouch::SetFingerTouch(SDL_FingerID fingerID, bool isTouching, float x, float y)
{
	for (int i = 0; i < MAX_FINGER_TOUCHES; ++i)
	{
		// If finger is already down, update it
		if (fingerID == m_Touches[i].fingerID)
		{
			m_Touches[i].isTouching = isTouching;
			m_Touches[i].x = x * m_ScreenWidth;
			m_Touches[i].y = y * m_ScreenHeight;
			m_Touches[i].xNormalized = x;
			m_Touches[i].yNormalized = y;

			return;
		}
	}

	// Reached only if fingerID is not currently registered
	for (int i = 0; i < MAX_FINGER_TOUCHES; ++i)
	{
		if (!m_Touches[i].isTouching)
		{
			m_Touches[i].fingerID = fingerID;
			m_Touches[i].isTouching = true;
			m_Touches[i].x = x * m_ScreenWidth;
			m_Touches[i].y = y * m_ScreenHeight;
			m_Touches[i].xNormalized = x;
			m_Touches[i].yNormalized = y;

			return;
		}
	}
}

Finger* ETouch::GetTouches()
{
	return m_Touches;
}

