//
//  2DEngine
//  ERigidbody.h
//  Eric Fleming
//  5/18/2018
//

#pragma once

#include <list>
#include <string>

#include <Box2D\Box2D.h>

#include "EComponent.h"

#define EVector2D b2Vec2
#define EMax b2Max
#define EMin b2Min

class ERigidbody : public EComponent
{
public:
	ERigidbody(EGameObject* gameObject) { m_GameObject = gameObject; }
	~ERigidbody() {}

	// Creates a rigidbody
	// @ element - data for setting up the rigidbody
	void Create(TiXmlElement* element);
	
	// Update the game object of the rigidbodies position
	void Update();
	
	// Does nothing
	void Destroy();

	// Call back funciton for collision begin events
	// Gameobject sub classes should override this function
	void BeginContact(ERigidbody* thisRigidbody, ERigidbody* otherRigidbody);
	
	// Call back funciton for collision end events
	// Gameobject sub classes should override this function
	void EndContact(ERigidbody* thisRigidbody, ERigidbody* otherRigidbody);

	// Returns the gameobject this rigidbody is attached to
	EGameObject* GetGameObject() { return m_GameObject; }

	// Returns the velocity of the rigidbody
	EVector2D GetVelocity() { return m_Body->GetLinearVelocity(); }
	
	// Returns the position of the rigidbody
	EVector2D GetPosition() { return m_Body->GetPosition(); }

	// Sets the velocity of the rigidbody
	// @ vector - a 2d vector reprresenting the current velocity of the rigidbody
	void SetVelocity(EVector2D vector) { m_Body->SetLinearVelocity(vector); }

	// Pointer to the name of the currently collided collider
	std::string* colliderName;

protected:
	b2Body* m_Body;

	std::list<std::string> m_ColliderNames;

private:
	// No copying
	ERigidbody(const ERigidbody& component) {}
	void operator=(const ERigidbody& component) {}

	void AddBoxCollider(TiXmlElement* element);
	void AddCircleCollider(TiXmlElement* element);
};

