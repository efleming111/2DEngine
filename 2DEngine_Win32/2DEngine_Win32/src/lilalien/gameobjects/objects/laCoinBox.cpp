//
//  lil Alien
//  laCoinBox.cpp
//  Eric Fleming
//  9/11/2018
//

#include "laCoinBox.h"

void laCoinBox::Create(TiXmlElement* rootElement, float pixelsPerGameUnit)
{
	lilGameObject::Create(rootElement, pixelsPerGameUnit);
}

void laCoinBox::OnStart()
{
	mCoinBox = (lilSprite*)GetComponentByName("CoinBox");
	mCoinBoxHit = (lilSprite*)GetComponentByName("CoinBoxHit");
}

void laCoinBox::Update()
{
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
		mCoinBox->isRendered = false;
		mCoinBoxHit->isRendered = true;
	}
}

void laCoinBox::EndContact(lilRigidbody* thisRigidbody, lilRigidbody* otherRigidbody)
{
}

