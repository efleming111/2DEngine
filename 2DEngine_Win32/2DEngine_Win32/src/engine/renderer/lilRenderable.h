//
//  2DEngine
//  lilRenderable.h
//  Eric Fleming
//  6/11/2018
//

#pragma once

#include <vector>

#include "../../../thirdpartysrc/glad/glad/glad.h"
#include <SDL.h>

#include "../components/lilSprite.h"
#include "lilMesh.h"
#include "lilShader.h"

class lilRenderable
{
public:
	lilRenderable() {}
	~lilRenderable() {}

	// Creates a sprite
	// @ element - data for setting up the renderable
	void Create(TiXmlElement* element, float pixelsPerGameUnit);

	void Draw(lilSprite* sprite);

	lilShader* GetShader() { return mShader; }

public:
	std::string name;

	//private:
	float mPixelsPerGameUnit;

	lilMesh* mMesh;
	lilShader* mShader;
	unsigned mTextureID;

private:
	// No copying
	lilRenderable(const lilRenderable& renderable) {}
	void operator=(const lilRenderable& renderable) {}
};

