//
//  lil Knight
//  lilLevelLogic.h
//  Eric Fleming
//  5/21/2018
//

#include "lilButtonControls.h"

#include "../../engine/renderer/EGLWindow.h"
#include "../../engine/gameobjects/EGameObjectManager.h"

void ButtonControls::Create(TiXmlElement* rootElement, float pixelsPerGameUnit)
{
	EGameObject::Create(rootElement, pixelsPerGameUnit);

	TiXmlElement* buttonPositions = rootElement->FirstChildElement("buttonpositions");
	for (TiXmlElement* position = buttonPositions->FirstChildElement(); position; position = position->NextSiblingElement())
	{
		Button* button = new Button();
		button->name = position->Attribute("name");

		double x, y;
		position->Attribute("x", &x);
		position->Attribute("y", &y);

		button->x = (((float)x * (float)lilGLWindow->Width()) - ((float)lilGLWindow->Width() * .5f)) / m_PixelsPerGameUnit;
		button->y = (((float)y * (float)lilGLWindow->Height()) - ((float)lilGLWindow->Height() * .5f)) / m_PixelsPerGameUnit;

		m_Buttons.push_back(button);
	}
}

void ButtonControls::OnStart()
{
	m_Camera = (Camera*)lilGameObjectManager->GetGameObject("Camera");
	m_Transform = m_Camera->m_Transform;

	for (std::list<Button*>::iterator it = m_Buttons.begin(); it != m_Buttons.end(); ++it)
	{
		ESprite* buttonSprite = (ESprite*)GetComponentByName((*it)->name.c_str());
		buttonSprite->xRelative = (*it)->x;
		buttonSprite->yRelative = (*it)->y;
	}
}

void ButtonControls::Update()
{
	m_Transform = m_Camera->m_Transform;

	EGameObject::Update();
}

void ButtonControls::Destroy()
{
	EGameObject::Destroy();
}

