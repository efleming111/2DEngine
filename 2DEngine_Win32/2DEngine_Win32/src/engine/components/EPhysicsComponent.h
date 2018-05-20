//
//  2DEngine
//  EPhysicsComponent.h
//  Eric Fleming
//  5/18/2018
//

#pragma once

#include <Box2D\Box2D.h>

#include "EComponent.h"

#define EVector2D b2Vec2
#define EMax b2Max
#define EMin b2Min

class EPhysicsComponent : public EComponent
{
public:
	EPhysicsComponent(EGameObject* gameObject) { m_GameObject = gameObject; }
	~EPhysicsComponent() {}

	void Create(TiXmlElement* element);
	void Update();
	void Destroy();

	// Set the logic durring contact
	// @ beginContact - function for logic when contact begins
	// @ endContact - function for logic when contact ends
	void SetContactLogicFunction(void(*beginContact)(EPhysicsComponent* other), void(*endContact)(EPhysicsComponent* other));

	void BeginContact(EPhysicsComponent* other);
	void EndContact(EPhysicsComponent* other);

protected:
	void(*BeginContactLogic)(EPhysicsComponent* other);
	void(*EndContactLogic)(EPhysicsComponent* other);

	b2Body* m_Body;

private:
	EPhysicsComponent(const EPhysicsComponent& component) {}
	void operator=(const EPhysicsComponent& component) {}

	void AddBoxCollider(TiXmlElement* element);
};

