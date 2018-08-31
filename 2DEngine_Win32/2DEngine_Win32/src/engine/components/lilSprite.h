//
//  2DEngine
//  lilSprite.h
//  Eric Fleming
//  5/20/2018
//

#pragma once

#include <string>

#include "lilComponent.h"
#include "../gameobjects/lilTransform.h"
#include "../renderer/lilMesh.h"
#include "../renderer/lilShader.h"

class lilRenderable;

class lilSprite : public lilComponent
{
public:
	lilSprite(lilGameObject* gameObject) { mGameObject = gameObject; }
	~lilSprite() {}

	// Creates a sprite
	// @ element - data for setting up the sprite
	void Create(TiXmlElement* element);

	// Updates the sprite
	void Update();

	// Does nothing
	void Destroy();

	void Draw();

public:
	lilTransform transform;
	float xRelative;
	float yRelative;

	std::string renderableName;
	lilRenderable* renderable;
	bool isRendered;

private:
	// No copying
	lilSprite(const lilSprite& component) {}
	void operator=(const lilSprite& component) {}
};



