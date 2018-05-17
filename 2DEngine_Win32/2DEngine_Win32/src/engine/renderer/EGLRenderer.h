//
//  2DEngine
//  EGLRenderer.h
//  Eric Fleming
//  4/2/2018
//

#pragma once

#include <vector>

#include "../../../thirdpartysrc/glad/glad/glad.h"
#include <SDL.h>

#define lilGLRenderer EGLRenderer::Instance()

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

private:
	static EGLRenderer* s_Instance;

	ECamera* m_CurrentCamera;

private:
	EGLRenderer() {}
	~EGLRenderer() {}
	EGLRenderer(const EGLRenderer& renderer) {}
	void operator=(const EGLRenderer& renderer) {}
};

