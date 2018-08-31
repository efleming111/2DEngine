//
//  2DEngine
//  ETouch.cpp
//  Eric Fleming
//  4/2/2018
//

#include "and_Touch.h"
#include "../renderer/lilGLWindow.h"

bool lilTouch::Initialize()
{
	mScreenWidth = (float)lilGLWindow->Width();
	mScreenHeight = (float)lilGLWindow->Height();

	for (int i = 0; i < MAX_FINGER_TOUCHES; ++i)
	{
		mTouches[i].fingerID = 0;
		mTouches[i].isTouching = false;
		mTouches[i].x = 0.0f;
		mTouches[i].y = 0.0f;
		mTouches[i].xNormalized = 0.0f;
		mTouches[i].yNormalized = 0.0f;
	}

	return true;
}

void lilTouch::Update()
{
}

void lilTouch::SetFingerTouch(SDL_FingerID fingerID, bool isTouching, float x, float y)
{
	for (int i = 0; i < MAX_FINGER_TOUCHES; ++i)
	{
		// If finger is already down, update it
		if (fingerID == mTouches[i].fingerID)
		{
			mTouches[i].isTouching = isTouching;
			mTouches[i].x = x * m_ScreenWidth;
			mTouches[i].y = y * m_ScreenHeight;
			mTouches[i].xNormalized = x;
			mTouches[i].yNormalized = y;

			return;
		}
	}

	// Reached only if fingerID is not currently registered
	for (int i = 0; i < MAX_FINGER_TOUCHES; ++i)
	{
		if (!mTouches[i].isTouching)
		{
			mTouches[i].fingerID = fingerID;
			mTouches[i].isTouching = true;
			mTouches[i].x = x * m_ScreenWidth;
			mTouches[i].y = y * m_ScreenHeight;
			mTouches[i].xNormalized = x;
			mTouches[i].yNormalized = y;

			return;
		}
	}
}

Finger* lilTouch::GetTouches()
{
	return mTouches;
}

