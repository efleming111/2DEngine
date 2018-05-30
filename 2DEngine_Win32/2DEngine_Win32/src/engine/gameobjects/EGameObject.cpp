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
	for (std::list<EComponent*>::iterator it = m_Components.begin(); it != m_Components.end(); ++it)
		(*it)->Update();
}

void EGameObject::Destroy()
{
	for (std::list<EComponent*>::iterator it = m_Components.begin(); it != m_Components.end(); ++it)
	{
		// Sprites get cleaned up by the renderer
		if ((*it)->GetType().compare("sprite") == 0)
			continue;

		(*it)->Destroy();
		delete (*it);
	}

	m_Components.clear();
}

EComponent* EGameObject::GetComponent(const char* type)
{
	for (std::list<EComponent*>::iterator it = m_Components.begin(); it != m_Components.end(); ++it)
		if ((*it)->GetType().compare(type) == 0)
			return (*it);

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
