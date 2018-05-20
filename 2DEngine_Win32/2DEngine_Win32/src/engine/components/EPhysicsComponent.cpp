//
//  2DEngine
//  EPhysicsComponent.cpp
//  Eric Fleming
//  5/19/2018/
//

#include <string>

#include "EPhysicsComponent.h"
#include "../physics/EPhysics.h"

void EPhysicsComponent::Create(TiXmlElement* element)
{
	m_Name = element->Attribute("name");

	b2BodyDef bodyDef;

	std::string bodyType = element->Attribute("bodytype");
	if (bodyType.compare("dynamic") == 0)
		bodyDef.type = b2_dynamicBody;
	else if (bodyType.compare("kinematic") == 0)
		bodyDef.type = b2_kinematicBody;
	else
		bodyDef.type = b2_staticBody;

	bodyDef.position.Set(m_GameObject->m_Transform.position.x, m_GameObject->m_Transform.position.y);

	std::string canRotate = element->Attribute("canRotate");
	if (canRotate.compare("true") == 0)
		bodyDef.fixedRotation = false;
	else
		bodyDef.fixedRotation = true;

	bodyDef.userData = (void*)this;

	lilPhysics->AddBody(m_Body, &bodyDef);

	for (TiXmlElement* colliders = element->FirstChildElement(); colliders; colliders = colliders->NextSiblingElement())
		AddBoxCollider(colliders);
}

void EPhysicsComponent::Update()
{
	// Empty
}

void EPhysicsComponent::Destroy()
{
	BeginContactLogic = 0;
	EndContactLogic = 0;
}

void EPhysicsComponent::SetContactLogicFunction(void(*beginContact)(EPhysicsComponent *other), void(*endContact)(EPhysicsComponent *other))
{
	BeginContactLogic = beginContact;
	EndContactLogic = endContact;
}

void EPhysicsComponent::BeginContact(EPhysicsComponent* other)
{
	BeginContactLogic(other);
}

void EPhysicsComponent::EndContact(EPhysicsComponent* other)
{
	EndContactLogic(other);
}

void EPhysicsComponent::AddBoxCollider(TiXmlElement* element)
{
	double width, height, xRel, yRel, angle, density, friction;

	element->Attribute("width", &width);
	element->Attribute("height", &height);
	element->Attribute("xrel", &xRel);
	element->Attribute("yrel", &yRel);
	element->Attribute("angle", &angle);
	element->Attribute("density", &density);
	element->Attribute("friction", &friction);

	b2PolygonShape box;
	box.SetAsBox((float)width * .5f, (float)height * .5f, b2Vec2(m_GameObject->m_Transform.position.x + (float)xRel, m_GameObject->m_Transform.position.y + (float)yRel), (float)angle);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &box;
	fixtureDef.density = (float)density;
	fixtureDef.friction = (float)friction;

	m_Body->CreateFixture(&fixtureDef);
}
