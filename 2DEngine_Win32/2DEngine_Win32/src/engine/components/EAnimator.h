//
//  2DEngine
//  EAnimator.h
//  Eric Fleming
//  5/9/2018
//

#pragma once

#include <vector>

#include "EComponent.h"
#include "subcomponents\EAnimation.h"

class EAnimator : public EComponent
{
public:
	EAnimator(EGameObject* gameObject) : EComponent(gameObject) {}
	~EAnimator() {}

	void Create(TiXmlElement* element);
	void Update();
	void Destroy();

	void SetCurrentAnimation(unsigned animationIndex);

	void FlipAnimationX();

private:
	std::vector<EAnimation*> m_Animations;

	int m_CurrentAnimation;

private:
	EAnimator(const EAnimator& animator) {}
	void operator=(const EAnimator& animator) {}

	void AddAnimation(EAnimation* animation);
	void FreeAnimations();
};

