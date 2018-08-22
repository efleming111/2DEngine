//
//  2DEngine
//  lilGLRenderer.h
//  Eric Fleming
//  4/2/2018
//

#pragma once

#include <list>

#include "../../../thirdpartysrc/glad/glad/glad.h"
#include <SDL.h>

#include "../components/lilCamera.h"
#include "../components/lilSprite.h"
#include "lilRenderable.h"
#include "lilMesh.h"
#include "lilTexture.h"
#include "lilShader.h"

#define lilGLRenderer laGLRenderer::Instance()

class laGLRenderer
{
public:
	// Returns only instance of renderer
	static laGLRenderer* Instance();

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

	void RegisterCamera(lilCamera* camera);

	// Adds sprite to manager
	// Returns index to sprite
	// @ sprite - sprite to be added
	lilRenderable* AddSprite(lilSprite* sprite);

	// Adds renderable object to renderer
	// @ element - data for the renderable
	void AddRenderable(TiXmlElement* element, float pixelsPerGameUnit);

	// Creates and adds mesh object
	// Returns pointer to mesh
	// @ vertexData - vertex data of object packed in an array of 3 position and 2 texture coordinates per vertex
	// @ vertexCount - number of vertices multiplied by 5
	// @ indices - index data
	// @ indicesCount - size of indices array
	lilMesh* AddMesh(float* vertexData, int vertexCount, unsigned short* indices, int indicesCount);

	// Adds texture
	// Returns created textures id, if texture exists, returns that texture id
	// @ filename - name of texture image to add
	unsigned AddTexture(const char* filename);

	// Adds shader
	// Returns a pointer to created shader, if shader exists, returns pointer to that shader
	// @ filename - name of shader file, both vert and frag shader must be named the same
	lilShader* AddShader(const char* filename);

	lilRenderable* GetRenderable(const char* renderableName);

	// Clears all current objects in the renderer
	void ClearRenderer();

private:
	static laGLRenderer* s_Instance;

	lilCamera* m_CurrentCamera;

	std::list<lilSprite*> m_Sprites;
	std::list<lilRenderable*> m_Renderables;

	std::list<lilMesh*> m_Meshes;
	std::list<lilTexture*> m_Textures;
	std::list<lilShader*> m_Shaders;

private:
	// Only one renderer, no copying
	laGLRenderer() {}
	~laGLRenderer() {}
	laGLRenderer(const laGLRenderer& renderer) {}
	void operator=(const laGLRenderer& renderer) {}

	// Sets the view and projection matrix for all shaders
	void SetViewAndProjectionMatrix();
};

