//
//  2DEngine
//  ESprite.cpp
//  Eric Fleming
//  5/20/2018
//

#include <string>

#include "ESprite.h"
#include "subcomponents\EMeshManager.h"
#include "subcomponents\ETextureManager.h"
#include "subcomponents\EShaderManager.h"
#include "../renderer/EGLRenderer.h"

void ESprite::Create(TiXmlElement* element)
{
	m_Type = element->Attribute("type");

	std::string rendered;
	rendered = element->Attribute("isrendered");
	if (rendered.compare("true") == 0)
		isRendered = true;
	else
		isRendered = false;

	double width, height, xRel, yRel, texLeft, texRight, texTop, texBottom;

	element->Attribute("width", &width);
	element->Attribute("height", &height);
	element->Attribute("xrel", &xRel);
	element->Attribute("yrel", &yRel);
	element->Attribute("texleft", &texLeft);
	element->Attribute("texright", &texRight);
	element->Attribute("textop", &texTop);
	element->Attribute("texbottom", &texBottom);

	m_XRel = (float)xRel;
	m_YRel = (float)yRel;

	m_Transform.position.x = (m_GameObject->m_Transform.position.x + m_XRel) * m_GameObject->m_PixelsPerGameUnit;
	m_Transform.position.y = (m_GameObject->m_Transform.position.y + m_YRel) * m_GameObject->m_PixelsPerGameUnit;
	m_Transform.position.z = 0.0f;
	m_Transform.rotation = 0.0f;
	m_Transform.scale = glm::vec3(1.0f, 1.0f, 1.0f);

	float halfWidth = (float)width * m_GameObject->m_PixelsPerGameUnit * .5f;
	float halfHeight = (float)height * m_GameObject->m_PixelsPerGameUnit * .5f;

	float vertexData[20] = {
		-halfWidth, -halfHeight, 0.0f,		(float)texLeft, (float)texTop,
		halfWidth, -halfHeight, 0.0f,		(float)texRight, (float)texTop,
		halfWidth, halfHeight, 0.0f,		(float)texRight, (float)texBottom,
		-halfWidth, halfHeight, 0.0f,		(float)texLeft, (float)texBottom
	};

	unsigned short indices[6] = { 0, 1, 3, 3, 1, 2 };

	mesh = lilMeshManager->AddMesh(vertexData, 20, indices, 6);

	std::string textureFile = element->Attribute("texturefile");
	textureID = lilTextureManager->AddTexture(textureFile.c_str());

	std::string shaderFile = element->Attribute("shaderfile");
	shader = lilShaderManager->AddShader(shaderFile.c_str());

	lilGLRenderer->AddSprite(this);
}

void ESprite::Update()
{
	m_Transform.position.x = (m_GameObject->m_Transform.position.x + m_XRel) * m_GameObject->m_PixelsPerGameUnit;
	m_Transform.position.y = (m_GameObject->m_Transform.position.y + m_YRel) * m_GameObject->m_PixelsPerGameUnit;
}

void ESprite::Destroy()
{
	// Empty
}
