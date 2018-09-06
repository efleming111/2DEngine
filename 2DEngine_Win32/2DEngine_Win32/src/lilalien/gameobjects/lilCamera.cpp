//
//  lil Knight
//  lilCamera.cpp
//  Eric Fleming
//  5/17/2018
//

#include "lilCamera.h"

void Camera::Create(TiXmlElement* rootElement, float pixelsPerGameUnit)
{
	EGameObject::Create(rootElement, pixelsPerGameUnit);
}

void Camera::OnStart()
{
	m_Player = (Player*)lilGameObjectManager->GetGameObjectByName("Player");
}

void Camera::Update()
{
	if (m_Player->m_Transform.position.x > m_Transform.position.x + 3.0f)
		m_Transform.position.x = m_Player->m_Transform.position.x - 3.0f;

	else if (m_Player->m_Transform.position.x < m_Transform.position.x - 3.0f)
		m_Transform.position.x = m_Player->m_Transform.position.x + 3.0f;

	if (m_Player->m_Transform.position.y > m_Transform.position.y + 3.0f)
		m_Transform.position.y = m_Player->m_Transform.position.y - 3.0f;

	else if (m_Player->m_Transform.position.y < m_Transform.position.y - 3.0f)
		m_Transform.position.y = m_Player->m_Transform.position.y + 3.0f;

	EGameObject::Update();
}

void Camera::Destroy()
{
	EGameObject::Destroy();
}
