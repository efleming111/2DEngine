//
//  2DEngine
//  EPhysics.cpp
//  Eric Fleming
//  5/10/2018
//

#include "EPhysics.h"
#include "../utilities/ETimer.h"

void PhysicsBody::Create(EPhysics* physics, PhysicsBodyType type, float x, float y, std::string name)
{
	m_Name = name;

	b2BodyDef bodyDef;
	bodyDef.type = (b2BodyType)type;
	bodyDef.position.Set(x, y);
	bodyDef.fixedRotation = true;
	bodyDef.userData = (void*)this;

	m_Body = physics->GetWorld()->CreateBody(&bodyDef);
}

void PhysicsBody::AddBoxCollider(float x, float y, float width, float height, bool isSensor)
{
	b2PolygonShape box;
	box.SetAsBox(width * 0.5f, height * 0.5f, b2Vec2(x, y), 0.0f);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &box;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;
	fixtureDef.isSensor = isSensor;

	m_Body->CreateFixture(&fixtureDef);
}

void ContactListener::BeginContact(b2Contact* contact)
{
	PhysicsBody* BodyA = static_cast<PhysicsBody*>(contact->GetFixtureA()->GetBody()->GetUserData());
	PhysicsBody* BodyB = static_cast<PhysicsBody*>(contact->GetFixtureB()->GetBody()->GetUserData());

	BodyA->BeginContact(BodyB);
	BodyB->BeginContact(BodyA);
}

void ContactListener::EndContact(b2Contact* contact)
{
	PhysicsBody* BodyA = static_cast<PhysicsBody*>(contact->GetFixtureA()->GetBody()->GetUserData());
	PhysicsBody* BodyB = static_cast<PhysicsBody*>(contact->GetFixtureB()->GetBody()->GetUserData());

	BodyA->EndContact(BodyB);
	BodyB->EndContact(BodyA);
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

void EPhysics::Shutdown()
{
	// TODO: Check if anything else needs deleted

	delete m_World;
}

void EPhysics::Update()
{
	m_AccumTime += lilTimer->DeltaTime();
	if (m_AccumTime < PHYSICS_TIME_STEP)
		return;

	m_AccumTime -= PHYSICS_TIME_STEP;

	m_World->Step(PHYSICS_TIME_STEP, m_VelocityIterations, m_PositionIterations);
}

