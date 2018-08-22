//
//  2DEngine
//  lilGameObject.cpp
//  Eric Fleming
//  5/18/2018
//

#include <sstream>
#include <iostream>

#include "lilGameObject.h"
#include "../utilities/lilFileIO.h"
#include "../components/lilCamera.h"
#include "../components/lilRigidbody.h"
#include "../components/lilSprite.h"
#include "../components/lilAnimator.h"

void lilGameObject::Create(TiXmlElement* rootElement, float pixelsPerGameUnit)
{
	m_PixelsPerGameUnit = pixelsPerGameUnit;

	m_Type = rootElement->Attribute("type");
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

void lilGameObject::Update()
{
	for (std::list<lilComponent*>::iterator it = m_Components.begin(); it != m_Components.end(); ++it)
		(*it)->Update();
}

void lilGameObject::Destroy()
{
	for (std::list<lilComponent*>::iterator it = m_Components.begin(); it != m_Components.end(); ++it)
	{
		// Sprites get cleaned up by the renderer
		if ((*it)->GetType().compare("sprite") == 0)
			continue;

		(*it)->Destroy();
		delete (*it);
	}

	m_Components.clear();
}

lilComponent* lilGameObject::GetComponentByType(const char* type)
{
	for (std::list<lilComponent*>::iterator it = m_Components.begin(); it != m_Components.end(); ++it)
		if ((*it)->GetType().compare(type) == 0)
			return (*it);

	return 0;
}

lilComponent* lilGameObject::GetComponentByName(const char* name)
{
	for (std::list<lilComponent*>::iterator it = m_Components.begin(); it != m_Components.end(); ++it)
		if ((*it)->GetName().compare(name) == 0)
			return (*it);

	return 0;
}

void lilGameObject::CreateComponents(TiXmlElement* components)
{
	for (TiXmlElement* component = components->FirstChildElement(); component; component = component->NextSiblingElement())
	{
		std::string type = component->Attribute("type");
		if (type.compare("camera") == 0)
		{
			lilCamera* camera = new lilCamera(this);
			camera->Create(component);
			m_Components.push_back(camera);
		}

		else if (type.compare("sprite") == 0)
		{
			lilSprite* sprite = new lilSprite(this);
			sprite->Create(component);
			m_Components.push_back(sprite);
		}

		else if (type.compare("rigidbody") == 0)
		{
			lilRigidbody* rigidbody = new lilRigidbody(this);
			rigidbody->Create(component);
			m_Components.push_back(rigidbody);
		}

		else if (type.compare("animator") == 0)
		{
			lilAnimator* animator = new lilAnimator(this);
			animator->Create(component);
			m_Components.push_back(animator);
		}
	}
}
