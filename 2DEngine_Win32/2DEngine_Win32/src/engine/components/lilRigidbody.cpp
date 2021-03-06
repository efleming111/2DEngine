//
//  2DEngine
//  lilRigidbody.cpp
//  Eric Fleming
//  5/19/2018/
//

#include "lilRigidbody.h"
#include "../physics/lilPhysics.h"

void lilRigidbody::Create(TiXmlElement* element)
{
	colliderName = 0;

	mType = element->Attribute("type");

	b2BodyDef bodyDef;

	std::string bodyType = element->Attribute("bodytype");
	if (bodyType.compare("dynamic") == 0)
		bodyDef.type = b2_dynamicBody;
	else if (bodyType.compare("kinematic") == 0)
		bodyDef.type = b2_kinematicBody;
	else
		bodyDef.type = b2_staticBody;

	bodyDef.position.Set(mGameObject->mTransform.position.x, mGameObject->mTransform.position.y);

	std::string canRotate = element->Attribute("canrotate");
	if (canRotate.compare("true") == 0)
		bodyDef.fixedRotation = false;
	else
		bodyDef.fixedRotation = true;

	bodyDef.userData = (void*)this;

	mBody = lilPhysics->AddBody(&bodyDef);

	for (TiXmlElement* colliders = element->FirstChildElement(); colliders; colliders = colliders->NextSiblingElement())
	{
		std::string colliderType = colliders->Attribute("type");
		if (colliderType.compare("Box") == 0)
			AddBoxCollider(colliders);
		else if (colliderType.compare("Circle") == 0)
			AddCircleCollider(colliders);
	}
}

void lilRigidbody::Update()
{
	b2Vec2 pos = mBody->GetPosition();
	mGameObject->mTransform.position.x = pos.x;
	mGameObject->mTransform.position.y = pos.y;
}

void lilRigidbody::Destroy()
{
	// Empty
}

void lilRigidbody::SetActive(bool isActive)
{
	mBody->SetActive(isActive);
}

void lilRigidbody::BeginContact(lilRigidbody* thisRigidbody, lilRigidbody* otherRigidbody)
{
	mGameObject->BeginContact(thisRigidbody, otherRigidbody);
}

void lilRigidbody::EndContact(lilRigidbody* thisRigidbody, lilRigidbody* otherRigidbody)
{
	mGameObject->EndContact(thisRigidbody, otherRigidbody);
}

void lilRigidbody::AddBoxCollider(TiXmlElement* element)
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
	mColliderNames.push_back(name);
	fixtureDef.userData = (void*)(&mColliderNames.back());

	mBody->CreateFixture(&fixtureDef);
}

void lilRigidbody::AddCircleCollider(TiXmlElement * element)
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
	mColliderNames.push_back(name);
	fixtureDef.userData = (void*)(&mColliderNames.back());

	mBody->CreateFixture(&fixtureDef);
}

