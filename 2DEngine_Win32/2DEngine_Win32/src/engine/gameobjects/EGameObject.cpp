//
//  2DEngine
//  EGameObject.cpp
//  Eric Fleming
//  5/18/2018
//

#include <sstream>
#include <iostream>

#include "EGameObject.h"
#include "../utilities/EFileIO.h"
#include "../components/ECameraComponent.h"
#include "../components/ELogicComponent.h"
#include "../components/EPhysicsComponent.h"
#include "../components/ESpriteComponent.h"

void EGameObject::Create(const char* filename, float pixelsPerGameUnit)
{
	m_PixelsPerGameUnit = pixelsPerGameUnit;

	char* xmlFile = lilFileIO::ReadFile(filename, "r");

	TiXmlDocument xmlDoc;
	xmlDoc.Parse(xmlFile);

	delete[] xmlFile;
	xmlFile = 0;

	TiXmlElement* rootElement = xmlDoc.RootElement();
	if (!rootElement)
		return;

	m_Name = rootElement->Attribute("name");

	int value;
	TiXmlElement* transform = rootElement->FirstChildElement("transform");
	transform->Attribute("x", &value);
	m_Transform.position.x = (float)value; 
	transform->Attribute("y", &value);
	m_Transform.position.y = (float)value;
	transform->Attribute("z", &value);
	m_Transform.position.z = (float)value;
	transform->Attribute("rotation", &value);
	m_Transform.rotation = (float)value;
	transform->Attribute("sx", &value);
	m_Transform.scale.x = (float)value;
	transform->Attribute("sy", &value);
	m_Transform.scale.y = (float)value;
	transform->Attribute("z", &value);
	m_Transform.scale.z = (float)value;

	CreateComponents(rootElement->FirstChildElement("components"));
}

void EGameObject::Update()
{
	for (unsigned i = 0; i < m_Components.size(); ++i)
		m_Components[i]->Update();
}

void EGameObject::Destroy()
{
	for (unsigned i = 0; i < m_Components.size(); ++i)
	{
		m_Components[i]->Destroy();
		delete m_Components[i];
	}

	m_Components.resize(0);
}

EComponent* EGameObject::GetComponent(unsigned index)
{
	if (index < m_Components.size())
		return m_Components[index];

	return 0;
}

EComponent* EGameObject::GetComponent(std::string name)
{
	for (unsigned i = 0; i < m_Components.size(); ++i)
		if (m_Components[i]->GetName().compare(name) == 0)
			return m_Components[i];

	return 0;
}

void EGameObject::CreateComponents(TiXmlElement* components)
{
	// TODO: Fill this out as components are created, consider sort to update in correct order
	for (TiXmlElement* component = components->FirstChildElement(); component; component = component->NextSiblingElement())
	{
		std::string type = component->Attribute("type");
		if (type.compare("camera"))
		{
			ECameraComponent* camera = new ECameraComponent(this);
			camera->Create(component);
			m_Components.push_back(camera);
		}

		else if (type.compare("logic"))
		{
			ELogicComponent* logic = new ELogicComponent(this);
			logic->Create(component);
			m_Components.push_back(logic);
		}

		else if (type.compare("sprite"))
		{
			ESpriteComponent* sprite = new ESpriteComponent(this);
			sprite->Create(component);
			m_Components.push_back(sprite);
		}

		else if (type.compare("physics"))
		{
			EPhysicsComponent* physics = new EPhysicsComponent(this);
			physics->Create(component);
			m_Components.push_back(physics);
		}

		else if (type.compare("animator"))
		{

		}
	}
}
