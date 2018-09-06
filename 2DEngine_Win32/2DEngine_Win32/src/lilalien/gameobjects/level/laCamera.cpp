//
//  lil Alien
//  laCamera.cpp
//  Eric Fleming
//  5/17/2018
//

#include "laCamera.h"

void laCamera::Create(TiXmlElement* rootElement, float pixelsPerGameUnit)
{
	lilGameObject::Create(rootElement, pixelsPerGameUnit);
}

void laCamera::OnStart()
{
	mPlayer = (laPlayer*)lilGameObjectManager->GetGameObjectByName("Player");
}

void laCamera::Update()
{
	if (mPlayer->mTransform.position.x > mTransform.position.x + 3.0f)
		mTransform.position.x = mPlayer->mTransform.position.x - 3.0f;

	else if (mPlayer->mTransform.position.x < mTransform.position.x - 3.0f)
		mTransform.position.x = mPlayer->mTransform.position.x + 3.0f;

	// TODO: set y in OnStart() and check for level begining and end
	if (mPlayer->mTransform.position.y > mTransform.position.y + 3.0f)
		mTransform.position.y = mPlayer->mTransform.position.y - 3.0f;

	else if (mPlayer->mTransform.position.y < mTransform.position.y - 3.0f)
		mTransform.position.y = mPlayer->mTransform.position.y + 3.0f;

	lilGameObject::Update();
}

void laCamera::Destroy()
{
	lilGameObject::Destroy();
}
