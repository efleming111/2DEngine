//
//  2DEngine
//  ESprite.h
//  Eric Fleming
//  5/20/2018
//

#pragma once

#include "EComponent.h"
#include "../gameobjects/ETransform.h"
#include "subcomponents/EMesh.h"
#include "subcomponents/EShader.h"

class ESprite : public EComponent
{
public:
	ESprite(EGameObject* gameObject) { m_GameObject = gameObject; }
	~ESprite() {}

	// Creates a sprite
	// @ element - data for setting up the sprite
	void Create(TiXmlElement* element);

	// Updates the sprite
	void Update();

	// Does nothing
	void Destroy();

public:
	ETransform m_Transform;
	float m_XRel;
	float m_YRel;

	EMesh* mesh;
	EShader* shader;
	unsigned textureID;

	bool isRendered;

private:
	// No copying
	ESprite(const ESprite& component) {}
	void operator=(const ESprite& component) {}
};

