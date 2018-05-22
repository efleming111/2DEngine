//
//  2DEngine
//  EAnimation.h
//  Eric Fleming
//  5/9/2018
//

#pragma once

#include <vector>

#include "../../../../thirdpartysrc/tinyxml/tinyxml.h"
#include "../ESprite.h"

class EAnimation
{
public:
	EAnimation() {}
	~EAnimation() {}

	void Create(TiXmlElement* element, EGameObject* gameObject);
	void Update();
	void Destroy();

	void StartAnimation();
	void StopAnimation();

	void FlipAnimationX();
	
private:
	std::vector<ESprite*> m_Frames;

	unsigned m_CurrentFrame;

	float m_TimeBetweenFrames;
	float m_AccumlativeTime;

	bool m_IsLooping;

private:
	EAnimation(const EAnimation& animation) {}
	void operator=(const EAnimation& animation) {}
};