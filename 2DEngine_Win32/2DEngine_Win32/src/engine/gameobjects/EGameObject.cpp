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
#include "../components/ECamera.h"
#include "../components/ELogic.h"
#include "../components/ERigidbody.h"
#include "../components/ESprite.h"
#include "../components/EAnimator.h"

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

	double value;
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
	transform->Attribute("sz", &value);
	m_Transform.scale.z = (float)value;

	CreateComponents(rootElement->FirstChildElement("components"));
}

void EGameObject::Create(TiXmlElement* rootElement, float pixelsPerGameUnit)
{
	m_PixelsPerGameUnit = pixelsPerGameUnit;

	m_Name = rootElement->Attribute("name");

	double value;
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
	transform->Attribute("sz", &value);
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

EComponent* EGameObject::GetComponent(const char* type)
{
	for (unsigned i = 0; i < m_Components.size(); ++i)
		if (m_Components[i]->GetType().compare(type) == 0)
			return m_Components[i];

	return 0;
}

void EGameObject::CreateComponents(TiXmlElement* components)
{
	for (TiXmlElement* component = components->FirstChildElement(); component; component = component->NextSiblingElement())
	{
		std::string type = component->Attribute("type");
		if (type.compare("camera") == 0)
		{
			ECamera* camera = new ECamera(this);
			camera->Create(component);
			m_Components.push_back(camera);
		}

		else if (type.compare("logic") == 0)
		{
			ELogic* logic = new ELogic(this);
			logic->Create(component);
			m_Components.push_back(logic);
		}

		else if (type.compare("sprite") == 0)
		{
			ESprite* sprite = new ESprite(this);
			sprite->Create(component);
			m_Components.push_back(sprite);
		}

		else if (type.compare("rigidbody") == 0)
		{
			ERigidbody* rigidbody = new ERigidbody(this);
			rigidbody->Create(component);
			m_Components.push_back(rigidbody);
		}

		else if (type.compare("animator") == 0)
		{
			EAnimator* animator = new EAnimator(this);
			animator->Create(component);
			m_Components.push_back(animator);
		}
	}
}
