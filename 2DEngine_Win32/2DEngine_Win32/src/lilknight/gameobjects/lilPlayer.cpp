//
//  lil Knight
//  lilPlayer.cpp
//  Eric Fleming
//  5/22/2018
//

#include "lilPlayer.h"
#include "../../engine/utilities/ETimer.h"

#include "../../engine/renderer/EGLRenderer.h"

void Player::Create(TiXmlElement* rootElement, float pixelsPerGameUnit)
{
	SDL_Log("Created lilPlayer, %s %d", __FILE__, __LINE__);

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

	m_IsRendered = true;

	m_IsFacingRight = true;
	m_IsJumping = false;
	m_IsAttacking = false;
	m_IsGrounded = false;

	m_IsTakingDamage = false;
	m_DamageAmount = 0.0f;
	m_DamageIntervalTime = 0.0f;
}

void Player::Update()
{
	EVector2D velocity = m_Rigidbody->GetVelocity();
	
#ifdef _WIN32
	if ((m_CurrentAnimation == ATTACK || m_CurrentAnimation == JUMP_ATTACK) &&
		m_Animator->IsCurrentAnimationFinished())
	{
		m_IsAttacking = false;
	}

	if (lilKeyboard->GetKeyDown(KC_A))
	{
		m_IsAttacking = true;
		m_CurrentAnimation = ATTACK;
	}

	if (lilKeyboard->GetKeyDown(KC_SPACE) && lilKeyboard->GetKeyDown(KC_Z) && m_IsGrounded ||
		lilKeyboard->GetKeyDown(KC_SPACE) && m_IsAttacking ||
		lilKeyboard->GetKeyDown(KC_Z) && m_IsJumping)
	{
		velocity.y = m_JumpPower;
		m_IsJumping = true;
		m_IsAttacking = true;
		m_CurrentAnimation = JUMP_ATTACK;
	}

	else if (lilKeyboard->GetKeyDown(KC_SPACE) && m_IsGrounded)
	{
		velocity.y = m_JumpPower;
		m_IsJumping = true;
		m_CurrentAnimation = JUMP;
	}
	
	if (lilKeyboard->GetKey(KC_LEFTARROW))
	{
		if (m_IsFacingRight)
		{
			m_Animator->FlipAnimationX();
			m_IsFacingRight = false;
		}

		if (lilKeyboard->GetKey(KC_R))
		{
			velocity.x = EMax(velocity.x - m_RunAcceleration, -m_MaxRunSpeed);

			if (!m_IsJumping)
				m_CurrentAnimation = RUN;
		}

		else
		{
			velocity.x = EMax(velocity.x - m_WalkAcceleration, -m_MaxWalkSpeed);

			if (!m_IsJumping)
				m_CurrentAnimation = WALK;
		}
	}
	
	else if (lilKeyboard->GetKey(KC_RIGHTARROW))
	{
		if (!m_IsFacingRight)
		{
			m_Animator->FlipAnimationX();
			m_IsFacingRight = true;
		}

		if (lilKeyboard->GetKey(KC_R))
		{
			velocity.x = EMin(velocity.x + m_RunAcceleration, m_MaxRunSpeed);

			if (!m_IsJumping)
				m_CurrentAnimation = RUN;
		}

		else
		{
			velocity.x = EMin(velocity.x + m_WalkAcceleration, m_MaxWalkSpeed);

			if (!m_IsJumping)
				m_CurrentAnimation = WALK;
		}
	}
	
	else
	{
		velocity.x *= .98f;
		if (!m_IsJumping && velocity.x < .05 && !m_IsAttacking)
			m_CurrentAnimation = IDLE;
	}

	// TODO: For testing HUD
	if (lilKeyboard->GetKeyDown(KC_C))
		m_Coins *= 9;

	if (lilKeyboard->GetKeyDown(KC_H))
	{
		// TODO: Set this thru enemy contact
		m_IsTakingDamage = true;
		m_DamageAmount = .1f;
	}

	if (lilKeyboard->GetKeyDown(KC_M))
		m_Magic += .05f;
#endif

#ifdef __ANDROID__
	Finger* fingers = lilTouch->GetTouches();
	for (int i = 0; i < MAX_FINGER_TOUCHES && fingers[i].isTouching; ++i)
		if (fingers[i].xNormalized > .75f && fingers[i].yNormalized < .25f)
		{
			int test = (int)lilGLRenderer->GetRenderable("Attack (1)")->m_TextureID;
			SDL_Log("Renderable %s %d, %s %d", lilGLRenderer->GetRenderable("Attack (1)")->name.c_str(), test, __FILE__, __LINE__);
			break;
		}
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
	SDL_Log("COLLISION, %s %d", __FILE__, __LINE__);
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

	m_DamageIntervalTime += lilTimer->DeltaTime();
	m_TotalDamageTime += lilTimer->DeltaTime();

	if (m_TotalDamageTime > TOTAL_DAMAGE_TIME)
	{
		m_DamageIntervalTime = 0.0f;
		m_TotalDamageTime = 0.0f;
		m_IsTakingDamage = false;
		m_Animator->IsRendered(true);
		return;
	}

	if (m_DamageIntervalTime > DAMAGE_BLINK_INTERVAL)
	{
		m_DamageIntervalTime -= DAMAGE_BLINK_INTERVAL;
		m_IsRendered = !m_IsRendered;
		m_Animator->IsRendered(m_IsRendered);
	}
}


