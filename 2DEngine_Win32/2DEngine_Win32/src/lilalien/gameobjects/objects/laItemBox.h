//
//  lil Alien
//  laItemBox.h
//  Eric Fleming
//  9/17/2018
//

#pragma once

#include "../../../engine/gameobjects/lilGameObject.h"
#include "../../../engine/components/lilRigidbody.h"
#include "../../../engine/components/lilSprite.h"
#include "../characters/laPlayer.h"

// TODO: For testing only
#include <SDL.h>

class laItemBox : public lilGameObject
{
public:
	laItemBox() {}
	~laItemBox() {}
	void Create(TiXmlElement* rootElement, float pixelsPerGameUnit);
	void OnStart();
	void Update();
	void Destroy();

	void BeginContact(lilRigidbody* thisRigidbody, lilRigidbody* otherRigidbody);
	void EndContact(lilRigidbody* thisRigidbody, lilRigidbody* otherRigidbody);

private:
	laPlayer* mPlayer;

	lilSprite* mItemBox;
	lilSprite* mItemBoxHit;
	lilSprite* mItem;

	float mHitBounceTime;

	bool mIsAlive;

private:
	laItemBox(const laItemBox& coinBox) {}
	void operator=(const laItemBox& coinBox) {}

	void MoveItem();
};
