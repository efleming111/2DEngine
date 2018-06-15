//
//  lil Knight
//  lilZombie.h
//  Eric Fleming
//  6/14/2018
//

#pragma once

#include "lilEnemy.h"
#include "../../../engine/components/ERigidbody.h"
#include "../../../engine/components/EAnimator.h"
#include "../../scenes/lilSceneObject.h"

// TODO: For testing only
#include <SDL.h>

enum ZombieAnimationState {
	ZOMBIE_ATTACK,
	ZOMBIE_DEAD,
	ZOMBIE_IDLE,
	ZOMBIE_WALK
};

class Zombie : public Enemy
{
public:
	Zombie() {}
	~Zombie() {}

	void Create(TiXmlElement* rootElement, float pixelsPerGameUnit);
	void OnStart();
	void Update();
	void Destroy();

	void BeginContact(ERigidbody* thisRigidbody, ERigidbody* otherRigidbody);
	void EndContact(ERigidbody* thisRigidbody, ERigidbody* otherRigidbody);

	void Hit();

protected:
	bool m_IsWalkingLeft;
	bool m_IsIdle;
	bool m_IsAttacking;
	ZombieAnimationState m_AnimationLastFrame;
	ZombieAnimationState m_CurrentAnimation;

	float m_WalkAcceleration;
	float m_MaxWalkSpeed;

	bool m_IsTakingDamage;
	float m_DamageBlinkInterval;
	float m_DamageBlinkIntervalAccum;
	int mNumberOfBlinks;
	int mBlinkCount;
	int m_Health;

private:
	Zombie(const Zombie& player) {}
	void operator=(const Zombie& player) {}

	void TakeDamage();
};


