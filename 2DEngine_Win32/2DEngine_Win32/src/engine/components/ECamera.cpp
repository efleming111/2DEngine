//
//  2DEngine
//  ECamera.cpp
//  Eric Fleming
//  5/18/2018
//

#include "ECamera.h"
#include "../renderer/EGLWindow.h"
#include "../renderer/EGLRenderer.h"

void ECamera::Create(TiXmlElement* element)
{
	m_Type = element->Attribute("type");

	Update();

	lilGLRenderer->RegisterCamera(this);
}

void ECamera::Update()
{
	float wWidth = (float)lilGLWindow->Width();
	float wHeight = (float)lilGLWindow->Height();

	m_View = glm::lookAt(m_GameObject->m_Transform.position * m_GameObject->m_PixelsPerGameUnit, m_GameObject->m_Transform.position * m_GameObject->m_PixelsPerGameUnit + glm::vec3(0.0f, 0.0, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	m_Projection = glm::ortho(wWidth * -.5f, wWidth * .5f, wHeight * -.5f, wHeight * .5f, 2.0f* m_GameObject->m_PixelsPerGameUnit, -2.0f* m_GameObject->m_PixelsPerGameUnit);
}

void ECamera::Destroy()
{
	// Empty
}

void ECamera::SetPosition(float x, float y)
{
	m_GameObject->m_Transform.position.x = x;
	m_GameObject->m_Transform.position.y = y;
}

void ECamera::Move(float xAmount, float yAmount)
{
	m_GameObject->m_Transform.position.x += xAmount;
	m_GameObject->m_Transform.position.y += yAmount;
}
