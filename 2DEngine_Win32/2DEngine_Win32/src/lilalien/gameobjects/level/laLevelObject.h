//
//  lil Alien
//  laLevelObject.h
//  Eric Fleming
//  5/21/2018
//

#pragma once

#include "../../../engine/gameobjects/lilGameObject.h"
#include "../../../engine/components/lilRigidbody.h"
#include "../../../engine/components/lilSprite.h"

// TODO: For testing only
#include <SDL.h>

class laLevelObject : public lilGameObject
{
public:
	laLevelObject() {}
	~laLevelObject() {}
	void Create(TiXmlElement* rootElement, float pixelsPerGameUnit);
	void OnStart();
	void Update();
	void Destroy();

	void BeginContact(lilRigidbody* thisRigidbody, lilRigidbody* otherRigidbody);
	void EndContact(lilRigidbody* thisRigidbody, lilRigidbody* otherRigidbody);

private:

private:
	laLevelObject(const laLevelObject& levelObject) {}
	void operator=(const laLevelObject& levelObject) {}
};

