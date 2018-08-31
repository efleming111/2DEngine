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
	lilComponent(lilGameObject* gameObject) { mGameObject = gameObject; }
	virtual ~lilComponent() {}

	virtual void Create(TiXmlElement* element) = 0;
	virtual void Update() = 0;
	virtual void Destroy() = 0;

	std::string& GetType() { return mType; }
	std::string& GetName() { return mName; }

protected:
	lilGameObject* mGameObject;
	std::string mType;
	std::string mName;

private:
	lilComponent(const lilComponent& component) {}
	void operator=(const lilComponent& component) {}
};

