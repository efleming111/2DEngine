//
//  lil Alien
//  laCoinBox.h
//  Eric Fleming
//  9/11/2018
//

#pragma once

#include "../../../engine/gameobjects/lilGameObject.h"
#include "../../../engine/components/lilRigidbody.h"
#include "../../../engine/components/lilSprite.h"
#include "../characters/laPlayer.h"

// TODO: For testing only
#include <SDL.h>

class laCoinBox : public lilGameObject
{
public:
	laCoinBox() {}
	~laCoinBox() {}
	void Create(TiXmlElement* rootElement, float pixelsPerGameUnit);
	void OnStart();
	void Update();
	void Destroy();

	void BeginContact(lilRigidbody* thisRigidbody, lilRigidbody* otherRigidbody);
	void EndContact(lilRigidbody* thisRigidbody, lilRigidbody* otherRigidbody);

private:
	laPlayer* mPlayer;

	lilSprite* mCoinBox;
	lilSprite* mCoinBoxHit;
	lilSprite* mCoin;

	float mHitBounceTime;

	bool mIsAlive;

private:
	laCoinBox(const laCoinBox& coinBox) {}
	void operator=(const laCoinBox& coinBox) {}

	void MoveCoin();
};

