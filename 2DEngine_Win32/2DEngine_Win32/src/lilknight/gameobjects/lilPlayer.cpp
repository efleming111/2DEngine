//
//  lil Knight
//  lilPlayer.cpp
//  Eric Fleming
//  5/22/2018
//

#include "lilPlayer.h"
#include "enemies/lilZombie.h"
#include "../../engine/utilities/ETimer.h"
#include "../../engine/gameobjects/EGameObjectManager.h"
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
	m_SceneObject = (SceneObject*)lilGameObjectManager->GetGameObjectByType("Scene");
	float x, y;
	m_SceneObject->GetPlayerStart(&x, &y);
#ifdef __ANDROID__
	m_ButtonControls = (ButtonControls*)lilGameObjectManager->GetGameObjectByName("androidcontrols");
#endif
	m_Rigidbody = (ERigidbody*)GetComponentByType("rigidbody");
	EVector2D pos(x, y);
	m_Rigidbody->SetPosition(pos);

	m_Animator = (EAnimator*)GetComponentByType("animator");

	m_IsRendered = true;

	m_IsFacingRight = true;
	m_IsJumping = false;
	m_IsAttacking = false;
	m_IsGrounded = false;

	m_EnemiesInHitRange[ENEMY_ON_LEFT].enemy = 0;
	m_EnemiesInHitRange[ENEMY_ON_RIGHT].enemy = 0;

	m_IsTakingDamage = false;
	m_TotalDamageTime = 2.0f;
	m_DamageBlinkInterval = .1f;
	m_DamageAmount = 0.0f;
	m_AccumDamageIntervalTime = 0.0f;
}

void Player::Update()
{
	EVector2D velocity = m_Rigidbody->GetVelocity();
	
	if ((m_CurrentAnimation == ATTACK || m_CurrentAnimation == JUMP_ATTACK) &&
		m_Animator->IsCurrentAnimationFinished())
	{
		m_IsAttacking = false;
		m_EnemiesInHitRange[ENEMY_ON_LEFT].scoredHit = false;
		m_EnemiesInHitRange[ENEMY_ON_RIGHT].scoredHit = false;
	}

#ifdef _WIN32
	if (lilKeyboard->GetKeyDown(KC_Z))
		m_IsAttacking = true;

	if (lilKeyboard->GetKeyDown(KC_SPACE) && m_IsGrounded)
	{
		velocity.y = m_JumpPower;
		m_IsJumping = true;
	}

	else if (!m_IsGrounded)
		m_IsJumping = true;
	
	if (lilKeyboard->GetKey(KC_LEFTARROW))
	{
		m_IsIdle = false;

		if (m_IsFacingRight)
		{
			m_Animator->FlipAnimationX();
			m_IsFacingRight = false;
		}

		if (lilKeyboard->GetKey(KC_X))
		{
			velocity.x = EMax(velocity.x - m_RunAcceleration, -m_MaxRunSpeed);

			if (!m_IsJumping)
				m_IsRunning = true;
		}

		else
		{
			velocity.x = EMax(velocity.x - m_WalkAcceleration, -m_MaxWalkSpeed);

			if (!m_IsJumping)
				m_IsRunning = false;
		}
	}
	
	else if (lilKeyboard->GetKey(KC_RIGHTARROW))
	{
		m_IsIdle = false;

		if (!m_IsFacingRight)
		{
			m_Animator->FlipAnimationX();
			m_IsFacingRight = true;
		}

		if (lilKeyboard->GetKey(KC_X))
		{
			velocity.x = EMin(velocity.x + m_RunAcceleration, m_MaxRunSpeed);

			if (!m_IsJumping)
				m_IsRunning = true;
		}

		else
		{
			velocity.x = EMin(velocity.x + m_WalkAcceleration, m_MaxWalkSpeed);

			if (!m_IsJumping)
				m_IsRunning = false;
		}
	}
	
	else
	{
		velocity.x *= .98f;
		if (abs(velocity.x) < .28f)
			velocity.x = 0.0f;

		if (!m_IsJumping && abs(velocity.x) < .05f && !m_IsAttacking)
			m_IsIdle = true;
	}
#endif
#ifdef __ANDROID__
	if (m_ButtonControls->GetButtonDown(2))
		m_IsAttacking = true;

	if (m_ButtonControls->GetButtonDown(3) && m_IsGrounded)
	{
		velocity.y = m_JumpPower;
		m_IsJumping = true;
	}

	else if (!m_IsGrounded)
		m_IsJumping = true;

	if (m_ButtonControls->GetButton(0))
	{
		m_IsIdle = false;

		if (m_IsFacingRight)
		{
			m_Animator->FlipAnimationX();
			m_IsFacingRight = false;
		}

		if (m_ButtonControls->GetButton(4))
		{
			velocity.x = EMax(velocity.x - m_RunAcceleration, -m_MaxRunSpeed);

			if (!m_IsJumping)
				m_IsRunning = true;
		}

		else
		{
			velocity.x = EMax(velocity.x - m_WalkAcceleration, -m_MaxWalkSpeed);

			if (!m_IsJumping)
				m_IsRunning = false;
		}
	}

	else if (m_ButtonControls->GetButton(1))
	{
		m_IsIdle = false;

		if (!m_IsFacingRight)
		{
			m_Animator->FlipAnimationX();
			m_IsFacingRight = true;
		}

		if (m_ButtonControls->GetButton(4))
		{
			velocity.x = EMin(velocity.x + m_RunAcceleration, m_MaxRunSpeed);

			if (!m_IsJumping)
				m_IsRunning = true;
		}

		else
		{
			velocity.x = EMin(velocity.x + m_WalkAcceleration, m_MaxWalkSpeed);

			if (!m_IsJumping)
				m_IsRunning = false;
		}
	}

	else
	{
		velocity.x *= .98f;
		if (abs(velocity.x) < .28f)
			velocity.x = 0.0f;

		if (!m_IsJumping && abs(velocity.x) < .05 && !m_IsAttacking)
			m_IsIdle = true;
	}
#endif

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
	{
		if (!m_IsFacingRight && m_EnemiesInHitRange[ENEMY_ON_LEFT].enemy && !m_EnemiesInHitRange[ENEMY_ON_LEFT].scoredHit)
		{
			m_EnemiesInHitRange[ENEMY_ON_LEFT].enemy->Hit();
			m_EnemiesInHitRange[ENEMY_ON_LEFT].scoredHit = true;
		}

		if (m_IsFacingRight && m_EnemiesInHitRange[ENEMY_ON_RIGHT].enemy && !m_EnemiesInHitRange[ENEMY_ON_RIGHT].scoredHit)
		{
			m_EnemiesInHitRange[ENEMY_ON_RIGHT].enemy->Hit();
			m_EnemiesInHitRange[ENEMY_ON_RIGHT].scoredHit = true;
		}

		if (m_IsGrounded)
			m_CurrentAnimation = ATTACK;
		else
			m_CurrentAnimation = JUMP_ATTACK;
	}

	else if (m_IsJumping || !m_IsGrounded)
		m_CurrentAnimation = JUMP;

	else if (m_IsRunning)
		m_CurrentAnimation = RUN;

	else if (!m_IsIdle)
		m_CurrentAnimation = WALK;

	else
		m_CurrentAnimation = IDLE;

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

	if (thisRigidbody->colliderName->compare("attackleft") == 0 && otherRigidbody->colliderName->compare("enemy") == 0)
	{
		if (!m_IsFacingRight)
		{
			m_EnemiesInHitRange[ENEMY_ON_LEFT].enemy = (Enemy*)(otherRigidbody->GetGameObject());
			m_EnemiesInHitRange[ENEMY_ON_LEFT].scoredHit = false;
		}
	}

	if (thisRigidbody->colliderName->compare("attackright") == 0 && otherRigidbody->colliderName->compare("enemy") == 0)
	{
		if (m_IsFacingRight)
		{
			m_EnemiesInHitRange[ENEMY_ON_RIGHT].enemy = (Enemy*)(otherRigidbody->GetGameObject());
			m_EnemiesInHitRange[ENEMY_ON_RIGHT].scoredHit = false;
		}
	}
}

void Player::EndContact(ERigidbody* thisRigidbody, ERigidbody* otherRigidbody)
{
	if (thisRigidbody->colliderName->compare("groundsensor") == 0 && otherRigidbody->colliderName->compare("ground") == 0)
	{
		m_IsGrounded = false;
	}

	if (thisRigidbody->colliderName->compare("attackleft") == 0 && otherRigidbody->colliderName->compare("enemy") == 0)
	{
		if (!m_IsFacingRight)
		{
			m_EnemiesInHitRange[ENEMY_ON_LEFT].enemy = 0;
		}
	}

	if (thisRigidbody->colliderName->compare("attackright") == 0 && otherRigidbody->colliderName->compare("enemy") == 0)
	{
		if (m_IsFacingRight)
		{
			m_EnemiesInHitRange[ENEMY_ON_RIGHT].enemy = 0;
		}
	}
}

void Player::TakeDamage()
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


