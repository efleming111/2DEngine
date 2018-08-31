//
//  2DEngine
//  lilAnimation.cpp
//  Eric Fleming
//  5/9/2018
//

#include <string>

#include "lilAnimation.h"
#include "../../utilities/lilTimer.h"

void lilAnimation::Create(TiXmlElement* element, lilGameObject* gameObject)
{
	mAccumlativeTime = 0.0f;

	double frameInterval;
	element->Attribute("frameinterval", &frameInterval);
	mTimeBetweenFrames = (float)frameInterval;

	std::string isLooping = element->Attribute("islooping");
	if (isLooping.compare("true") == 0)
		mIsLooping = true;
	else
		mIsLooping = false;

	for (TiXmlElement* spriteElement = element->FirstChildElement(); spriteElement; spriteElement = spriteElement->NextSiblingElement())
	{
		lilSprite* sprite = new lilSprite(gameObject);
		sprite->Create(spriteElement);
		mFrames.push_back(sprite);
	}

	mCurrentFrame = mFrames.begin();

	mIsFinished = false;
}

void lilAnimation::Update()
{
	mAccumlativeTime += lilTimer->DeltaTime();
	if (mAccumlativeTime >= mTimeBetweenFrames)
	{
		mAccumlativeTime -= mTimeBetweenFrames;

		(*mCurrentFrame)->isRendered = false;

		mCurrentFrame++;
		if (mCurrentFrame == mFrames.end())
		{
			if (mIsLooping)
			{
				mCurrentFrame = mFrames.begin();
			}

			else
			{
				mIsFinished = true;
				mCurrentFrame--;
			}
		}
			
		(*mCurrentFrame)->isRendered = true;
	}

	(*mCurrentFrame)->Update();
}

void lilAnimation::Destroy()
{
	// Empty
}

void lilAnimation::StartAnimation()
{
	mCurrentFrame = mFrames.begin();
	mAccumlativeTime = 0.0f;
	(*mCurrentFrame)->isRendered = true;
	mIsFinished = false;
}

void lilAnimation::StopAnimation()
{
	(*mCurrentFrame)->isRendered = false;
	mIsFinished = false;
}

void lilAnimation::FlipAnimationX()
{
	for (std::list<lilSprite*>::iterator it = mFrames.begin(); it != mFrames.end(); ++it)
		(*it)->transform.scale.x *= -1.0f;
}

void lilAnimation::IsRendered(bool isRendered)
{
	(*mCurrentFrame)->isRendered = isRendered;
}

