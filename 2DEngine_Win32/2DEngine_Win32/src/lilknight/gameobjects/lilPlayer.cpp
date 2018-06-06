//
//  lil Knight
//  lilPlayer.cpp
//  Eric Fleming
//  5/22/2018
//

#include "lilPlayer.h"
#include "../../engine/utilities/ETimer.h"

void Player::Create(TiXmlElement* rootElement, float pixelsPerGameUnit)
{
	EGameObject::Create(rootElement, pixelsPerGameUnit);

	// TODO: Get player attribute here. 
	double walkAcc, maxWalkSpeed, runAcc, maxRunSpeed, jumpPower;
	rootElement->Attribute("walkacceleration", &walkAcc);
	rootElement->Attribute("maxwalkspeed", &maxWalkSpeed);
	rootElement->Attribute("runacceleration", &runAcc);
	rootElement->Attribute("maxrunspeed", &maxRunSpeed);
	rootElement->Attribute("jumppower", &jumpPower);

	m_AnimationLastFrame = m_CurrentAnimation = JUMP;

	m_WalkAcceleration = (float)walkAcc;
	m_MaxWalkSpeed = (float)maxWalkSpeed;
	m_RunAcceleration = (float)runAcc;
	m_MaxRunSpeed = (float)maxRunSpeed;
	m_JumpPower = (float)jumpPower;

	m_Coins = 1;
	m_Health = 1.0f;
	m_Magic = 0.0f;
}

void Player::OnStart()
{
	m_Rigidbody = (ERigidbody*)GetComponentByType("rigidbody");
	m_Animator = (EAnimator*)GetComponentByType("animator");

	m_IsFacingRight = true;
	m_IsJumping = false;
	m_IsGrounded = false;

	m_IsTakingDamage = false;
	m_DamageAmount = 0.0f;
	m_AccumDamgeTime = 0.0f;
}

void Player::Update()
{
	m_CurrentAnimation = IDLE;

	EVector2D velocity = m_Rigidbody->GetVelocity();
	
#ifdef _WIN32
	// TODO: add is grounded sensor
	if (lilKeyboard->GetKeyDown(KC_SPACE) && m_IsGrounded)
	{
		velocity.y = m_JumpPower;
		m_IsJumping = true;
		m_CurrentAnimation = JUMP;
	}
	
	if (lilKeyboard->GetKey(KC_A) || lilKeyboard->GetKey(KC_LEFTARROW))
	{
		if (m_IsFacingRight)
		{
			m_Animator->FlipAnimationX();
			m_IsFacingRight = false;
		}

		velocity.x = EMax(velocity.x - m_WalkAcceleration, -m_MaxWalkSpeed);

		if (!m_IsJumping)
			m_CurrentAnimation = WALK;
	}
	
	else if (lilKeyboard->GetKey(KC_D) || lilKeyboard->GetKey(KC_RIGHTARROW))
	{
		if (!m_IsFacingRight)
		{
			m_Animator->FlipAnimationX();
			m_IsFacingRight = true;
		}

		velocity.x = EMin(velocity.x + m_WalkAcceleration, m_MaxWalkSpeed);
		if (!m_IsJumping)
			m_CurrentAnimation = WALK;
}
	
	else
	{
		velocity.x *= .98f;
		if (!m_IsJumping && velocity.x < .05)
			m_CurrentAnimation = IDLE;
	}

	// TODO: For testing HUD
	if (lilKeyboard->GetKeyDown(KC_C))
		m_Coins *= 9;

	if (lilKeyboard->GetKeyDown(KC_H))
	{

	}

	if (lilKeyboard->GetKeyDown(KC_M))
		m_Magic += .05f;
#endif
	
#ifdef __ANDROID__
	
#endif 

	if (m_IsTakingDamage)
		TakeDamage();

	if (m_AnimationLastFrame != m_CurrentAnimation)
	{
		m_AnimationLastFrame = m_CurrentAnimation;
		m_Animator->SetCurrentAnimation((unsigned)m_CurrentAnimation);
	}
	
	m_Rigidbody->SetVelocity(velocity);

	EGameObject::Update();
}

void Player::Destroy()
{
	EGameObject::Destroy();
}

void Player::BeginContact(ERigidbody* thisRigidbody, ERigidbody* otherRigidbody)
{
	if (thisRigidbody->colliderName->compare("groundsensor") == 0 && otherRigidbody->colliderName->compare("ground") == 0)
	{
		m_IsGrounded = true;
		m_IsJumping = false;
	}
}

void Player::EndContact(ERigidbody* thisRigidbody, ERigidbody* otherRigidbody)
{
	if (thisRigidbody->colliderName->compare("groundsensor") == 0 && otherRigidbody->colliderName->compare("ground") == 0)
	{
		m_IsGrounded = false;
	}
}

void Player::TakeDamage()
{
	m_Health -= m_DamageAmount;
	m_DamageAmount = 0.0f;

	m_AccumDamgeTime += lilTimer->DeltaTime();

	// TODO: Make player flash when hit
}


