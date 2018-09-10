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
	mPixelsPerGameUnit = pixelsPerGameUnit;

	mType = rootElement->Attribute("type");
	mName = rootElement->Attribute("name");

	double value;
	TiXmlElement* transform = rootElement->FirstChildElement("transform");
	transform->Attribute("x", &value);
	mTransform.position.x = (float)value;
	transform->Attribute("y", &value);
	mTransform.position.y = (float)value;
	transform->Attribute("z", &value);
	mTransform.position.z = (float)value;
	transform->Attribute("rotation", &value);
	mTransform.rotation = (float)value;
	transform->Attribute("sx", &value);
	mTransform.scale.x = (float)value;
	transform->Attribute("sy", &value);
	mTransform.scale.y = (float)value;
	transform->Attribute("sz", &value);
	mTransform.scale.z = (float)value;

	CreateComponents(rootElement->FirstChildElement("components"));
}

void lilGameObject::Update()
{
	for (std::list<lilComponent*>::iterator it = mComponents.begin(); it != mComponents.end(); ++it)
		(*it)->Update();
}

void lilGameObject::Destroy()
{
	for (std::list<lilComponent*>::iterator it = mComponents.begin(); it != mComponents.end(); ++it)
	{
		// Sprites get cleaned up by the renderer
		if ((*it)->GetType().compare("Sprite") == 0)
			continue;

		(*it)->Destroy();
		delete (*it);
	}

	mComponents.clear();
}

lilComponent* lilGameObject::GetComponentByType(const char* type)
{
	for (std::list<lilComponent*>::iterator it = mComponents.begin(); it != mComponents.end(); ++it)
		if ((*it)->GetType().compare(type) == 0)
			return (*it);

	return 0;
}

lilComponent* lilGameObject::GetComponentByName(const char* name)
{
	for (std::list<lilComponent*>::iterator it = mComponents.begin(); it != mComponents.end(); ++it)
		if ((*it)->GetName().compare(name) == 0)
			return (*it);

	return 0;
}

void lilGameObject::CreateComponents(TiXmlElement* components)
{
	for (TiXmlElement* component = components->FirstChildElement(); component; component = component->NextSiblingElement())
	{
		std::string type = component->Attribute("type");

		if (type.compare("Camera") == 0)
		{
			lilCamera* camera = new lilCamera(this);
			camera->Create(component);
			mComponents.push_back(camera);
		}

		else if (type.compare("Sprite") == 0)
		{
			lilSprite* sprite = new lilSprite(this);
			sprite->Create(component);
			mComponents.push_back(sprite);
		}

		else if (type.compare("Rigidbody") == 0)
		{
			lilRigidbody* rigidbody = new lilRigidbody(this);
			rigidbody->Create(component);
			mComponents.push_back(rigidbody);
		}

		else if (type.compare("Animator") == 0)
		{
			lilAnimator* animator = new lilAnimator(this);
			animator->Create(component);
			mComponents.push_back(animator);
		}
	}
}


