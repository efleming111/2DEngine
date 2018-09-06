//
//  lil Alien
//  laLevelObject.cpp
//  Eric Fleming
//  5/21/2018
//

#include "laLevelObject.h"

void laLevelObject::Create(TiXmlElement* rootElement, float pixelsPerGameUnit)
{
	lilGameObject::Create(rootElement, pixelsPerGameUnit);
}

void laLevelObject::OnStart()
{
	// Empty
}

void laLevelObject::Update()
{
	lilGameObject::Update();
}

void laLevelObject::Destroy()
{
	lilGameObject::Destroy();
}

void laLevelObject::BeginContact(lilRigidbody* thisRigidbody, lilRigidbody* otherRigidbody)
{
}

void laLevelObject::EndContact(lilRigidbody* thisRigidbody, lilRigidbody* otherRigidbody)
{
}

