//
//  2DEngine
//  EGameObject.h
//  Eric Fleming
//  5/18/2018
//

#pragma once

#include <string>
#include <vector>

#include "ETransform.h"
#include "../components/EComponent.h"
#include "../../../thirdpartysrc/tinyxml/tinyxml.h"

class EComponent;
class ERigidbody;

class EGameObject
{
public:
	EGameObject() {}
	 virtual ~EGameObject() {}

	virtual void Create(const char* filename, float pixelsPerGameUnit) = 0;
	virtual void Create(TiXmlElement* rootElement, float pixelsPerGameUnit) = 0;
	virtual void OnStart() = 0;
	virtual void Update() = 0;
	virtual void Destroy() = 0;

	virtual void BeginContact(ERigidbody* thisRigidbody, ERigidbody* otherRigidbody) {}
	virtual void EndContact(ERigidbody* thisRigidbody, ERigidbody* otherRigidbody) {}

	EComponent* GetComponent(const char* type);

public:
	std::string m_Name;
	ETransform m_Transform;
	float m_PixelsPerGameUnit;

protected:
	std::vector<EComponent*> m_Components;

private:
	void CreateComponents(TiXmlElement* components);
};