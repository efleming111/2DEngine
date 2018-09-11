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
	// TODO: For testing only
	SDL_Log("Created lilPlayer, %s %d", __FILE__, __LINE__);

	lilGameObject::Create(rootElement, pixelsPerGameUnit);

	// TODO: Get player attribute here. 
	double walkAcc, maxWalkSpeed, runAcc, maxRunSpeed, jumpPower;
	rootElement->Attribute("walkacceleration", &walkAcc);
	rootElement->Attribute("maxwalkspeed", &maxWalkSpeed);
	rootElement->Attribute("runacceleration", &runAcc);
	rootElement->Attribute("maxrunspeed", &maxRunSpeed);
	rootElement->Attribute("jumppower", &jumpPower);

	mAnimationLastFrame = mCurrentAnimation = JUMP;

	mWalkAcceleration = (float)walkAcc;
	mMaxWalkSpeed = (float)maxWalkSpeed;
	mRunAcceleration = (float)runAcc;
	mMaxRunSpeed = (float)maxRunSpeed;
	mJumpPower = (float)jumpPower;

	mCoins = 1;
	mHealth = 1;
	mScore = 1;
}

void laPlayer::OnStart()
{
	mLevelController = (laLevelController*)lilGameObjectManager->GetGameObjectByType("LevelController");
	float x, y;
	mLevelController->GetPlayerStart(&x, &y);

	mRigidbody = (lilRigidbody*)GetComponentByType("Rigidbody");
	lilVector2D pos(x, y);
	mRigidbody->SetPosition(pos);

	mAnimator = (lilAnimator*)GetComponentByType("Animator");

	mIsRendered = true;

	mIsFacingRight = true;
	mIsJumping = false;
	mIsAttacking = false;
	mIsGrounded = false;

	mIsTakingDamage = false;
	mCanTakeDamage = true;
	mTotalDamageTime = 2.0f;
	mDamageBlinkInterval = .1f;
	mDamageAmount = 0;
	mAccumDamageIntervalTime = 0.0f;
}

void laPlayer::Update()
{
	lilVector2D velocity = mRigidbody->GetVelocity();

	/*if (mCurrentAnimation == DEAD)
		mRigidbody->SetActive(false);*/

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
		velocity.x *= .98f;
		if (abs(velocity.x) < .28f)
			velocity.x = 0.0f;

		if (!mIsJumping && abs(velocity.x) < .05f && !mIsAttacking)
			mIsIdle = true;
	}

	/*if (mIsTakingDamage)
		TakeDamage();*/

	/*if (mIsJumping || !mIsGrounded)
		mCurrentAnimation = JUMP;

	else if (mIsRunning)
		mCurrentAnimation = RUN;

	else if (!mIsIdle)
		mCurrentAnimation = WALK;

	else
		mCurrentAnimation = IDLE;*/

	/*if (mHealth <= 0)
	{
		mCurrentAnimation = DEAD;
		velocity.x = 0.0f;
	}

	if (mAnimationLastFrame != mCurrentAnimation)
	{
		mAnimationLastFrame = mCurrentAnimation;
		mAnimator->SetCurrentAnimation((unsigned)mCurrentAnimation);
	}*/
	
	mRigidbody->SetVelocity(velocity);

	lilGameObject::Update();
}

void laPlayer::Destroy()
{
	lilGameObject::Destroy();
}

void laPlayer::BeginContact(lilRigidbody* thisRigidbody, lilRigidbody* otherRigidbody)
{
	if (thisRigidbody->colliderName->compare("GroundSensor") == 0 && otherRigidbody->colliderName->compare("Ground") == 0)
	{
		mIsGrounded = true;
		mIsJumping = false;
	}
}

void laPlayer::EndContact(lilRigidbody* thisRigidbody, lilRigidbody* otherRigidbody)
{
	if (thisRigidbody->colliderName->compare("GroundSensor") == 0 && otherRigidbody->colliderName->compare("Ground") == 0)
	{
		mIsGrounded = false;
	}
}

void laPlayer::Hit(int amount)
{
	if (mCanTakeDamage)
	{
		mIsTakingDamage = true;
		mDamageAmount = amount;
	}
}

void laPlayer::TakeDamage()
{
	mHealth -= mDamageAmount;
	mDamageAmount = 0;
	mCanTakeDamage = false;

	mAccumDamageIntervalTime += lilTimer->DeltaTime();
	mAccumDamageTime += lilTimer->DeltaTime();

	if (mAccumDamageTime > mTotalDamageTime)
	{
		mAccumDamageIntervalTime = 0.0f;
		mAccumDamageTime = 0.0f;
		mIsTakingDamage = false;
		mCanTakeDamage = true;
		mAnimator->IsRendered(true);
		return;
	}

	if (mAccumDamageIntervalTime > mDamageBlinkInterval)
	{
		mAccumDamageIntervalTime -= mDamageBlinkInterval;
		mIsRendered = !mIsRendered;
		mAnimator->IsRendered(mIsRendered);
	}
}


