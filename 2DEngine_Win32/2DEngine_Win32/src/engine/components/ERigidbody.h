//
//  2DEngine
//  ERigidbody.h
//  Eric Fleming
//  5/18/2018
//

#pragma once

#include <list>
#include <string>

#include <Box2D\Box2D.h>

#include "EComponent.h"

#define EVector2D b2Vec2
#define EMax b2Max
#define EMin b2Min

class ERigidbody : public EComponent
{
public:
	ERigidbody(EGameObject* gameObject) { m_GameObject = gameObject; }
	~ERigidbody() {}

	void Create(TiXmlElement* element);
	void Update();
	void Destroy();

	void BeginContact(ERigidbody* thisRigidbody, ERigidbody* otherRigidbody);
	void EndContact(ERigidbody* thisRigidbody, ERigidbody* otherRigidbody);

	EGameObject* GetGameObject() { return m_GameObject; }

	EVector2D GetVelocity() { return m_Body->GetLinearVelocity(); }
	EVector2D GetPosition() { return m_Body->GetPosition(); }

	void SetVelocity(EVector2D vector) { m_Body->SetLinearVelocity(vector); }

	std::string* colliderName;

protected:
	void(*BeginContactLogic)(ERigidbody* thisRigidbody, ERigidbody* otherRigidbody);
	void(*EndContactLogic)(ERigidbody* thisRigidbody, ERigidbody* otherRigidbody);

	b2Body* m_Body;

	std::list<std::string> m_ColliderNames;

private:
	ERigidbody(const ERigidbody& component) {}
	void operator=(const ERigidbody& component) {}

	void AddBoxCollider(TiXmlElement* element);
	void AddCircleCollider(TiXmlElement* element);
};

