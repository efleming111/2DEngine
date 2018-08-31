//
//  2DEngine
//  lilAnimator.h
//  Eric Fleming
//  5/9/2018
//

#pragma once

#include <list>

#include "lilComponent.h"
#include "subcomponents\lilAnimation.h"

class lilAnimator : public lilComponent
{
public:
	lilAnimator(lilGameObject* gameObject) : lilComponent(gameObject) {}
	~lilAnimator() {}

	// Creates animations for animator
	// @ element - data for the animations for this animator
	void Create(TiXmlElement* element);

	// Updates the animator
	void Update();

	// Does nothing
	void Destroy();

	// Sets current animation
	// @ animationIndex - index of animation to play, index starts at 0
	void SetCurrentAnimation(unsigned animationIndex);

	// Flips the animations along their y axis
	void FlipAnimationX();

	// Changes the time between animations
	void SetCurrentAnimationIntervalTime(float interval);

	// Return true if animation has finished playing
	bool IsCurrentAnimationFinished() { return (*mCurrentAnimation)->IsAnimationFinished(); }

	void IsRendered(bool isRendered) { (*mCurrentAnimation)->IsRendered(isRendered); }

	std::list<lilAnimation*>::iterator mCurrentAnimation;
private:
	std::list<lilAnimation*> mAnimations;

	//std::list<EAnimation*>::iterator mCurrentAnimation;

private:
	// No copying
	lilAnimator(const lilAnimator& animator) {}
	void operator=(const lilAnimator& animator) {}
};

