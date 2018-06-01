//
//  lil Knight
//  lilHUD.cpp
//  Eric Fleming
//  6/1/2018
//

#include "lilHUD.h"

void HUD::Create(TiXmlElement* rootElement, float pixelsPerGameUnit)
{
	EGameObject::Create(rootElement, pixelsPerGameUnit);

	/*TiXmlElement* components = rootElement->FirstChildElement("components");
	for (TiXmlElement* component = components->FirstChildElement(); component; component = component->NextSiblingElement())
	{
		std::string type = component->Attribute("type");
		if (type.compare("renderable") == 0)
		{
			ECamera* camera = new ECamera(this);
			camera->Create(component);
			m_Components.push_back(camera);
		}
	}*/
	
}

void HUD::OnStart()
{
	m_Player = (Player*)lilGameObjectManager->GetGameObject("Player");
	m_Camera = (Camera*)lilGameObjectManager->GetGameObject("Camera");

	m_Transform = m_Camera->m_Transform;

}

void HUD::Update()
{
	m_Transform = m_Camera->m_Transform;

	EGameObject::Update();
}

void HUD::Destroy()
{
	EGameObject::Destroy();
}