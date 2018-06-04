//
//  2DEngine
//  ESprite.h
//  Eric Fleming
//  5/20/2018
//

#pragma once

#include <string>

#include "EComponent.h"
#include "../gameobjects/ETransform.h"
#include "subcomponents/EMesh.h"
#include "subcomponents/EShader.h"

class ERenderable;

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

	void Draw();

public:
	ETransform transform;
	float xRelative;
	float yRelative;

	std::string renderableName;
	ERenderable* renderable;
	bool isRendered;

private:
	// No copying
	ESprite(const ESprite& component) {}
	void operator=(const ESprite& component) {}
};



