//
//  2DEngine
//  lilTimer.cpp
//  Eric Fleming
//  4/2/2018
//

#include "lilTimer.h"

laTimer* laTimer::sInstance = 0;

laTimer* laTimer::Instance()
{
	if (!sInstance)
		sInstance = new laTimer();

	return sInstance;
}

bool laTimer::Initialize()
{
	mIsStarted = false;

	mTimeSinceStart = 0;
	mCurrentTime = SDL_GetTicks();

	mAccumulatedTime = 0.0f;
	mDeltaTime = 0.0f;

	mFrames = 0;
	mFPS = 0;

	return true;
}

void laTimer::Start()
{
	if (!mIsStarted)
	{
		mTimeSinceStart += SDL_GetTicks() - mCurrentTime;
		mCurrentTime = SDL_GetTicks();
		mAccumulatedTime = 0.0f;
		mDeltaTime = 0.0f;
		mFrames = 0;
		mFPS = 0;
		mIsStarted = true;
	}
}

void laTimer::Stop()
{
	if (mIsStarted)
	{
		mAccumulatedTime = 0.0f;
		mDeltaTime = 0.0f;
		mFrames = 0;
		mFPS = 0;
		mIsStarted = false;
	}
}

void laTimer::Update()
{
	if (mIsStarted)
	{
		mDeltaTime = (float(SDL_GetTicks() - mCurrentTime)) / 1000.0f;
		++mFrames;
	}

	mTimeSinceStart += SDL_GetTicks() - mCurrentTime;
	mCurrentTime = SDL_GetTicks();

	mAccumulatedTime += mDeltaTime;
	if (mAccumulatedTime >= 1.0f)
	{
		mFPS = mFrames;
		mFrames = 0;
		mAccumulatedTime = 0.0f;
	}
}

