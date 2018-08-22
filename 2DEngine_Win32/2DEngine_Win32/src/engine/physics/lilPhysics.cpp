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

laPhysics* laPhysics::s_Instance = 0;

laPhysics* laPhysics::Instance()
{
	if (!s_Instance)
		s_Instance = new laPhysics();

	return s_Instance;
}

bool laPhysics::Initialize(float xGravity, float yGravity)
{
	b2Vec2 gravity(xGravity, yGravity);
	m_World = new b2World(gravity);

	m_AccumTime = 0.0f;

	m_VelocityIterations = 6;
	m_PositionIterations = 2;

	m_World->SetContactListener(&m_ContactListener);

	return true;
}

void laPhysics::Update()
{
	m_AccumTime += lilTimer->DeltaTime();
	if (m_AccumTime < PHYSICS_TIME_STEP)
		return;

	m_AccumTime -= PHYSICS_TIME_STEP;

	m_World->Step(PHYSICS_TIME_STEP, m_VelocityIterations, m_PositionIterations);
}

void laPhysics::Shutdown()
{
	DestroyBodies();
	delete m_World;
}

b2Body* laPhysics::AddBody(const b2BodyDef* bodyDef)
{
	b2Body* tempBody = m_World->CreateBody(bodyDef);
	m_Bodies.push_back(tempBody);
	return m_Bodies.back();
}

void laPhysics::DestroyBodies()
{
	for (std::list<b2Body*>::iterator it = m_Bodies.begin(); it != m_Bodies.end(); ++it)
		m_World->DestroyBody((*it));

	m_Bodies.clear();
}


