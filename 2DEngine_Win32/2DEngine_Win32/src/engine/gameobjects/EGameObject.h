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

class EGameObject
{
public:
	EGameObject() {}
	 ~EGameObject() {}

	void Create(const char* filename);
	void Update();
	void Destroy();

	const std::string& GetName() { return m_Name; }

	EComponent* GetComponent(unsigned index);
	EComponent* GetComponent(std::string name);

public:
	ETransform m_Transform;

protected:
	std::string m_Name;
	std::vector<EComponent*> m_Components;

private:
	void CreateComponents(TiXmlElement* components);
};