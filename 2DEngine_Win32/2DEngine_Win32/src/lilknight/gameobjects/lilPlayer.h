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
#include "enemies/lilEnemy.h"
#include "lilButtonControls.h"
#include "../scenes/lilSceneObject.h"

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

enum {
	ENEMY_ON_LEFT,
	ENEMY_ON_RIGHT
};

class ButtonControls;

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

	void Hit(float amount);

	int GetCoins() { return m_Coins; }
	float GetHealth() { return m_Health; }
	float GetMagic() { return m_Magic; }

protected:
	struct EnemyInHitRange {
		Enemy* enemy;
		bool scoredHit;
	};
	SceneObject* m_SceneObject;

	ButtonControls* m_ButtonControls;
	ERigidbody* m_Rigidbody;
	EAnimator* m_Animator;
	bool m_IsRendered;

	bool m_IsFacingRight;
	bool m_IsIdle;
	bool m_IsJumping;
	bool m_IsAttacking;

	EnemyInHitRange m_EnemiesInHitRange[2];

	PlayerAnimationState m_AnimationLastFrame;
	PlayerAnimationState m_CurrentAnimation;

	float m_WalkAcceleration;
	float m_MaxWalkSpeed;
	bool m_IsRunning;
	float m_RunAcceleration;
	float m_MaxRunSpeed;

	bool m_IsGrounded;
	float m_JumpPower;

	bool m_IsTakingDamage;
	bool mCanTakeDamage;
	float m_DamageAmount;
	float m_TotalDamageTime;
	float m_DamageBlinkInterval;
	float m_AccumDamageIntervalTime;
	float m_AccumDamageTime;

	int m_Coins;
	float m_Health;
	float m_Magic;

private:
	Player(const Player& player) {}
	void operator=(const Player& player) {}

	void TakeDamage();
};



