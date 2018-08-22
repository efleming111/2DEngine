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
		lilSprite* sprite = new lilSprite(gameObject);
		sprite->Create(spriteElement);
		m_Frames.push_back(sprite);
	}

	m_CurrentFrame = m_Frames.begin();

	m_IsFinished = false;
}

void lilAnimation::Update()
{
	m_AccumlativeTime += lilTimer->DeltaTime();
	if (m_AccumlativeTime >= m_TimeBetweenFrames)
	{
		m_AccumlativeTime -= m_TimeBetweenFrames;

		(*m_CurrentFrame)->isRendered = false;

		m_CurrentFrame++;
		if (m_CurrentFrame == m_Frames.end())
		{
			if (m_IsLooping)
			{
				m_CurrentFrame = m_Frames.begin();
			}

			else
			{
				m_IsFinished = true;
				m_CurrentFrame--;
			}
		}
			
		(*m_CurrentFrame)->isRendered = true;
	}

	(*m_CurrentFrame)->Update();
}

void lilAnimation::Destroy()
{
	// Empty
}

void lilAnimation::StartAnimation()
{
	m_CurrentFrame = m_Frames.begin();
	m_AccumlativeTime = 0.0f;
	(*m_CurrentFrame)->isRendered = true;
	m_IsFinished = false;
}

void lilAnimation::StopAnimation()
{
	(*m_CurrentFrame)->isRendered = false;
	m_IsFinished = false;
}

void lilAnimation::FlipAnimationX()
{
	for (std::list<lilSprite*>::iterator it = m_Frames.begin(); it != m_Frames.end(); ++it)
		(*it)->transform.scale.x *= -1.0f;
}

void lilAnimation::IsRendered(bool isRendered)
{
	(*m_CurrentFrame)->isRendered = isRendered;
}

