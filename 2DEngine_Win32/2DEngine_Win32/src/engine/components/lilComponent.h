//
//  2DEngine
//  lilComponent.h
//  Eric Fleming
//  5/18/2018
//

#pragma once

#include <string>

#include "../gameobjects/lilGameObject.h"
#include "../../../thirdpartysrc/tinyxml/tinyxml.h"

class lilGameObject;

// Abstract class to derive all components from
class lilComponent
{
public:
	lilComponent() {}
	lilComponent(lilGameObject* gameObject) { m_GameObject = gameObject; }
	virtual ~lilComponent() {}

	virtual void Create(TiXmlElement* element) = 0;
	virtual void Update() = 0;
	virtual void Destroy() = 0;

	std::string& GetType() { return m_Type; }
	std::string& GetName() { return m_Name; }

protected:
	lilGameObject* m_GameObject;
	std::string m_Type;
	std::string m_Name;

private:
	lilComponent(const lilComponent& component) {}
	void operator=(const lilComponent& component) {}
};

