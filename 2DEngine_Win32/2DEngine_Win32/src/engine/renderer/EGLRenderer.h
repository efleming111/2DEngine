//
//  2DEngine
//  EGLRenderer.h
//  Eric Fleming
//  4/2/2018
//

#pragma once

#include <list>

#include "../../../thirdpartysrc/glad/glad/glad.h"
#include <SDL.h>

#include "../components/ECamera.h"
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

class EGLRenderer
{
public:
	// Returns only instance of renderer
	static EGLRenderer* Instance();

	// Creates renderer
	// Returns true on success
	bool Initialize();

	// Resizes the rendering viewport
	void ResizeViewport(int width, int height);

	// Sets the screen clearing color
	// @ red - amount of red 0 - 1
	// @ green - amount of green 0 - 1
	// @ blue - amount of blue 0 - 1
	// @ alpha - amount of alpha 0 - 1
	void SetClearColor(float red, float green, float blue, float alpha);

	// Draws the current frame
	void DrawFrame();

	void RegisterCamera(ECamera* camera);

	// Adds sprite to manager
	// Returns renderable that sprite uses
	// @ sprite - sprite to be added
	ERenderable* AddSprite(ESprite* sprite);

	// Adds renderable object to renderer
	// @ element - data for the renderable
	void AddRenderable(TiXmlElement* element, float pixelsPerGameUnit);

	ERenderable* GetRenderable(const char* renderableName);

	// Frees all loaded sprites
	void FreeRenderer();

private:
	static EGLRenderer* s_Instance;

	ECamera* m_CurrentCamera;

	std::list<ESprite*> m_Sprites;
	std::list<ERenderable*> m_Renderables;

private:
	// Only one renderer, no copying
	EGLRenderer() {}
	~EGLRenderer() {}
	EGLRenderer(const EGLRenderer& renderer) {}
	void operator=(const EGLRenderer& renderer) {}
};

