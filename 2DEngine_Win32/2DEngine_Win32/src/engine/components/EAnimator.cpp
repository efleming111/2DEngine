//
//  2DEngine
//  EAnimator.cpp
//  Eric Fleming
//  5/9/2018
//

#include "EAnimator.h"

void EAnimator::Create(TiXmlElement* element)
{
	m_Type = element->Attribute("type");

	element->Attribute("startinganimation", &m_CurrentAnimation);

	for (TiXmlElement* animationElement = element->FirstChildElement(); animationElement; animationElement = animationElement->NextSiblingElement())
	{
		EAnimation* animation = new EAnimation();
		animation->Create(animationElement, m_GameObject);
		m_Animations.push_back(animation);
	}
}

void EAnimator::Update()
{
	m_Animations[m_CurrentAnimation]->Update();
}

void EAnimator::Destroy()
{
	FreeAnimations();
}

void EAnimator::SetCurrentAnimation(unsigned animationIndex)
{
	if (animationIndex < m_Animations.size() && m_CurrentAnimation != animationIndex)
	{
		m_Animations[m_CurrentAnimation]->StopAnimation();
		m_CurrentAnimation = animationIndex;
		m_Animations[m_CurrentAnimation]->StartAnimation();
	}
}

void EAnimator::FlipAnimationX()
{
	for (unsigned i = 0; i < m_Animations.size(); ++i)
		m_Animations[i]->FlipAnimationX();
}

void EAnimator::AddAnimation(EAnimation* animation)
{
	m_Animations.push_back(animation);
}

void EAnimator::FreeAnimations()
{
	for (unsigned i = 0; i < m_Animations.size(); ++i)
	{
		m_Animations[i]->Destroy();
		delete m_Animations[i];
	}
}
