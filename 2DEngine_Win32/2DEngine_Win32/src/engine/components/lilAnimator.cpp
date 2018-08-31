//
//  2DEngine
//  lilAnimator.cpp
//  Eric Fleming
//  5/9/2018
//

#include "lilAnimator.h"

void lilAnimator::Create(TiXmlElement* element)
{
	mType = element->Attribute("type");

	int currentAnimation;
	element->Attribute("startinganimation", &currentAnimation);

	for (TiXmlElement* animationElement = element->FirstChildElement(); animationElement; animationElement = animationElement->NextSiblingElement())
	{
		lilAnimation* animation = new lilAnimation();
		animation->Create(animationElement, mGameObject);
		mAnimations.push_back(animation);
	}

	mCurrentAnimation = mAnimations.begin();
	for (int i = 0; i < currentAnimation; ++i)
		mCurrentAnimation++;
}

void lilAnimator::Update()
{
	(*mCurrentAnimation)->Update();
}

void lilAnimator::Destroy()
{
	// Empty
}

void lilAnimator::SetCurrentAnimation(unsigned animationIndex)
{
	std::list<lilAnimation*>::iterator it = mAnimations.begin();
	for (unsigned i = 0; i < animationIndex; ++i)
		it++;

	if (animationIndex < mAnimations.size() && mCurrentAnimation != it)
	{
		(*mCurrentAnimation)->StopAnimation();
		mCurrentAnimation = it;
		(*mCurrentAnimation)->StartAnimation();
	}
}

void lilAnimator::FlipAnimationX()
{
	for (std::list<lilAnimation*>::iterator it = mAnimations.begin(); it != mAnimations.end(); it++)
		(*it)->FlipAnimationX();
}

void lilAnimator::SetCurrentAnimationIntervalTime(float interval)
{
	(*mCurrentAnimation)->SetIntervalTime(interval);
}

