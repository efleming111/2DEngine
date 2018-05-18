//
//  2DEngine
//  EPhysicsComponent.h
//  Eric Fleming
//  5/18/2018/2018
//

#pragma once

#include <Box2D\Box2D.h>

#include "EComponent.h"

#define EVector2D b2Vec2
#define EMax b2Max
#define EMin b2Min

enum PhysicsBodyType {
	STATIC_BODY = b2_staticBody,
	KINEMATIC_BODY = b2_kinematicBody,
	DYNAMIC_BODY = b2_dynamicBody
};

class EPhysicsComponent : public EComponent
{
public:
	EPhysicsComponent(EGameObject* gameObject) { m_GameObject = gameObject; }
	~EPhysicsComponent() {}

	void Create(TiXmlElement* element);
	void Update();
	void Destroy();

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

