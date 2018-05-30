//
//  2DEngine
//  EPhysics.h
//  Eric Fleming
//  5/10/2018
//

#pragma once

#include <list>

#include <Box2D\Box2D.h>

#define EVector2D b2Vec2
#define EMax b2Max
#define EMin b2Min

const float PHYSICS_TIME_STEP = 1.0f / 60.0f;

class ContactListener : public b2ContactListener
{
	void BeginContact(b2Contact* contact);
	void EndContact(b2Contact* contact);
};

#define lilPhysics EPhysics::Instance()

class EPhysics
{
public:
	// Returns only instance of class
	static EPhysics* Instance();

	// Initialize physics engine with gravity
	// @ xGravity - x gravity amount
	// @ yGravity - y gravity amount
	bool Initialize(float xGravity, float yGravity);

	// Update the physics engine
	void Update();

	// Shuts down and cleans up physics engine
	void Shutdown();

	// Adds a body to the physics engine
	// @ body - pointer to the body being added
	// @ bodyDef - Reference to the body's definetion
	b2Body* AddBody(const b2BodyDef* bodyDef);

	// Clear all the current bodies in the physics engine
	void DestroyBodies();

private:
	static EPhysics* s_Instance;

	b2World * m_World;
	std::list<b2Body*> m_Bodies;

	int32 m_VelocityIterations;
	int32 m_PositionIterations;

	ContactListener m_ContactListener;

	float m_AccumTime;

private:
	// Only one instance of class and no copying
	EPhysics() {}
	~EPhysics() {}
	EPhysics(const EPhysics& physics) {}
	void operator=(const EPhysics& physics) {}
};

