//
//  lil Knight
//  lilPlayer.h
//  Eric Fleming
//  5/21/2018
//

#pragma once

#include "../../engine/gameobjects/EGameObject.h"
#include "../../engine/input/EInput.h"
#include "../../engine/components/ERigidbody.h"
#include "../../engine/components/EAnimator.h"

// TODO: For testing only
#include <SDL.h>

enum PlayerAnimationState {
	ATTACK,
	DEAD,
	IDLE,
	JUMP,
	JUMP_ATTACK,
	RUN,
	WALK
};

class Player : public EGameObject
{
public:
	Player() {}
	~Player() {}

	void Create(TiXmlElement* rootElement, float pixelsPerGameUnit);
	void OnStart();
	void Update();
	void Destroy();

	void BeginContact(ERigidbody* thisRigidbody, ERigidbody* otherRigidbody);
	void EndContact(ERigidbody* thisRigidbody, ERigidbody* otherRigidbody);

	int GetCoins() { return m_Coins; }
	float GetHealth() { return m_Health; }
	float GetMagic() { return m_Magic; }

protected:
	ERigidbody* m_Rigidbody;
	EAnimator* m_Animator;

	bool m_IsFacingRight;
	bool m_IsJumping;
	PlayerAnimationState m_AnimationLastFrame;
	PlayerAnimationState m_CurrentAnimation;

	float m_WalkAcceleration;
	float m_MaxWalkSpeed;
	float m_RunAcceleration;
	float m_MaxRunSpeed;

	bool m_IsGrounded;
	float m_JumpPower;

	bool m_IsTakingDamage;
	float m_DamageAmount;
	float m_AccumDamgeTime;

	int m_Coins;
	float m_Health;
	float m_Magic;

private:
	Player(const Player& player) {}
	void operator=(const Player& player) {}

	void TakeDamage();
};



