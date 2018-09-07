//
//  lil Alien
//  laPlayer.h
//  Eric Fleming
//  5/21/2018
//

#pragma once

#include "../../../engine/gameobjects/lilGameObject.h"
#include "../../../engine/input/lilInput.h"
#include "../../../engine/components/lilRigidbody.h"
#include "../../../engine/components/lilAnimator.h"
#include "laEnemy.h"
#include "../level/laLevelController.h"

// TODO: For testing only
#include <SDL.h>

// TODO: set to order of animations
enum PlayerAnimationState {
	SHOOT,
	DEAD,
	IDLE,
	JUMP,
	CLIMB,
	RUN,
	WALK
};

class laPlayer : public lilGameObject
{
public:
	laPlayer() {}
	~laPlayer() {}

	void Create(TiXmlElement* rootElement, float pixelsPerGameUnit);
	void OnStart();
	void Update();
	void Destroy();

	void BeginContact(lilRigidbody* thisRigidbody, lilRigidbody* otherRigidbody);
	void EndContact(lilRigidbody* thisRigidbody, lilRigidbody* otherRigidbody);

	void Hit(int amount);

	int GetCoins() { return mCoins; }
	int GetHealth() { return mHealth; }
	int GetScore() { return mScore; }

protected:
	laLevelController* mLevelController;

	lilRigidbody* mRigidbody;
	lilAnimator* mAnimator;
	bool mIsRendered;

	bool mIsFacingRight;
	bool mIsIdle;
	bool mIsJumping;
	bool mIsAttacking;

	PlayerAnimationState mAnimationLastFrame;
	PlayerAnimationState mCurrentAnimation;

	float mWalkAcceleration;
	float mMaxWalkSpeed;
	bool mIsRunning;
	float mRunAcceleration;
	float mMaxRunSpeed;

	bool mIsGrounded;
	float mJumpPower;

	bool mIsTakingDamage;
	bool mCanTakeDamage;
	int mDamageAmount;
	float mTotalDamageTime;
	float mDamageBlinkInterval;
	float mAccumDamageIntervalTime;
	float mAccumDamageTime;

	int mCoins;
	int mHealth;
	int mScore;

private:
	laPlayer(const laPlayer& player) {}
	void operator=(const laPlayer& player) {}

	void TakeDamage();
};



