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
	m_CurrentFrame = 0;
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
}

void EAnimation::Update()
{
	m_AccumlativeTime += lilTimer->DeltaTime();
	if (m_AccumlativeTime >= m_TimeBetweenFrames)
	{
		m_AccumlativeTime -= m_TimeBetweenFrames;

		m_Frames[m_CurrentFrame]->isRendered = false;

		m_CurrentFrame++;
		if (m_CurrentFrame >= m_Frames.size())
			if (m_IsLooping)
				m_CurrentFrame = 0;
			else
				m_CurrentFrame--;

		m_Frames[m_CurrentFrame]->isRendered = true;
	}

	m_Frames[m_CurrentFrame]->Update();
}

void EAnimation::Destroy()
{
	for (unsigned i = 0; i < m_Frames.size(); ++i)
	{
		m_Frames[i]->Destroy();
		delete m_Frames[i];
	}

	m_Frames.clear();
}

void EAnimation::StartAnimation()
{
	m_CurrentFrame = 0;
	m_AccumlativeTime = 0.0f;
	m_Frames[m_CurrentFrame]->isRendered = true;
}

void EAnimation::StopAnimation()
{
	m_Frames[m_CurrentFrame]->isRendered = false;
}

void EAnimation::FlipAnimationX()
{
	for (unsigned i = 0; i < m_Frames.size(); ++i)
		m_Frames[i]->m_Transform.scale.x *= -1.0f;
}

