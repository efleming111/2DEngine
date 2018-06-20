//
//  lil Knight
//  lilPlayer.cpp
//  Eric Fleming
//  5/22/2018
//

#include "lilZombie.h"
#include "../../../engine/utilities/ETimer.h"
#include "../../../engine/gameobjects/EGameObjectManager.h"
#include "../../../engine/renderer/EGLRenderer.h"

void Zombie::Create(TiXmlElement* rootElement, float pixelsPerGameUnit)
{
	Enemy::Create(rootElement, pixelsPerGameUnit);
	double walkAcc, maxWalkSpeed;
	rootElement->Attribute("walkacceleration", &walkAcc);
	rootElement->Attribute("maxwalkspeed", &maxWalkSpeed);

	m_AnimationLastFrame = m_CurrentAnimation = ZOMBIE_WALK;

	m_WalkAcceleration = (float)walkAcc;
	m_MaxWalkSpeed = (float)maxWalkSpeed;
}

void Zombie::OnStart()
{
	Enemy::OnStart();

	mPlayer = (Player*)lilGameObjectManager->GetGameObjectByName("Player");
	mIsHittingPlayer = false;

	m_IsWalkingLeft = false;
	m_IsIdle = true;
	m_Animator->FlipAnimationX();
	m_IsAttacking = false;

	m_IsTakingDamage = false;
	m_DamageBlinkInterval = .15f;
	m_DamageBlinkIntervalAccum = 0.0f;
	mNumberOfBlinks = 3;
	mBlinkCount = 0;
	m_Health = 2;
}

void Zombie::Update()
{
	EVector2D velocity = m_Rigidbody->GetVelocity();

	if (abs(m_Transform.position.x - mPlayer->m_Transform.position.x) < 8.0f)
	{
		m_IsWalkingLeft = true;
		m_IsIdle = false;
	}

	if (mIsHittingPlayer)
		mPlayer->Hit(.1f);

	if (m_CurrentAnimation == ZOMBIE_DEAD)
		m_Rigidbody->SetActive(false);


	if (m_Health <= 0)
	{
		m_CurrentAnimation = ZOMBIE_DEAD;
		velocity.x = 0.0f;
	}

	else
	{
		if (m_IsIdle)
			velocity.x = 0.0f;

		else if (m_IsWalkingLeft)
			velocity.x = EMax(velocity.x - m_WalkAcceleration, -m_MaxWalkSpeed);
		else
			velocity.x = EMin(velocity.x + m_WalkAcceleration, m_MaxWalkSpeed);

		if (m_IsTakingDamage)
			TakeDamage();

		if (m_IsAttacking)
			m_CurrentAnimation = ZOMBIE_ATTACK;
		else if (abs(velocity.x) > .15f)
			m_CurrentAnimation = ZOMBIE_WALK;
		else
			m_CurrentAnimation = ZOMBIE_IDLE;
	}
	

	if (m_AnimationLastFrame != m_CurrentAnimation)
	{
		m_AnimationLastFrame = m_CurrentAnimation;
		m_Animator->SetCurrentAnimation((unsigned)m_CurrentAnimation);
	}

	m_Rigidbody->SetVelocity(velocity);

	Enemy::Update();
}

void Zombie::Destroy()
{
	Enemy::Destroy();
}

void Zombie::BeginContact(ERigidbody* thisRigidbody, ERigidbody* otherRigidbody)
{
	if (thisRigidbody->colliderName->compare("attack") == 0 && otherRigidbody->colliderName->compare("playertopcollider") == 0)
	{
		m_IsAttacking = true;
	}

	if (thisRigidbody->colliderName->compare("hitplayer") == 0 && otherRigidbody->colliderName->compare("playertopcollider") == 0)
	{
		mIsHittingPlayer = true;
	}

	if (thisRigidbody->colliderName->compare("enemy") == 0 && otherRigidbody->colliderName->compare("enemyreverse") == 0)
	{
		m_IsWalkingLeft = !m_IsWalkingLeft;
		m_Animator->FlipAnimationX();
	}
}

void Zombie::EndContact(ERigidbody* thisRigidbody, ERigidbody* otherRigidbody)
{
	if (thisRigidbody->colliderName->compare("attack") == 0 && otherRigidbody->colliderName->compare("playertopcollider") == 0)
	{
		m_IsAttacking = false;
	}

	if (thisRigidbody->colliderName->compare("hitplayer") == 0 && otherRigidbody->colliderName->compare("playertopcollider") == 0)
	{
		mIsHittingPlayer = false;
	}
}

void Zombie::Hit()
{
	m_IsTakingDamage = true;
	m_Animator->IsRendered(false);
	m_Health--;
}

void Zombie::TakeDamage()
{
	m_DamageBlinkIntervalAccum += lilTimer->DeltaTime();

	if (m_DamageBlinkIntervalAccum > m_DamageBlinkInterval && mBlinkCount < mNumberOfBlinks)
	{
		m_DamageBlinkIntervalAccum = 0.0f;
		m_Animator->IsRendered(true);
		m_IsTakingDamage = false;
		mBlinkCount++;
		if (mBlinkCount == mNumberOfBlinks)
			mBlinkCount = 0;
	}
}
