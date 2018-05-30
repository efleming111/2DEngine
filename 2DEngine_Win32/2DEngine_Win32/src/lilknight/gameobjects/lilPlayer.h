//
//  lil Knight
//  lilPlayer.h
//  Eric Fleming
//  5/21/2018
//

#include "../../engine/gameobjects/EGameObject.h"
#include "../../engine/input/EInput.h"
#include "../../engine/components/ERigidbody.h"
#include "../../engine/components/EAnimator.h"

// TODO: For testing only
#include <SDL.h>

#pragma once

class Player : public EGameObject
{
public:
	Player() {}
	~Player() {}

	void Create(TiXmlElement* rootElement, float pixelsPerGameUnit);
	void OnStart();
	void Update();
	void Destroy();

	void BeginContact(ERigidbody* thisRigidbody, ERigidbody* otherRigidbody);
	void EndContact(ERigidbody* thisRigidbody, ERigidbody* otherRigidbody);

protected:
	ERigidbody* m_Rigidbody;
	EAnimator* m_Animator;

	bool m_IsFacingRight;

	bool m_IsGrounded;

private:
	Player(const Player& player) {}
	void operator=(const Player& player) {}
};



