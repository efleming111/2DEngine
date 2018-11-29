//
//  lil Alien
//  laPlayer.cpp
//  Eric Fleming
//  5/22/2018
//

#include "laPlayer.h"
#include "../../../engine/utilities/lilTimer.h"
#include "../../../engine/gameobjects/lilGameObjectManager.h"
#include "../../../engine/renderer/lilGLRenderer.h"

void laPlayer::Create(TiXmlElement* rootElement, float pixelsPerGameUnit)
{
	lilGameObject::Create(rootElement, pixelsPerGameUnit);

	// TODO: Get player attribute here. 
	double gravityScale, walkAcc, maxWalkSpeed, runAcc, maxRunSpeed, jumpPower;
	rootElement->Attribute("gravityscale", &gravityScale);
	rootElement->Attribute("walkacceleration", &walkAcc);
	rootElement->Attribute("maxwalkspeed", &maxWalkSpeed);
	rootElement->Attribute("runacceleration", &runAcc);
	rootElement->Attribute("maxrunspeed", &maxRunSpeed);
	rootElement->Attribute("jumppower", &jumpPower);

	mAnimationLastFrame = mCurrentAnimation = FACE;

	mGravityScale = (float)gravityScale;
	mWalkAcceleration = (float)walkAcc;
	mMaxWalkSpeed = (float)maxWalkSpeed;
	mRunAcceleration = (float)runAcc;
	mMaxRunSpeed = (float)maxRunSpeed;
	mJumpPower = (float)jumpPower;

	mCoins = 00;
	for (int i = 0; i < 4; ++i)
		mKeys[i] = false;
	mScore = 0000000;
}

void laPlayer::OnStart()
{
	mLevelController = (laLevelController*)lilGameObjectManager->GetGameObjectByType("LevelController");
	float x, y;
	mLevelController->GetPlayerStart(&x, &y);

	mRigidbody = (lilRigidbody*)GetComponentByType("Rigidbody");
	lilVector2D pos(x, y);
	mRigidbody->SetPosition(pos);
	mRigidbody->SetOwnGravityScale(mGravityScale);

	mAnimator = (lilAnimator*)GetComponentByType("Animator");

	mIsRendered = true;

	mIsFacingRight = true;
	mIsJumping = false;
	mIsGrounded = false;
}

void laPlayer::Update()
{
	lilVector2D velocity = mRigidbody->GetVelocity();

	// TODO: Handler player dying

	if (lilInput->GetButtonDown("Jump") && mIsGrounded)
	{
		velocity.y = mJumpPower;
		mIsJumping = true;
	}

	else if (!mIsGrounded)
		mIsJumping = true;
	
	if (lilInput->GetButton("Left"))
	{
		mIsIdle = false;

		if (mIsFacingRight)
		{
			mAnimator->FlipAnimationX();
			mIsFacingRight = false;
		}

		if (lilInput->GetButton("Run"))
		{
			velocity.x = lilMax(velocity.x - mRunAcceleration, -mMaxRunSpeed);

			if (!mIsJumping)
				mIsRunning = true;
		}

		else
		{
			velocity.x = lilMax(velocity.x - mWalkAcceleration, -mMaxWalkSpeed);

			if (!mIsJumping)
				mIsRunning = false;
		}
	}
	
	else if (lilInput->GetButton("Right"))
	{
		mIsIdle = false;

		if (!mIsFacingRight)
		{
			mAnimator->FlipAnimationX();
			mIsFacingRight = true;
		}

		if (lilInput->GetButton("Run"))
		{
			velocity.x = lilMin(velocity.x + mRunAcceleration, mMaxRunSpeed);

			if (!mIsJumping)
				mIsRunning = true;
		}

		else
		{
			velocity.x = lilMin(velocity.x + mWalkAcceleration, mMaxWalkSpeed);

			if (!mIsJumping)
				mIsRunning = false;
		}
	}
	
	else
	{
		velocity.x *= .96f;
		if (abs(velocity.x) < .3f)
			velocity.x = 0.0f;

		if (!mIsJumping && abs(velocity.x) < .05f)
			mIsIdle = true;
	}

	if (mIsJumping || !mIsGrounded)
		mCurrentAnimation = JUMP;

	else if (mIsRunning)
	{
		mCurrentAnimation = WALK;
		mAnimator->SetCurrentAnimationIntervalTime(.75f);
	}

	else if (!mIsIdle)
	{
		mCurrentAnimation = WALK;
		mAnimator->SetCurrentAnimationIntervalTime(.125f);
	}
		

	else
		mCurrentAnimation = FACE;

	if (mAnimationLastFrame != mCurrentAnimation)
	{
		mAnimationLastFrame = mCurrentAnimation;
		mAnimator->SetCurrentAnimation((unsigned)mCurrentAnimation);
	}
	
	mRigidbody->SetVelocity(velocity);

	lilGameObject::Update();
}

void laPlayer::Destroy()
{
	lilGameObject::Destroy();
}

void laPlayer::BeginContact(lilRigidbody* thisRigidbody, lilRigidbody* otherRigidbody)
{
	if (thisRigidbody->colliderName->compare("GroundSensor") == 0 && 
		(otherRigidbody->colliderName->compare("Ground") == 0 || otherRigidbody->colliderName->compare("ItemBox") == 0 || otherRigidbody->colliderName->compare("CoinBox") == 0 ||
			otherRigidbody->colliderName->compare("BreakableBrick") == 0))
	{
		mIsGrounded = true;
		mIsJumping = false;
	}

	if (thisRigidbody->colliderName->compare("HeadSensor") == 0 && otherRigidbody->colliderName->compare("BreakableBrick") == 0)
	{
		mScore += 10;
	}
}

void laPlayer::EndContact(lilRigidbody* thisRigidbody, lilRigidbody* otherRigidbody)
{
	if (thisRigidbody->colliderName->compare("GroundSensor") == 0 && otherRigidbody->colliderName->compare("Ground") == 0)
	{
		mIsGrounded = false;
	}
}

void laPlayer::AddKey(int index)
{
	if (index >= 0 && index < 4)
		mKeys[index] = true;
}

bool laPlayer::GetKey(int index)
{
	if (index >= 0 && index < 4)
		return mKeys[index];

	return false;
}



