//
//  2DEngine
//  lilSprite.cpp
//  Eric Fleming
//  5/20/2018
//

#include <string>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "lilSprite.h"
#include "../renderer/lilGLRenderer.h"

void lilSprite::Create(TiXmlElement* element)
{
	mType = element->Attribute("type");
	mName = element->Attribute("name");
	renderableName = element->Attribute("renderablename");

	int renderOrder;
	element->Attribute("renderorder", &renderOrder);

	std::string rendered;
	rendered = element->Attribute("isrendered");
	if (rendered.compare("true") == 0)
		isRendered = true;
	else
		isRendered = false;

	double xScale, yScale, xRel, yRel;

	element->Attribute("width", &xScale);
	element->Attribute("height", &yScale);
	element->Attribute("xrel", &xRel);
	element->Attribute("yrel", &yRel);

	xRelative = (float)xRel;
	yRelative = (float)yRel;

	/*
	1 - Backgrounds
	2 - Background items
	3 - Tiles
	4 - Player
	5 - Hud level 1
	6 - Hud level 2
	*/
	transform.position.x = xRelative + mGameObject->mTransform.position.x;
	transform.position.y = yRelative + mGameObject->mTransform.position.y;
	transform.position.z = (.01f * (float)renderOrder) / mGameObject->mPixelsPerGameUnit;
	transform.rotation = 0.0f;
	transform.scale = glm::vec3((float)xScale, (float)yScale, 1.0f);

	renderable = lilGLRenderer->AddSprite(this);
}

void lilSprite::Update()
{
	transform.position.x = mGameObject->mTransform.position.x + xRelative;
	transform.position.y = mGameObject->mTransform.position.y + yRelative;
}

void lilSprite::Destroy()
{
	// Empty
}

void lilSprite::Draw()
{
	renderable->Draw(this);
}


