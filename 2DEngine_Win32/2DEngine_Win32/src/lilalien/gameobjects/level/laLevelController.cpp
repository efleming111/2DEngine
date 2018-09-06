//
//  lil Alien
//  laLevelController.cpp
//  Eric Fleming
//  5/30/2018
//

#include "laLevelController.h"
#include "../../../engine/input/lilInput.h"
#include "../../../engine/renderer/lilGLRenderer.h"
#include "../../../engine/components/lilRigidbody.h"

#include <SDL.h>

void laLevelController::Create(TiXmlElement* rootElement, float pixelsPerGameUnit)
{
	lilGameObject::Create(rootElement, pixelsPerGameUnit);

	double red, green, blue;
	rootElement->Attribute("clearcolorred", &red);
	rootElement->Attribute("clearcolorgreen", &green);
	rootElement->Attribute("clearcolorblue", &blue);
	lilGLRenderer->SetClearColor((float)red, (float)green, (float)blue, 1.0f);

	TiXmlElement* playerStart = rootElement->FirstChildElement("playerstart");
	mPlayerStartX = 0.0f;
	mPlayerStartY = 0.0f;
	if (playerStart)
	{
		double x, y;
		playerStart->Attribute("x", &x);
		playerStart->Attribute("y", &y);
		mPlayerStartX = (float)x;
		mPlayerStartY = (float)y;
	}

	mChangeScene = false;

	TiXmlElement* levels = rootElement->FirstChildElement("levels");
	for (TiXmlAttribute* loadOptions = levels->FirstAttribute(); loadOptions; loadOptions = loadOptions->Next())
	{
		std::string index = loadOptions->Name();
		std::string filename = loadOptions->Value();
		mLoadOptions[index] = filename;
	}
}

void laLevelController::OnStart()
{
	mIsDefaultLevel = false;
	if (mName.compare("DefaultLevel") == 0)
		mIsDefaultLevel = true;
}

void laLevelController::Update()
{
	lilGameObject::Update();

	if (mIsDefaultLevel)
	{
		mChangeScene = true;
		mNextScene = mLoadOptions["option1"];
	}
}

void laLevelController::Destroy()
{
	lilGameObject::Destroy();
}

void laLevelController::BeginContact(lilRigidbody* thisRigidbody, lilRigidbody* otherRigidbody)
{
	if (thisRigidbody->colliderName->compare("option1") == 0 && otherRigidbody->colliderName->compare("PlayerBottomCollider") == 0)
	{
		mChangeScene = true;
		mNextScene = mLoadOptions[(*thisRigidbody->colliderName)];
	}

	else if (thisRigidbody->colliderName->compare("option2") == 0 && otherRigidbody->colliderName->compare("PlayerBottomCollider") == 0)
	{
		mChangeScene = true;
		mNextScene = mLoadOptions[(*thisRigidbody->colliderName)];
	}
}

void laLevelController::EndContact(lilRigidbody* thisRigidbody, lilRigidbody* otherRigidbody)
{
	if (thisRigidbody->colliderName->compare("KillZone") == 0 && otherRigidbody->colliderName->compare("PlayerTopCollider") == 0)
	{
		mChangeScene = true;
		mNextScene = mName;
		// TODO: save player data
	}
}

void laLevelController::GetPlayerStart(float* x, float* y)
{
	(*x) = mPlayerStartX;
	(*y) = mPlayerStartY;
}

