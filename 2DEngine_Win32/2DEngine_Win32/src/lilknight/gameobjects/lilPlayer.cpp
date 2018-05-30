//
//  lil Knight
//  lilPlayer.cpp
//  Eric Fleming
//  5/22/2018
//

#include "lilPlayer.h"

void Player::Create(TiXmlElement* rootElement, float pixelsPerGameUnit)
{
	EGameObject::Create(rootElement, pixelsPerGameUnit);
}

void Player::OnStart()
{
	m_Rigidbody = (ERigidbody*)GetComponent("rigidbody");
	m_Animator = (EAnimator*)GetComponent("animator");

	m_IsFacingRight = true;
	m_IsGrounded = false;
}

void Player::Update()
{
	EVector2D velocity = m_Rigidbody->GetVelocity();
	
#ifdef _WIN32
	// TODO: add is grounded sensor
	if (lilKeyboard->GetKeyDown(KC_SPACE) && m_IsGrounded)
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

	EGameObject::Update();
}

void Player::Destroy()
{
	EGameObject::Destroy();
}

void Player::BeginContact(ERigidbody* thisRigidbody, ERigidbody* otherRigidbody)
{
	SDL_Log("%s hit %s, %s %d", thisRigidbody->colliderName, otherRigidbody->colliderName->c_str(), __FILE__, __LINE__);
	/*std::string temp = other->GetGameObject()->GetName();
	if(other->GetGameObject()->GetName().compare("Collider") == 0)
		SDL_Log("Player Hit Ground, %s %d", __FILE__, __LINE__);*/

	if (thisRigidbody->colliderName->compare("groundsensor") == 0 && otherRigidbody->colliderName->compare("ground") == 0)
		m_IsGrounded = true;
}

void Player::EndContact(ERigidbody* thisRigidbody, ERigidbody* otherRigidbody)
{
	if (thisRigidbody->colliderName->compare("groundsensor") == 0 && otherRigidbody->colliderName->compare("ground") == 0)
		m_IsGrounded = false;
}


