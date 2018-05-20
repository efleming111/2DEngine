//
//  2DEngine
//  ECameraComponent.cpp
//  Eric Fleming
//  5/18/2018
//

#include "ECameraComponent.h"
#include "../renderer/EGLWindow.h"
#include "../renderer/EGLRenderer.h"

void ECameraComponent::Create(TiXmlElement* element)
{
	m_Name = element->Attribute("name");

	Update();

	lilGLRenderer->RegisterCamera(this);
}

void ECameraComponent::Update()
{
	float wWidth = (float)lilGLWindow->Width();
	float wHeight = (float)lilGLWindow->Height();

	m_View = glm::lookAt(m_GameObject->m_Transform.position, m_GameObject->m_Transform.position + glm::vec3(0.0f, 0.0, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	m_Projection = glm::ortho(wWidth * -.5f, wWidth * .5f, wHeight * -.5f, wHeight * .5f, 1.0f, -1.0f);
}

void ECameraComponent::Destroy()
{
	// Empty
}

void ECameraComponent::SetPosition(float x, float y)
{
	m_GameObject->m_Transform.position.x = x;
	m_GameObject->m_Transform.position.y = y;
}

void ECameraComponent::Move(float xAmount, float yAmount)
{
	m_GameObject->m_Transform.position.x += xAmount;
	m_GameObject->m_Transform.position.y += yAmount;
}
