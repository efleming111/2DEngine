//
//  lil Alien
//  laCoinBox.cpp
//  Eric Fleming
//  9/11/2018
//

#include "../../../engine/gameobjects/lilGameObjectManager.h"
#include "../../../engine/utilities/lilTimer.h"

#include "laItemBox.h"

void laItemBox::Create(TiXmlElement* rootElement, float pixelsPerGameUnit)
{
	lilGameObject::Create(rootElement, pixelsPerGameUnit);

	mIsAlive = true;
	mHitBounceTime = .075f;
}

void laItemBox::OnStart()
{
	mPlayer = (laPlayer*)lilGameObjectManager->GetGameObjectByType("Player");

	mItemBox = (lilSprite*)GetComponentByName("ItemBox");
	mItemBoxHit = (lilSprite*)GetComponentByName("ItemBoxHit");

	// TODO: Add to list of items
	std::string items[] = { "YellowKeyItem", "GreenKeyItem" };
	for (int i = 0; i < 2; ++i)
	{
		mItem = (lilSprite*)GetComponentByName(items[i].c_str());
		if (mItem)
			break;
	}
}

void laItemBox::Update()
{
	if (!mIsAlive)
	{
		mHitBounceTime -= lilTimer->DeltaTime();
		MoveItem();
	}

	if (mHitBounceTime < 0.0f)
	{
		mHitBounceTime = 0.0f;
		mItemBoxHit->yRelative = 0.0f;
	}

	lilGameObject::Update();
}

void laItemBox::Destroy()
{
	lilGameObject::Destroy();
}

void laItemBox::BeginContact(lilRigidbody* thisRigidbody, lilRigidbody* otherRigidbody)
{
	if (otherRigidbody->colliderName->compare("HeadSensor") == 0)
	{
		if (mIsAlive)
		{
			mItemBox->isRendered = false;
			mItemBoxHit->isRendered = true;
			mItemBoxHit->yRelative = .15f;
			mItem->isRendered = true;
			mIsAlive = false;
			mPlayer->AddCoin();
		}

	}
}

void laItemBox::EndContact(lilRigidbody* thisRigidbody, lilRigidbody* otherRigidbody)
{
}

void laItemBox::MoveItem()
{
	if (mItem->isRendered)
		if (mItem->yRelative < 1.0f)
			mItem->yRelative += 7.0f * lilTimer->DeltaTime();
		/*else
			mItem->isRendered = false;*/
}