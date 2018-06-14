//
//  lil Knight
//  lilPlayer.cpp
//  Eric Fleming
//  5/22/2018
//

#include "lilZombie.h"
#include "../../engine/utilities/ETimer.h"
#include "../../engine/gameobjects/EGameObjectManager.h"
#include "../../engine/renderer/EGLRenderer.h"

void Zombie::Create(TiXmlElement* rootElement, float pixelsPerGameUnit)
{
	EGameObject::Create(rootElement, pixelsPerGameUnit);

	// TODO: Get player attribute here. 
	double walkAcc, maxWalkSpeed;
	rootElement->Attribute("walkacceleration", &walkAcc);
	rootElement->Attribute("maxwalkspeed", &maxWalkSpeed);

	m_AnimationLastFrame = m_CurrentAnimation = ZOMBIE_WALK;

	m_WalkAcceleration = (float)walkAcc;
	m_MaxWalkSpeed = (float)maxWalkSpeed;
}

void Zombie::OnStart()
{
	//m_SceneObject = (SceneObject*)lilGameObjectManager->GetGameObjectByType("Scene");
	// TODO: add enemey starts to scene object
	/*float x, y;
	m_SceneObject->GetPlayerStart(&x, &y);*/

	m_Rigidbody = (ERigidbody*)GetComponentByType("rigidbody");
	/*EVector2D pos(x, y);
	m_Rigidbody->SetPosition(pos);*/

	m_Animator = (EAnimator*)GetComponentByType("animator");

	m_IsRendered = true;

	m_IsWalkingLeft = true;
	m_Animator->FlipAnimationX();
	m_IsAttacking = false;

	m_IsTakingDamage = false;
	m_TotalDamageTime = 2.0f;
	m_DamageBlinkInterval = .1f;
	m_DamageAmount = 0.0f;
	m_AccumDamageIntervalTime = 0.0f;
}

void Zombie::Update()
{
	EVector2D velocity = m_Rigidbody->GetVelocity();
	if(m_IsWalkingLeft)
		velocity.x = EMax(velocity.x - m_WalkAcceleration, -m_MaxWalkSpeed);
	else
		velocity.x = EMin(velocity.x + m_WalkAcceleration, m_MaxWalkSpeed);

	m_IsIdle = false;


	// TODO: For testing HUD
	//if (lilKeyboard->GetKeyDown(KC_C))
	//	m_Coins *= 9;

	//if (lilKeyboard->GetKeyDown(KC_H))
	//{
	//	// TODO: Set this thru enemy contact
	//	m_IsTakingDamage = true;
	//	m_DamageAmount = .1f;
	//}

	//if (lilKeyboard->GetKeyDown(KC_M))
	//	m_Magic += .05f;

	if (m_IsTakingDamage)
		TakeDamage();

	if (m_IsAttacking)
		m_CurrentAnimation = ZOMBIE_ATTACK;
	else if(abs(velocity.x) > .15f)
		m_CurrentAnimation = ZOMBIE_WALK;
	else
		m_CurrentAnimation = ZOMBIE_IDLE;

	if (m_AnimationLastFrame != m_CurrentAnimation)
	{
		m_AnimationLastFrame = m_CurrentAnimation;
		m_Animator->SetCurrentAnimation((unsigned)m_CurrentAnimation);
	}

	m_Rigidbody->SetVelocity(velocity);

	EGameObject::Update();
}

void Zombie::Destroy()
{
	EGameObject::Destroy();
}

void Zombie::BeginContact(ERigidbody* thisRigidbody, ERigidbody* otherRigidbody)
{
	if (thisRigidbody->colliderName->compare("attack") == 0 && otherRigidbody->colliderName->compare("playertopcollider") == 0)
	{
		m_IsAttacking = true;
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
}

void Zombie::TakeDamage()
{
	m_Health -= m_DamageAmount;
	m_DamageAmount = 0.0f;

	m_AccumDamageIntervalTime += lilTimer->DeltaTime();
	m_AccumDamageTime += lilTimer->DeltaTime();

	if (m_AccumDamageTime > m_TotalDamageTime)
	{
		m_AccumDamageIntervalTime = 0.0f;
		m_AccumDamageTime = 0.0f;
		m_IsTakingDamage = false;
		m_Animator->IsRendered(true);
		return;
	}

	if (m_AccumDamageIntervalTime > m_DamageBlinkInterval)
	{
		m_AccumDamageIntervalTime -= m_DamageBlinkInterval;
		m_IsRendered = !m_IsRendered;
		m_Animator->IsRendered(m_IsRendered);
	}
}
