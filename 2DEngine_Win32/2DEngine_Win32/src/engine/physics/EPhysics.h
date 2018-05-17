//
//  2DEngine
//  EPhysics.h
//  Eric Fleming
//  5/10/2018
//

#pragma once

#include <string>

#include <Box2D\Box2D.h>

#define EVector2D b2Vec2
#define EMax b2Max
#define EMin b2Min

enum PhysicsBodyType {
	STATIC_BODY = b2_staticBody,
	KINEMATIC_BODY = b2_kinematicBody,
	DYNAMIC_BODY = b2_dynamicBody
};

const float PHYSICS_TIME_STEP = 1.0f / 60.0f;

class PhysicsBody;

class ContactListener : public b2ContactListener
{
	void BeginContact(b2Contact* contact);
	void EndContact(b2Contact* contact);
};

class EPhysics
{
public:
	EPhysics() {}
	~EPhysics() {}

	bool Initialize(float xGravity, float yGravity);
	void Shutdown();
	void Update();

	b2World* GetWorld() { return m_World; }

private:
	b2World * m_World;

	int32 m_VelocityIterations;
	int32 m_PositionIterations;

	ContactListener m_ContactListener;

	float m_AccumTime;

private:
	EPhysics(const EPhysics& physics) {}
	void operator=(const EPhysics& physics) {}
};

class PhysicsBody
{
public:
	PhysicsBody() {}
	virtual ~PhysicsBody() {}

	void Create(EPhysics* physics, PhysicsBodyType type, float x, float y, std::string name);

	void AddBoxCollider(float x, float y, float width, float height, bool isSensor);

	virtual void BeginContact(PhysicsBody* other) {}
	virtual void EndContact(PhysicsBody* other) {}

	std::string& GetName() { return m_Name; }

	EVector2D GetVelocity() { return m_Body->GetLinearVelocity(); }
	EVector2D GetPosition() { return m_Body->GetPosition(); }

	void SetVelocity(EVector2D vector) { m_Body->SetLinearVelocity(vector); }

private:
	b2Body * m_Body;

	std::string m_Name;
};

