//
//  2DEngine
//  lilRigidbody.h
//  Eric Fleming
//  5/18/2018
//

#pragma once

#include <list>
#include <string>

#include <Box2D\Box2D.h>

#include "lilComponent.h"

#define lilVector2D b2Vec2
#define lilMax b2Max
#define lilMin b2Min

class lilRigidbody : public lilComponent
{
public:
	lilRigidbody(lilGameObject* gameObject) { mGameObject = gameObject; }
	~lilRigidbody() {}

	// Creates a rigidbody
	// @ element - data for setting up the rigidbody
	void Create(TiXmlElement* element);
	
	// Update the game object of the rigidbodies position
	void Update();
	
	// Does nothing
	void Destroy();

	// Set weather rigidbody is active
	void SetActive(bool isActive);

	// Call back funciton for collision begin events
	// Gameobject sub classes should override this function
	void BeginContact(lilRigidbody* thisRigidbody, lilRigidbody* otherRigidbody);
	
	// Call back funciton for collision end events
	// Gameobject sub classes should override this function
	void EndContact(lilRigidbody* thisRigidbody, lilRigidbody* otherRigidbody);

	// Returns the gameobject this rigidbody is attached to
	lilGameObject* GetGameObject() { return mGameObject; }

	// Returns the velocity of the rigidbody
	lilVector2D GetVelocity() { return mBody->GetLinearVelocity(); }
	
	// Returns the position of the rigidbody
	lilVector2D GetPosition() { return mBody->GetPosition(); }

	// Sets the velocity of the rigidbody
	// @ vector - a 2d vector reprresenting the current velocity of the rigidbody
	void SetVelocity(lilVector2D vector) { mBody->SetLinearVelocity(vector); }

	void SetPosition(lilVector2D position) { mBody->SetTransform(position, 0.0f); }

	// Pointer to the name of the currently collided collider
	std::string* colliderName;

protected:
	b2Body* mBody;

	std::list<std::string> mColliderNames;

private:
	// No copying
	lilRigidbody(const lilRigidbody& component) {}
	void operator=(const lilRigidbody& component) {}

	void AddBoxCollider(TiXmlElement* element);
	void AddCircleCollider(TiXmlElement* element);
};

