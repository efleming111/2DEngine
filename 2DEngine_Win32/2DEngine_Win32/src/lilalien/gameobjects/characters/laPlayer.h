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
	FACE,
	JUMP,
	CROUCH,
	HURT,
	CLIMB,
	SWIM,
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

	void AddCoin() { mCoins++; }
	void AddScore(int amount) { mScore += amount; }
	void AddKey(int index);

	int GetCoins() { return mCoins; }
	bool* GetKeys() { return mKeys; }
	bool GetKey(int index);
	int GetScore() { return mScore; }

protected:
	laLevelController* mLevelController;

	lilRigidbody* mRigidbody;
	lilAnimator* mAnimator;
	bool mIsRendered;

	bool mIsFacingRight;
	bool mIsIdle;
	bool mIsJumping;

	PlayerAnimationState mAnimationLastFrame;
	PlayerAnimationState mCurrentAnimation;

	float mWalkAcceleration;
	float mMaxWalkSpeed;
	bool mIsRunning;
	float mRunAcceleration;
	float mMaxRunSpeed;

	bool mIsGrounded;
	float mJumpPower;

	int mCoins;
	bool mKeys[4]; // Yellow, Green, Red, Blue
	int mScore;

private:
	laPlayer(const laPlayer& player) {}
	void operator=(const laPlayer& player) {}
};



