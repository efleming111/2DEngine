//
//  lil Knight
//  lilSceneObject.cpp
//  Eric Fleming
//  5/30/2018
//

#include "lilSceneObject.h"
#include "../../engine/input/EInput.h"

#include <SDL.h>

void SceneObject::Create(TiXmlElement* rootElement, float pixelsPerGameUnit)
{
	EGameObject::Create(rootElement, pixelsPerGameUnit);

	m_ChangeScene = false;

	TiXmlElement* scenes = rootElement->FirstChildElement("scenes");
	m_NextScene = scenes->Attribute("option1");

	SDL_Log("Scene Object, %s %d", __FILE__, __LINE__);
}

void SceneObject::OnStart()
{
	SDL_Log("Scene Object, %s %d", __FILE__, __LINE__);
}

void SceneObject::Update()
{
	EGameObject::Update();
	// TODO: Scene should change this not key press
	if (lilKeyboard->GetKeyDown(KC_Y))
		m_ChangeScene = true;
}

void SceneObject::Destroy()
{
	EGameObject::Destroy();
}

