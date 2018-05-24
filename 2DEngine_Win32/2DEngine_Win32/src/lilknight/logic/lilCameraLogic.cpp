#include "lilCameraLogic.h"

void CameraLogic::Create()
{
	// Empty
}

void CameraLogic::OnStart()
{
	m_Player = lilGameObjectManager->GetGameObject("Player");
}

void CameraLogic::Update()
{
	if (m_Player->m_Transform.position.x > m_GameObject->m_Transform.position.x)
		m_GameObject->m_Transform.position.x = m_Player->m_Transform.position.x;
}

void CameraLogic::Destroy()
{
	// Empty
}
