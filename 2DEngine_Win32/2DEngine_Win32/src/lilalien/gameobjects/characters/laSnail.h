//
//  lil Alien
//  laSnail.h
//  Eric Fleming
//  6/14/2018
//

#pragma once

#include "laEnemy.h"
#include "../../../engine/components/lilRigidbody.h"
#include "../../../engine/components/lilAnimator.h"
#include "../../levelmanager/laLevelManager.h"
#include "laPlayer.h"

// TODO: For testing only
#include <SDL.h>

enum SnailAnimationState {
	SNAIL_MOVE,
	SNAIL_DEAD
};

class laSnail : public laEnemy
{
public:
	laSnail() {}
	~laSnail() {}

	void Create(TiXmlElement* rootElement, float pixelsPerGameUnit);
	void OnStart();
	void Update();
	void Destroy();

	void BeginContact(lilRigidbody* thisRigidbody, lilRigidbody* otherRigidbody);
	void EndContact(lilRigidbody* thisRigidbody, lilRigidbody* otherRigidbody);

protected:
	laPlayer* mPlayer;

	bool mIsWalkingLeft;
	bool mIsIdle;
	SnailAnimationState mAnimationLastFrame;
	SnailAnimationState mCurrentAnimation;

	float mWalkAcceleration;
	float mMaxWalkSpeed;

private:
	laSnail(const laSnail& player) {}
	void operator=(const laSnail& player) {}
};


