//
//  2DEngine
//  EPhysics.cpp
//  Eric Fleming
//  5/10/2018
//

#include "EPhysics.h"
#include "../utilities/ETimer.h"
#include "../components/EPhysicsComponent.h"

void ContactListener::BeginContact(b2Contact* contact)
{
	EPhysicsComponent* BodyA = static_cast<EPhysicsComponent*>(contact->GetFixtureA()->GetBody()->GetUserData());
	EPhysicsComponent* BodyB = static_cast<EPhysicsComponent*>(contact->GetFixtureB()->GetBody()->GetUserData());

	BodyA->BeginContact(BodyB);
	BodyB->BeginContact(BodyA);
}

void ContactListener::EndContact(b2Contact* contact)
{
	EPhysicsComponent* BodyA = static_cast<EPhysicsComponent*>(contact->GetFixtureA()->GetBody()->GetUserData());
	EPhysicsComponent* BodyB = static_cast<EPhysicsComponent*>(contact->GetFixtureB()->GetBody()->GetUserData());

	BodyA->EndContact(BodyB);
	BodyB->EndContact(BodyA);
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

void EPhysics::AddBody(b2Body* body, const b2BodyDef* bodyDef)
{
	body = m_World->CreateBody(bodyDef);
	m_Bodies.push_back(body);
}

void EPhysics::DestroyBodies()
{
	for (unsigned i = 0; i < m_Bodies.size(); ++i)
		m_World->DestroyBody(m_Bodies[i]);

	m_Bodies.resize(0);
}


