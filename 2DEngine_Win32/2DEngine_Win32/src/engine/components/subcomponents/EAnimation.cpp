//
//  2DEngine
//  EAnimation.cpp
//  Eric Fleming
//  5/9/2018
//

#include <string>

#include "EAnimation.h"
#include "../../utilities/ETimer.h"

void EAnimation::Create(TiXmlElement* element, EGameObject* gameObject)
{
	m_AccumlativeTime = 0.0f;

	double frameInterval;
	element->Attribute("frameinterval", &frameInterval);
	m_TimeBetweenFrames = (float)frameInterval;

	std::string isLooping = element->Attribute("islooping");
	if (isLooping.compare("true") == 0)
		m_IsLooping = true;
	else
		m_IsLooping = false;

	for (TiXmlElement* spriteElement = element->FirstChildElement(); spriteElement; spriteElement = spriteElement->NextSiblingElement())
	{
		ESprite* sprite = new ESprite(gameObject);
		sprite->Create(spriteElement);
		m_Frames.push_back(sprite);
	}

	m_CurrentFrame = m_Frames.begin();
}

void EAnimation::Update()
{
	m_AccumlativeTime += lilTimer->DeltaTime();
	if (m_AccumlativeTime >= m_TimeBetweenFrames)
	{
		m_AccumlativeTime -= m_TimeBetweenFrames;

		(*m_CurrentFrame)->isRendered = false;

		m_CurrentFrame++;
		if (m_CurrentFrame == m_Frames.end())
			if (m_IsLooping)
				m_CurrentFrame = m_Frames.begin();
			else
				m_CurrentFrame--;

		(*m_CurrentFrame)->isRendered = true;
	}

	(*m_CurrentFrame)->Update();
}

void EAnimation::Destroy()
{
	// Empty
}

void EAnimation::StartAnimation()
{
	m_CurrentFrame = m_Frames.begin();
	m_AccumlativeTime = 0.0f;
	(*m_CurrentFrame)->isRendered = true;
}

void EAnimation::StopAnimation()
{
	(*m_CurrentFrame)->isRendered = false;
}

void EAnimation::FlipAnimationX()
{
	for (std::list<ESprite*>::iterator it = m_Frames.begin(); it != m_Frames.end(); ++it)
		(*it)->transform.scale.x *= -1.0f;
}

