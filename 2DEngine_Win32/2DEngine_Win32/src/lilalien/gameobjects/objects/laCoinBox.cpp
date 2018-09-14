//
//  lil Alien
//  laCoinBox.cpp
//  Eric Fleming
//  9/11/2018
//

#include "../../../engine/gameobjects/lilGameObjectManager.h"
#include "../../../engine/utilities/lilTimer.h"

#include "laCoinBox.h"

void laCoinBox::Create(TiXmlElement* rootElement, float pixelsPerGameUnit)
{
	lilGameObject::Create(rootElement, pixelsPerGameUnit);

	mIsAlive = true;
	mHitBounceTime = .075f;
}

void laCoinBox::OnStart()
{
	mPlayer = (laPlayer*)lilGameObjectManager->GetGameObjectByType("Player");

	mCoinBox = (lilSprite*)GetComponentByName("CoinBox");
	mCoinBoxHit = (lilSprite*)GetComponentByName("CoinBoxHit");
	mCoin = (lilSprite*)GetComponentByName("CoinGold");
}

void laCoinBox::Update()
{
	if (!mIsAlive)
	{
		mHitBounceTime -= lilTimer->DeltaTime();
		MoveCoin();
	}

	if (mHitBounceTime < 0.0f)
	{
		mHitBounceTime = 0.0f;
		mCoinBoxHit->yRelative = 0.0f;
	}

	lilGameObject::Update();
}

void laCoinBox::Destroy()
{
	lilGameObject::Destroy();
}

void laCoinBox::BeginContact(lilRigidbody* thisRigidbody, lilRigidbody* otherRigidbody)
{
	if (otherRigidbody->colliderName->compare("HeadSensor") == 0)
	{
		if (mIsAlive)
		{
			mCoinBox->isRendered = false;
			mCoinBoxHit->isRendered = true;
			mCoinBoxHit->yRelative = .15f;
			mCoin->isRendered = true;
			mIsAlive = false;
			mPlayer->AddCoin();
		}
		
	}
}

void laCoinBox::EndContact(lilRigidbody* thisRigidbody, lilRigidbody* otherRigidbody)
{
}

void laCoinBox::MoveCoin()
{
	if (mCoin->isRendered)
		if (mCoin->yRelative < 1.5f)
			mCoin->yRelative += 7.0f * lilTimer->DeltaTime();
		else
			mCoin->isRendered = false;
}

