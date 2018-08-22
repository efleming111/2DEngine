//
//  2DEngine
//  ERenderable.h
//  Eric Fleming
//  6/11/2018
//

#pragma once

#include <vector>

#include "../../../thirdpartysrc/glad/glad/glad.h"
#include <SDL.h>

#include "../components/ESprite.h"

#define lilGLRenderer EGLRenderer::Instance()

class ERenderable
{
public:
	ERenderable() {}
	~ERenderable() {}

	// Creates a sprite
	// @ element - data for setting up the renderable
	void Create(TiXmlElement* element, float pixelsPerGameUnit);

	void Draw(ESprite* sprite);

	EShader* GetShader() { return m_Shader; }

public:
	std::string name;

	//private:
	float m_PixelsPerGameUnit;

	EMesh* m_Mesh;
	EShader* m_Shader;
	unsigned m_TextureID;

private:
	// No copying
	ERenderable(const ERenderable& renderable) {}
	void operator=(const ERenderable& renderable) {}
};

