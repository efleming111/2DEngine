//
//  lil Alien
//  laBeakableBrick.h
//  Eric Fleming
//  9/11/2018
//

#pragma once

#include "../../../engine/gameobjects/lilGameObject.h"
#include "../../../engine/components/lilRigidbody.h"
#include "../../../engine/components/lilSprite.h"

// TODO: For testing only
#include <SDL.h>

class laBreakableBrick : public lilGameObject
{
public:
	laBreakableBrick() {}
	~laBreakableBrick() {}
	void Create(TiXmlElement* rootElement, float pixelsPerGameUnit);
	void OnStart();
	void Update();
	void Destroy();

	void BeginContact(lilRigidbody* thisRigidbody, lilRigidbody* otherRigidbody);
	void EndContact(lilRigidbody* thisRigidbody, lilRigidbody* otherRigidbody);

private:
	lilSprite* mBrick;
	lilRigidbody* mRigidbody;

private:
	laBreakableBrick(const laBreakableBrick& levelObject) {}
	void operator=(const laBreakableBrick& levelObject) {}
};

