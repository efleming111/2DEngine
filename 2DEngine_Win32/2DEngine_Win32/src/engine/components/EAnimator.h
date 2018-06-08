//
//  2DEngine
//  EAnimator.h
//  Eric Fleming
//  5/9/2018
//

#pragma once

#include <list>

#include "EComponent.h"
#include "subcomponents\EAnimation.h"

class EAnimator : public EComponent
{
public:
	EAnimator(EGameObject* gameObject) : EComponent(gameObject) {}
	~EAnimator() {}

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
	bool IsCurrentAnimationFinished() { return (*m_CurrentAnimation)->IsAnimationFinished(); }

	void IsRendered(bool isRendered) { (*m_CurrentAnimation)->IsRendered(isRendered); }

	std::list<EAnimation*>::iterator m_CurrentAnimation;
private:
	std::list<EAnimation*> m_Animations;

	//std::list<EAnimation*>::iterator m_CurrentAnimation;

private:
	// No copying
	EAnimator(const EAnimator& animator) {}
	void operator=(const EAnimator& animator) {}
};

