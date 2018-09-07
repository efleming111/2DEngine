//
//  lil Knight
//  lilPlayer.cpp
//  Eric Fleming
//  5/22/2018
//

#include "laSnail.h"
#include "../../../engine/utilities/lilTimer.h"
#include "../../../engine/gameobjects/lilGameObjectManager.h"
#include "../../../engine/renderer/lilGLRenderer.h"

void laSnail::Create(TiXmlElement* rootElement, float pixelsPerGameUnit)
{
	laEnemy::Create(rootElement, pixelsPerGameUnit);
	double walkAcc, maxWalkSpeed;
	rootElement->Attribute("walkacceleration", &walkAcc);
	rootElement->Attribute("maxwalkspeed", &maxWalkSpeed);

	mAnimationLastFrame = mCurrentAnimation = SNAIL_MOVE;

	mWalkAcceleration = (float)walkAcc;
	mMaxWalkSpeed = (float)maxWalkSpeed;
}

void laSnail::OnStart()
{
	laEnemy::OnStart();

	mPlayer = (laPlayer*)lilGameObjectManager->GetGameObjectByType("Player");

	mIsWalkingLeft = false;
	mIsIdle = true;
	mAnimator->FlipAnimationX();
}

void laSnail::Update()
{
	lilVector2D velocity = mRigidbody->GetVelocity();

	if (abs(mTransform.position.x - mPlayer->mTransform.position.x) < 8.0f)
	{
		mIsWalkingLeft = true;
		mIsIdle = false;
	}

	if (mCurrentAnimation == SNAIL_DEAD)
	{
		mRigidbody->SetActive(false);
		velocity.x = 0.0f;
	}

	else
	{
		if (mIsIdle)
			velocity.x = 0.0f;

		else if (mIsWalkingLeft)
			velocity.x = lilMax(velocity.x - mWalkAcceleration, -mMaxWalkSpeed);
		else
			velocity.x = lilMin(velocity.x + mWalkAcceleration, mMaxWalkSpeed);
	}
	

	if (mAnimationLastFrame != mCurrentAnimation)
	{
		mAnimationLastFrame = mCurrentAnimation;
		mAnimator->SetCurrentAnimation((unsigned)mCurrentAnimation);
	}

	mRigidbody->SetVelocity(velocity);

	laEnemy::Update();
}

void laSnail::Destroy()
{
	laEnemy::Destroy();
}

void laSnail::BeginContact(lilRigidbody* thisRigidbody, lilRigidbody* otherRigidbody)
{
	if (thisRigidbody->colliderName->compare("Enemy") == 0 && otherRigidbody->colliderName->compare("EnemyReverse") == 0)
	{
		mIsWalkingLeft = !mIsWalkingLeft;
		mAnimator->FlipAnimationX();
	}
}

void laSnail::EndContact(lilRigidbody* thisRigidbody, lilRigidbody* otherRigidbody)
{
	/*if (thisRigidbody->colliderName->compare("attack") == 0 && otherRigidbody->colliderName->compare("playertopcollider") == 0)
	{
		m_IsAttacking = false;
	}*/
}

