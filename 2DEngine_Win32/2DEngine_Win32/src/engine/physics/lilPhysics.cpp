//
//  2DEngine
//  lilPhysics.cpp
//  Eric Fleming
//  5/10/2018
//

#include "lilPhysics.h"
#include "../utilities/lilTimer.h"
#include "../components/lilRigidbody.h"

void lilContactListener::BeginContact(b2Contact* contact)
{
	lilRigidbody* BodyA = static_cast<lilRigidbody*>(contact->GetFixtureA()->GetBody()->GetUserData());
	lilRigidbody* BodyB = static_cast<lilRigidbody*>(contact->GetFixtureB()->GetBody()->GetUserData());

	if (contact->GetFixtureA()->IsSensor() || contact->GetFixtureB()->IsSensor())
	{
		BodyA->colliderName = (std::string*)contact->GetFixtureA()->GetUserData();
		BodyB->colliderName = (std::string*)contact->GetFixtureB()->GetUserData();

		BodyA->BeginContact(BodyA, BodyB);
		BodyB->BeginContact(BodyB, BodyA);

		BodyA->colliderName = 0;
		BodyB->colliderName = 0;
	}
}

void lilContactListener::EndContact(b2Contact* contact)
{
	lilRigidbody* BodyA = static_cast<lilRigidbody*>(contact->GetFixtureA()->GetBody()->GetUserData());
	lilRigidbody* BodyB = static_cast<lilRigidbody*>(contact->GetFixtureB()->GetBody()->GetUserData());

	if (contact->GetFixtureA()->IsSensor() || contact->GetFixtureB()->IsSensor())
	{
		BodyA->colliderName = (std::string*)contact->GetFixtureA()->GetUserData();
		BodyB->colliderName = (std::string*)contact->GetFixtureB()->GetUserData();

		BodyA->EndContact(BodyA, BodyB);
		BodyB->EndContact(BodyB, BodyA);

		BodyA->colliderName = 0;
		BodyB->colliderName = 0;
	}
}

laPhysics* laPhysics::sInstance = 0;

laPhysics* laPhysics::Instance()
{
	if (!sInstance)
		sInstance = new laPhysics();

	return sInstance;
}

bool laPhysics::Initialize(float xGravity, float yGravity)
{
	b2Vec2 gravity(xGravity, yGravity);
	mWorld = new b2World(gravity);

	mAccumTime = 0.0f;

	mVelocityIterations = 6;
	mPositionIterations = 2;

	mWorld->SetContactListener(&mContactListener);

	return true;
}

void laPhysics::Update()
{
	mAccumTime += lilTimer->DeltaTime();
	if (mAccumTime < PHYSICS_TIME_STEP)
		return;

	mAccumTime -= PHYSICS_TIME_STEP;

	mWorld->Step(PHYSICS_TIME_STEP, mVelocityIterations, mPositionIterations);
}

void laPhysics::Shutdown()
{
	DestroyBodies();
	delete mWorld;
}

b2Body* laPhysics::AddBody(const b2BodyDef* bodyDef)
{
	b2Body* tempBody = mWorld->CreateBody(bodyDef);
	mBodies.push_back(tempBody);
	return mBodies.back();
}

void laPhysics::DestroyBodies()
{
	for (std::list<b2Body*>::iterator it = mBodies.begin(); it != mBodies.end(); ++it)
		mWorld->DestroyBody((*it));

	mBodies.clear();
}


