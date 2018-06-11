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
#ifdef _WIN32
	if (lilKeyboard->GetKeyDown(KC_Y))
		m_ChangeScene = true;
#endif // _WIN32

#ifdef __ANDROID__
	Finger* fingers = lilTouch->GetTouches();
	for(int i = 0; i < MAX_FINGER_TOUCHES && fingers[i].isTouching; ++i)
		if (fingers[i].xNormalized < .25f && fingers[i].yNormalized < .25f)
		{
			SDL_Log("Touch Logged At Change Scene, %s %d", __FILE__, __LINE__);
			m_ChangeScene = true;
			break;
		}
#endif // __ANDROID__

}

void SceneObject::Destroy()
{
	EGameObject::Destroy();
}

