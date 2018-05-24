//
//  2DEngine
//  ERigidbody.h
//  Eric Fleming
//  5/18/2018
//

#pragma once

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

	void Create(TiXmlElement* element);
	void Update();
	void Destroy();

	// Set the logic durring contact
	// @ beginContact - function for logic when contact begins
	// @ endContact - function for logic when contact ends
	void SetContactLogicFunction(void(*beginContact)(ERigidbody* other), void(*endContact)(ERigidbody* other));

	void BeginContact(ERigidbody* other);
	void EndContact(ERigidbody* other);

	EGameObject* GetGameObject() { return m_GameObject; }

	EVector2D GetVelocity() { return m_Body->GetLinearVelocity(); }
	EVector2D GetPosition() { return m_Body->GetPosition(); }

	void SetVelocity(EVector2D vector) { m_Body->SetLinearVelocity(vector); }

protected:
	void(*BeginContactLogic)(ERigidbody* other);
	void(*EndContactLogic)(ERigidbody* other);

	b2Body* m_Body;

private:
	ERigidbody(const ERigidbody& component) {}
	void operator=(const ERigidbody& component) {}

	void AddBoxCollider(TiXmlElement* element);
	void AddCircleCollider(TiXmlElement* element);
};

