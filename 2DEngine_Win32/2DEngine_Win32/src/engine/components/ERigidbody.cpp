//
//  2DEngine
//  ERigidbody.cpp
//  Eric Fleming
//  5/19/2018/
//

#include "ERigidbody.h"
#include "../physics/EPhysics.h"

void ERigidbody::Create(TiXmlElement* element)
{
	colliderName = 0;

	m_Type = element->Attribute("type");

	b2BodyDef bodyDef;

	std::string bodyType = element->Attribute("bodytype");
	if (bodyType.compare("dynamic") == 0)
		bodyDef.type = b2_dynamicBody;
	else if (bodyType.compare("kinematic") == 0)
		bodyDef.type = b2_kinematicBody;
	else
		bodyDef.type = b2_staticBody;

	bodyDef.position.Set(m_GameObject->m_Transform.position.x, m_GameObject->m_Transform.position.y);

	std::string canRotate = element->Attribute("canrotate");
	if (canRotate.compare("true") == 0)
		bodyDef.fixedRotation = false;
	else
		bodyDef.fixedRotation = true;

	bodyDef.userData = (void*)this;

	m_Body = lilPhysics->AddBody(&bodyDef);

	for (TiXmlElement* colliders = element->FirstChildElement(); colliders; colliders = colliders->NextSiblingElement())
	{
		std::string colliderType = colliders->Attribute("type");
		if (colliderType.compare("box") == 0)
			AddBoxCollider(colliders);
		else if (colliderType.compare("circle") == 0)
			AddCircleCollider(colliders);
	}
}

void ERigidbody::Update()
{
	b2Vec2 pos = m_Body->GetPosition();
	m_GameObject->m_Transform.position.x = pos.x;
	m_GameObject->m_Transform.position.y = pos.y;
}

void ERigidbody::Destroy()
{
	// Empty
}

void ERigidbody::SetActive(bool isActive)
{
	m_Body->SetActive(isActive);
}

void ERigidbody::BeginContact(ERigidbody* thisRigidbody, ERigidbody* otherRigidbody)
{
	m_GameObject->BeginContact(thisRigidbody, otherRigidbody);
}

void ERigidbody::EndContact(ERigidbody* thisRigidbody, ERigidbody* otherRigidbody)
{
	m_GameObject->EndContact(thisRigidbody, otherRigidbody);
}

void ERigidbody::AddBoxCollider(TiXmlElement* element)
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
	box.SetAsBox((float)width * .5f, (float)height * .5f, b2Vec2((float)xRel, (float)yRel), (float)angle);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &box;
	fixtureDef.density = (float)density;
	fixtureDef.friction = (float)friction;

	std::string isSensor = element->Attribute("issensor");
	if (isSensor.compare("true") == 0)
		fixtureDef.isSensor = true;
	else
		fixtureDef.isSensor = false;

	std::string name = element->Attribute("name");
	m_ColliderNames.push_back(name);
	fixtureDef.userData = (void*)(&m_ColliderNames.back());

	m_Body->CreateFixture(&fixtureDef);
}

void ERigidbody::AddCircleCollider(TiXmlElement * element)
{
	double radius, xRel, yRel, density, friction;

	element->Attribute("radius", &radius);
	element->Attribute("xrel", &xRel);
	element->Attribute("yrel", &yRel);
	element->Attribute("density", &density);
	element->Attribute("friction", &friction);

	b2CircleShape circle;
	circle.m_p.Set((float)xRel, (float)yRel);
	circle.m_radius = (float)radius;

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &circle;
	fixtureDef.density = (float)density;
	fixtureDef.friction = (float)friction;

	std::string isSensor = element->Attribute("issensor");
	if (isSensor.compare("true") == 0)
		fixtureDef.isSensor = true;
	else
		fixtureDef.isSensor = false;

	std::string name = element->Attribute("name");
	m_ColliderNames.push_back(name);
	fixtureDef.userData = (void*)(&m_ColliderNames.back());

	m_Body->CreateFixture(&fixtureDef);
}

