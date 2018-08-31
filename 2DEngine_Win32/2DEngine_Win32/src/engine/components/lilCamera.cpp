//
//  2DEngine
//  lilCamera.cpp
//  Eric Fleming
//  5/18/2018
//

#include "lilCamera.h"
#include "../renderer/lilGLWindow.h"
#include "../renderer/lilGLRenderer.h"

void lilCamera::Create(TiXmlElement* element)
{
	mType = element->Attribute("type");

	Update();

	lilGLRenderer->RegisterCamera(this);
}

void lilCamera::Update()
{
	float wWidth = (float)lilGLWindow->Width();
	float wHeight = (float)lilGLWindow->Height();

	mView = glm::lookAt(mGameObject->mTransform.position * mGameObject->mPixelsPerGameUnit, mGameObject->mTransform.position * mGameObject->mPixelsPerGameUnit + glm::vec3(0.0f, 0.0, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	//mProjection = glm::ortho(wWidth * -.5f, wWidth * .5f, wHeight * -.5f, wHeight * .5f, 2.0f * mGameObject->mPixelsPerGameUnit, -2.0f * mGameObject->mPixelsPerGameUnit);
	mProjection = glm::ortho(wWidth * -.5f, wWidth * .5f, wHeight * -.5f, wHeight * .5f, .1f, 2.0f * mGameObject->mPixelsPerGameUnit);
}

void lilCamera::Destroy()
{
	// Empty
}

void lilCamera::SetPosition(float x, float y)
{
	mGameObject->mTransform.position.x = x;
	mGameObject->mTransform.position.y = y;
}

void lilCamera::Move(float xAmount, float yAmount)
{
	mGameObject->mTransform.position.x += xAmount;
	mGameObject->mTransform.position.y += yAmount;
}
