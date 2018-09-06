//
//  lil Knight
//  lilEnemy.h
//  Eric Fleming
//  6/14/2018
//

#pragma once

#include "../../../engine/gameobjects/EGameObject.h"
#include "../../../engine/components/ERigidbody.h"
#include "../../../engine/components/EAnimator.h"

class Enemy : public EGameObject
{
public:
	Enemy() {}
	virtual ~Enemy() {}

	virtual void Create(TiXmlElement* rootElement, float pixelsPerGameUnit);
	virtual void OnStart();
	virtual void Update();
	virtual void Destroy();

	virtual void Hit() = 0;

protected:
	ERigidbody* m_Rigidbody;
	EAnimator* m_Animator;
	bool m_IsRendered;

private:
	Enemy(const Enemy& enemy) {}
	void operator=(const Enemy& enemy) {}

	virtual void TakeDamage() = 0;
};
