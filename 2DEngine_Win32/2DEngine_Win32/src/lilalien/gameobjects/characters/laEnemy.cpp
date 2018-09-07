//
//  lil Alien
//  laEnemy.cpp
//  Eric Fleming
//  6/14/2018
//

#include "laEnemy.h"

void laEnemy::Create(TiXmlElement * rootElement, float pixelsPerGameUnit)
{
	lilGameObject::Create(rootElement, pixelsPerGameUnit);
}

void laEnemy::OnStart()
{
	mRigidbody = (lilRigidbody*)GetComponentByType("Rigidbody");

	mAnimator = (lilAnimator*)GetComponentByType("Animator");

	mIsRendered = true;
}

void laEnemy::Update()
{
	lilGameObject::Update();
}

void laEnemy::Destroy()
{
	lilGameObject::Destroy();
}
