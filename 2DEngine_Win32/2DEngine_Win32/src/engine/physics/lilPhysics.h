//
//  2DEngine
//  lilPhysics.h
//  Eric Fleming
//  5/10/2018
//

#pragma once

#include <list>

#include <Box2D\Box2D.h>

#define lilVector2D b2Vec2
#define lilMax b2Max
#define lilMin b2Min

const float PHYSICS_TIME_STEP = 1.0f / 60.0f;

class lilContactListener : public b2ContactListener
{
	void BeginContact(b2Contact* contact);
	void EndContact(b2Contact* contact);
};

#define lilPhysics laPhysics::Instance()

class laPhysics
{
public:
	// Returns only instance of class
	static laPhysics* Instance();

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
	static laPhysics* sInstance;

	b2World * mWorld;
	std::list<b2Body*> mBodies;

	int32 mVelocityIterations;
	int32 mPositionIterations;

	lilContactListener mContactListener;

	float mAccumTime;

private:
	// Only one instance of class and no copying
	laPhysics() {}
	~laPhysics() {}
	laPhysics(const laPhysics& physics) {}
	void operator=(const laPhysics& physics) {}
};

