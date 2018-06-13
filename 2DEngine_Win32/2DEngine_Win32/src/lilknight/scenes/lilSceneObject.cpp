//
//  lil Knight
//  lilSceneObject.cpp
//  Eric Fleming
//  5/30/2018
//

#include "lilSceneObject.h"
#include "../../engine/input/EInput.h"
#include "../../engine/renderer/EGLRenderer.h"
#include "../../engine/components/ERigidbody.h"

#include <SDL.h>

void SceneObject::Create(TiXmlElement* rootElement, float pixelsPerGameUnit)
{
	EGameObject::Create(rootElement, pixelsPerGameUnit);

	double red, green, blue;
	rootElement->Attribute("clearcolorred", &red);
	rootElement->Attribute("clearcolorgreen", &green);
	rootElement->Attribute("clearcolorblue", &blue);
	lilGLRenderer->SetClearColor((float)red, (float)green, (float)blue, 1.0f);

	TiXmlElement* playerStart = rootElement->FirstChildElement("playerstart");
	m_PlayerStartX = 0.0f;
	m_PlayerStartY = 0.0f;
	if (playerStart)
	{
		double x, y;
		playerStart->Attribute("x", &x);
		playerStart->Attribute("y", &y);
		m_PlayerStartX = (float)x;
		m_PlayerStartY = (float)y;
	}

	m_ChangeScene = false;

	TiXmlElement* scenes = rootElement->FirstChildElement("scenes");
	for (TiXmlAttribute* loadOptions = scenes->FirstAttribute(); loadOptions; loadOptions = loadOptions->Next())
	{
		std::string index = loadOptions->Name();
		std::string filename = loadOptions->Value();
		m_LoadOptions[index] = filename;
	}
}

void SceneObject::OnStart()
{
	m_IsStarterScene = false;
	if (m_Name.compare("StarterScene") == 0)
		m_IsStarterScene = true;
}

void SceneObject::Update()
{
	EGameObject::Update();

	if (m_IsStarterScene)
	{
		m_ChangeScene = true;
		m_NextScene = m_LoadOptions["option1"];
	}
}

void SceneObject::Destroy()
{
	EGameObject::Destroy();
}

void SceneObject::BeginContact(ERigidbody* thisRigidbody, ERigidbody* otherRigidbody)
{
	if (thisRigidbody->colliderName->compare("option1") == 0 && otherRigidbody->colliderName->compare("playerbottomcollider") == 0)
	{
		m_ChangeScene = true;
		m_NextScene = m_LoadOptions[(*thisRigidbody->colliderName)];
	}

	else if (thisRigidbody->colliderName->compare("option2") == 0 && otherRigidbody->colliderName->compare("playerbottomcollider") == 0)
	{
		m_ChangeScene = true;
		m_NextScene = m_LoadOptions[(*thisRigidbody->colliderName)];
	}
}

void SceneObject::EndContact(ERigidbody * thisRigidbody, ERigidbody * otherRigidbody)
{
	if (thisRigidbody->colliderName->compare("playerkillzone") == 0 && otherRigidbody->colliderName->compare("playertopcollider") == 0)
	{
		m_ChangeScene = true;
		m_NextScene = m_Name;
		// TODO: save player data
	}
}

void SceneObject::GetPlayerStart(float* x, float* y)
{
	(*x) = m_PlayerStartX;
	(*y) = m_PlayerStartY;
}

