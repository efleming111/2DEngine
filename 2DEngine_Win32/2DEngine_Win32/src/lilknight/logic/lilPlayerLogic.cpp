//
//  lil Knight
//  lilPlayerLogic.cpp
//  Eric Fleming
//  5/22/2018
//

#include "lilPlayerLogic.h"

void PlayerLogic::Create()
{
	m_Rigidbody = (ERigidbody*)m_GameObject->GetComponent("rigidbody");
	m_Animator = (EAnimator*)m_GameObject->GetComponent("animator");

	m_IsFacingRight = true;
}

void PlayerLogic::Update()
{
	EVector2D velocity = m_Rigidbody->GetVelocity();
	
#ifdef _WIN32
	// TODO: add is grounded sensor
	if (lilKeyboard->GetKeyDown(KC_SPACE))
	{
		velocity.y = 10.0f;
	}
	
	if (lilKeyboard->GetKey(KC_A) || lilKeyboard->GetKey(KC_LEFTARROW))
	{
		if (m_IsFacingRight)
		{
			m_Animator->FlipAnimationX();
			m_IsFacingRight = false;
		}

		velocity.x = EMax(velocity.x - .2f, -5.0f);
		m_Animator->SetCurrentAnimation(1u);
	}
	
	else if (lilKeyboard->GetKey(KC_D) || lilKeyboard->GetKey(KC_RIGHTARROW))
	{
		if (!m_IsFacingRight)
		{
			m_Animator->FlipAnimationX();
			m_IsFacingRight = true;
		}

		velocity.x = EMin(velocity.x + .2f, 5.0f);
		m_Animator->SetCurrentAnimation(1u);
}
	
	else
	{
		velocity.x *= .98f;
		m_Animator->SetCurrentAnimation(0u);
	}
#endif
	
#ifdef __ANDROID__
	
#endif 
	
	m_Rigidbody->SetVelocity(velocity);
}

void PlayerLogic::Destroy()
{
	// Empty
}

void PlayerBeginContact(ERigidbody* other)
{
	SDL_Log("Player Begin Contact, %s %d", __FILE__, __LINE__);
}

void PlayerEndContact(ERigidbody* other)
{
	SDL_Log("Player Begin Contact, %s %d", __FILE__, __LINE__);
}


