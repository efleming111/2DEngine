//
//  lil Knight
//  lilCamera.cpp
//  Eric Fleming
//  5/17/2018
//

#include "lilCamera.h"

void Camera::Create(const char* filename, float pixelsPerGameUnit)
{
	EGameObject::Create(filename, pixelsPerGameUnit);
}

void Camera::Create(TiXmlElement* rootElement, float pixelsPerGameUnit)
{
	EGameObject::Create(rootElement, pixelsPerGameUnit);
}

void Camera::OnStart()
{
	m_Player = (Player*)lilGameObjectManager->GetGameObject("Player");
}

void Camera::Update()
{
	EGameObject::Update();

	if (m_Player->m_Transform.position.x > m_Transform.position.x)
		m_Transform.position.x = m_Player->m_Transform.position.x;
}

void Camera::Destroy()
{
	EGameObject::Destroy();
}
