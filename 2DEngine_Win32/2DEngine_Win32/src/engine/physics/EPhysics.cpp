//
//  2DEngine
//  EPhysics.cpp
//  Eric Fleming
//  5/10/2018
//

#include "EPhysics.h"
#include "../utilities/ETimer.h"
#include "../components/ERigidbody.h"

void ContactListener::BeginContact(b2Contact* contact)
{
	ERigidbody* BodyA = static_cast<ERigidbody*>(contact->GetFixtureA()->GetBody()->GetUserData());
	ERigidbody* BodyB = static_cast<ERigidbody*>(contact->GetFixtureB()->GetBody()->GetUserData());

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

void ContactListener::EndContact(b2Contact* contact)
{
	ERigidbody* BodyA = static_cast<ERigidbody*>(contact->GetFixtureA()->GetBody()->GetUserData());
	ERigidbody* BodyB = static_cast<ERigidbody*>(contact->GetFixtureB()->GetBody()->GetUserData());

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

EPhysics* EPhysics::s_Instance = 0;

EPhysics* EPhysics::Instance()
{
	if (!s_Instance)
		s_Instance = new EPhysics();

	return s_Instance;
}

bool EPhysics::Initialize(float xGravity, float yGravity)
{
	b2Vec2 gravity(xGravity, yGravity);
	m_World = new b2World(gravity);

	m_AccumTime = 0.0f;

	m_VelocityIterations = 6;
	m_PositionIterations = 2;

	m_World->SetContactListener(&m_ContactListener);

	return true;
}

void EPhysics::Update()
{
	m_AccumTime += lilTimer->DeltaTime();
	if (m_AccumTime < PHYSICS_TIME_STEP)
		return;

	m_AccumTime -= PHYSICS_TIME_STEP;

	m_World->Step(PHYSICS_TIME_STEP, m_VelocityIterations, m_PositionIterations);
}

void EPhysics::Shutdown()
{
	DestroyBodies();
	delete m_World;
}

b2Body* EPhysics::AddBody(const b2BodyDef* bodyDef)
{
	b2Body* tempBody = m_World->CreateBody(bodyDef);
	m_Bodies.push_back(tempBody);
	return m_Bodies.back();
}

void EPhysics::DestroyBodies()
{
	for (std::list<b2Body*>::iterator it = m_Bodies.begin(); it != m_Bodies.end(); ++it)
		m_World->DestroyBody((*it));

	m_Bodies.clear();
}


