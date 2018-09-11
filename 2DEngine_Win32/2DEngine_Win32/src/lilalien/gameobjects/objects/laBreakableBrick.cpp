//
//  lil Alien
//  laBreakableBrick.cpp
//  Eric Fleming
//  9/11/2018
//

#include "laBreakableBrick.h"

void laBreakableBrick::Create(TiXmlElement* rootElement, float pixelsPerGameUnit)
{
	lilGameObject::Create(rootElement, pixelsPerGameUnit);
}

void laBreakableBrick::OnStart()
{
	mBrick = (lilSprite*)GetComponentByName("BreakableBrick");
	mRigidbody = (lilRigidbody*)GetComponentByType("Rigidbody");
}

void laBreakableBrick::Update()
{
	lilGameObject::Update();
}

void laBreakableBrick::Destroy()
{
	lilGameObject::Destroy();
}

void laBreakableBrick::BeginContact(lilRigidbody* thisRigidbody, lilRigidbody* otherRigidbody)
{
	if (otherRigidbody->colliderName->compare("HeadSensor") == 0)
	{
		mBrick->isRendered = false;
		mRigidbody->SetActive(false);
	}
}

void laBreakableBrick::EndContact(lilRigidbody* thisRigidbody, lilRigidbody* otherRigidbody)
{
}

