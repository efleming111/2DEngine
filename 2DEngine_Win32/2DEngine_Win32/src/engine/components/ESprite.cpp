//
//  2DEngine
//  ESprite.cpp
//  Eric Fleming
//  5/20/2018
//

#include <string>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "ESprite.h"
#include "../renderer/EGLRenderer.h"

void ESprite::Create(TiXmlElement* element)
{
	m_Type = element->Attribute("type");
	m_Name = element->Attribute("name");
	renderableName = element->Attribute("renderablename");

	/*
	1 - Backgrounds
	2 - Background items
	3 - Tiles
	4 - Player
	5 - Hud level 1
	6 - Hud level 2
	*/
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

	transform.position.x = xRelative + m_GameObject->m_Transform.position.x;
	transform.position.y = yRelative + m_GameObject->m_Transform.position.y;
	transform.position.z = (.01f * (float)renderOrder) / -m_GameObject->m_PixelsPerGameUnit;
	transform.rotation = 0.0f;
	transform.scale = glm::vec3((float)xScale, (float)yScale, 1.0f);

	renderable = lilGLRenderer->AddSprite(this);
}

void ESprite::Update()
{
	transform.position.x = m_GameObject->m_Transform.position.x + xRelative;
	transform.position.y = m_GameObject->m_Transform.position.y + yRelative;
}

void ESprite::Destroy()
{
	// Empty
}

void ESprite::Draw()
{
	renderable->Draw(this);
}


