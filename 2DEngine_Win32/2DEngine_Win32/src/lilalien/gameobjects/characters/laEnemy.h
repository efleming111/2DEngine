//
//  lil Alien
//  laEnemy.h
//  Eric Fleming
//  6/14/2018
//

#pragma once

#include "../../../engine/gameobjects/lilGameObject.h"
#include "../../../engine/components/lilRigidbody.h"
#include "../../../engine/components/lilAnimator.h"

class laEnemy : public lilGameObject
{
public:
	laEnemy() {}
	virtual ~laEnemy() {}

	virtual void Create(TiXmlElement* rootElement, float pixelsPerGameUnit);
	virtual void OnStart();
	virtual void Update();
	virtual void Destroy();

	virtual void Hit() = 0;

protected:
	lilRigidbody* mRigidbody;
	lilAnimator* mAnimator;
	bool mIsRendered;

private:
	laEnemy(const laEnemy& enemy) {}
	void operator=(const laEnemy& enemy) {}

	virtual void TakeDamage() = 0;
};
