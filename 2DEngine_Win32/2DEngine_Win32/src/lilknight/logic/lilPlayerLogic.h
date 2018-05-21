//
//  lil Knight
//  lilPlayerLogic.h
//  Eric Fleming
//  5/21/2018
//

#include "../../engine/gameobjects/EGameObject.h"
#include "../../engine/input/EInput.h"
#include "../../engine/components/EPhysicsComponent.h"

// TODO: For testing only
#include <SDL.h>

#pragma once

void PlayerLogic(EGameObject* gameObject)
{
	static EPhysicsComponent* playerPhysics = (EPhysicsComponent*)gameObject->GetComponent("PlayerPhysics");

	EVector2D velocity = playerPhysics->GetVelocity();

#ifdef _WIN32
	// TODO: add is grounded sensor
	if (lilKeyboard->GetKeyDown(KC_SPACE))
	{
		velocity.y = 10.0f;
	}

	if (lilKeyboard->GetKey(KC_A) || lilKeyboard->GetKey(KC_LEFTARROW))
	{
		velocity.x = EMax(velocity.x - .2f, -5.0f);
	}

	else if (lilKeyboard->GetKey(KC_D) || lilKeyboard->GetKey(KC_RIGHTARROW))
	{
		velocity.x = EMin(velocity.x + .2f, 5.0f);
}

	else
	{
		velocity.x *= .98f;
	}
#endif

#ifdef __ANDROID__

#endif 

	playerPhysics->SetVelocity(velocity);
}

void PlayerBeginContact(EPhysicsComponent* other)
{
	SDL_Log("Player Begin Contact, %s %d", __FILE__, __LINE__);
}

void PlayerEndContact(EPhysicsComponent* other)
{
	SDL_Log("Player End Contact, %s %d", __FILE__, __LINE__);
}

