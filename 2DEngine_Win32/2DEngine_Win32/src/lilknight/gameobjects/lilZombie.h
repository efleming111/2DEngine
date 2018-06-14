//
//  lil Knight
//  lilZombie.h
//  Eric Fleming
//  6/14/2018
//

#pragma once

#include "../../engine/gameobjects/EGameObject.h"
#include "../../engine/components/ERigidbody.h"
#include "../../engine/components/EAnimator.h"
#include "../scenes/lilSceneObject.h"

// TODO: For testing only
#include <SDL.h>

enum ZombieAnimationState {
	ZOMBIE_ATTACK,
	ZOMBIE_DEAD,
	ZOMBIE_IDLE,
	ZOMBIE_WALK
};

class Zombie : public EGameObject
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

protected:
	SceneObject * m_SceneObject;

	ERigidbody* m_Rigidbody;
	EAnimator* m_Animator;
	bool m_IsRendered;

	bool m_IsWalkingLeft;
	bool m_IsIdle;
	bool m_IsAttacking;
	ZombieAnimationState m_AnimationLastFrame;
	ZombieAnimationState m_CurrentAnimation;

	float m_WalkAcceleration;
	float m_MaxWalkSpeed;

	bool m_IsTakingDamage;
	float m_DamageAmount;
	float m_TotalDamageTime;
	float m_DamageBlinkInterval;
	float m_AccumDamageIntervalTime;
	float m_AccumDamageTime;

	float m_Health;

private:
	Zombie(const Zombie& player) {}
	void operator=(const Zombie& player) {}

	void TakeDamage();
};


