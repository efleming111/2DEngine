#include "lilEnemy.h"

void Enemy::Create(TiXmlElement * rootElement, float pixelsPerGameUnit)
{
	EGameObject::Create(rootElement, pixelsPerGameUnit);
}

void Enemy::OnStart()
{
	m_Rigidbody = (ERigidbody*)GetComponentByType("rigidbody");

	m_Animator = (EAnimator*)GetComponentByType("animator");

	m_IsRendered = true;
}

void Enemy::Update()
{
	EGameObject::Update();
}

void Enemy::Destroy()
{
	EGameObject::Destroy();
}
