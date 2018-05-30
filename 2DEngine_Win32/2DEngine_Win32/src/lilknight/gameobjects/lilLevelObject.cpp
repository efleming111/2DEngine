//
//  lil Knight
//  lilLevelLogic.h
//  Eric Fleming
//  5/21/2018
//

#include "lilLevelObject.h"

void LevelObject::Create(TiXmlElement* rootElement, float pixelsPerGameUnit)
{
	EGameObject::Create(rootElement, pixelsPerGameUnit);
}

void LevelObject::OnStart()
{
}

void LevelObject::Update()
{
	EGameObject::Update();
}

void LevelObject::Destroy()
{
	EGameObject::Destroy();
}

void LevelObject::BeginContact(ERigidbody* thisRigidbody, ERigidbody* otherRigidbody)
{
}

void LevelObject::EndContact(ERigidbody* thisRigidbody, ERigidbody* otherRigidbody)
{
}


