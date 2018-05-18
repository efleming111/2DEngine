//
//  2DEngine
//  EComponent.h
//  Eric Fleming
//  5/18/2018
//

#pragma once

#include <string>
#include <vector>

#include "../gameobjects/EGameObject.h"
#include "../../../thirdpartysrc/tinyxml/tinyxml.h"

class EGameObject;

class EComponent
{
public:
	EComponent() {}
	EComponent(EGameObject* gameObject) { m_GameObject = gameObject; }
	virtual ~EComponent() {}

	virtual void Create(TiXmlElement* element) = 0;
	virtual void Update() = 0;
	virtual void Destroy() = 0;

	std::string& GetName() { return m_Name; }

protected:
	EGameObject* m_GameObject;
	std::string m_Name;

private:
	EComponent(const EComponent& component) {}
	void operator=(const EComponent& component) {}
};

