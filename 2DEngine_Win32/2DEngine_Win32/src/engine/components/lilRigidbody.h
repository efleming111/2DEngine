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
	lilRigidbody(lilGameObject* gameObject) { m_GameObject = gameObject; }
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
	lilGameObject* GetGameObject() { return m_GameObject; }

	// Returns the velocity of the rigidbody
	lilVector2D GetVelocity() { return m_Body->GetLinearVelocity(); }
	
	// Returns the position of the rigidbody
	lilVector2D GetPosition() { return m_Body->GetPosition(); }

	// Sets the velocity of the rigidbody
	// @ vector - a 2d vector reprresenting the current velocity of the rigidbody
	void SetVelocity(lilVector2D vector) { m_Body->SetLinearVelocity(vector); }

	void SetPosition(lilVector2D position) { m_Body->SetTransform(position, 0.0f); }

	// Pointer to the name of the currently collided collider
	std::string* colliderName;

protected:
	b2Body* m_Body;

	std::list<std::string> m_ColliderNames;

private:
	// No copying
	lilRigidbody(const lilRigidbody& component) {}
	void operator=(const lilRigidbody& component) {}

	void AddBoxCollider(TiXmlElement* element);
	void AddCircleCollider(TiXmlElement* element);
};

