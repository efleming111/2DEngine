//
//  2DEngine
//  lilAnimator.cpp
//  Eric Fleming
//  5/9/2018
//

#include "lilAnimator.h"

void lilAnimator::Create(TiXmlElement* element)
{
	m_Type = element->Attribute("type");

	int currentAnimation;
	element->Attribute("startinganimation", &currentAnimation);

	for (TiXmlElement* animationElement = element->FirstChildElement(); animationElement; animationElement = animationElement->NextSiblingElement())
	{
		lilAnimation* animation = new lilAnimation();
		animation->Create(animationElement, m_GameObject);
		m_Animations.push_back(animation);
	}

	m_CurrentAnimation = m_Animations.begin();
	for (int i = 0; i < currentAnimation; ++i)
		m_CurrentAnimation++;
}

void lilAnimator::Update()
{
	(*m_CurrentAnimation)->Update();
}

void lilAnimator::Destroy()
{
	// Empty
}

void lilAnimator::SetCurrentAnimation(unsigned animationIndex)
{
	std::list<lilAnimation*>::iterator it = m_Animations.begin();
	for (unsigned i = 0; i < animationIndex; ++i)
		it++;

	if (animationIndex < m_Animations.size() && m_CurrentAnimation != it)
	{
		(*m_CurrentAnimation)->StopAnimation();
		m_CurrentAnimation = it;
		(*m_CurrentAnimation)->StartAnimation();
	}
}

void lilAnimator::FlipAnimationX()
{
	for (std::list<lilAnimation*>::iterator it = m_Animations.begin(); it != m_Animations.end(); it++)
		(*it)->FlipAnimationX();
}

void lilAnimator::SetCurrentAnimationIntervalTime(float interval)
{
	(*m_CurrentAnimation)->SetIntervalTime(interval);
}

