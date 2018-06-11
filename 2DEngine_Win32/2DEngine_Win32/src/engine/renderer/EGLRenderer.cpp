//
//  2DEngine
//  EGLRenderer.cpp
//  Eric Fleming
//  4/2/2018
//

#include <string>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "EGLRenderer.h"
#include "EGLWindow.h"

EGLRenderer* EGLRenderer::s_Instance = 0;

EGLRenderer* EGLRenderer::Instance()
{
	if (!s_Instance)
		s_Instance = new EGLRenderer();

	return s_Instance;
}

bool EGLRenderer::Initialize()
{
	// Initialize GLAD
	if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
	{
		SDL_Log("ERROR: Failed To Initialize GLAD Library, %s %d", __FILE__, __LINE__);
		return false;
	}

	ResizeViewport(lilGLWindow->Width(), lilGLWindow->Height());

	glEnable(GL_DEPTH_TEST);

	SetClearColor(0.8f, 0.2f, 0.2f, 1.0f);

	return true;
}

void EGLRenderer::ResizeViewport(int width, int height)
{
	glViewport(0, 0, width, height);
}

void EGLRenderer::SetClearColor(float red, float green, float blue, float alpha)
{
	glClearColor(red, green, blue, alpha);
}

void EGLRenderer::DrawFrame()
{
	SetViewAndProjectionMatrix();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (std::list<ESprite*>::iterator it = m_Sprites.begin(); it != m_Sprites.end(); ++it)
		(*it)->Draw();

	lilGLWindow->SwapBuffers();
}

void EGLRenderer::RegisterCamera(ECamera* camera)
{
	m_CurrentCamera = camera;
}

ERenderable* EGLRenderer::AddSprite(ESprite* sprite)
{
	ERenderable* renderable = 0;
	for (std::list<ERenderable*>::iterator it = m_Renderables.begin(); it != m_Renderables.end(); ++it)
		if (sprite->renderableName.compare((*it)->name) == 0)
			renderable = (*it);
	
	m_Sprites.push_back(sprite);

	return renderable;
}

void EGLRenderer::AddRenderable(TiXmlElement* element, float pixelsPerGameUnit)
{
	ERenderable* renderable = new ERenderable();
	renderable->Create(element, pixelsPerGameUnit);
	m_Renderables.push_back(renderable);
}

EMesh* EGLRenderer::AddMesh(float * vertexData, int vertexCount, unsigned short * indices, int indicesCount)
{
	EMesh* mesh;
	mesh = new EMesh();
	mesh->Create(vertexData, vertexCount, indices, indicesCount);

	m_Meshes.push_back(mesh);

	return mesh;
}

unsigned EGLRenderer::AddTexture(const char * filename)
{
	for (std::list<ETexture*>::iterator it = m_Textures.begin(); it != m_Textures.end(); ++it)
		if ((*it)->GetName().compare(filename) == 0)
			return (*it)->GetID();

	ETexture* tempTexture = new ETexture();
	tempTexture->Create(filename);
	m_Textures.push_back(tempTexture);

	return tempTexture->GetID();
}

EShader* EGLRenderer::AddShader(const char * filename)
{
	for (std::list<EShader*>::iterator it = m_Shaders.begin(); it != m_Shaders.end(); ++it)
		if ((*it)->GetName().compare(filename) == 0)
			return (*it);

	EShader* tempShader = new EShader();
	tempShader->Create(filename);
	m_Shaders.push_back(tempShader);

	return tempShader;
}

ERenderable* EGLRenderer::GetRenderable(const char* renderableName)
{
	for (std::list<ERenderable*>::iterator it = m_Renderables.begin(); it != m_Renderables.end(); ++it)
		if ((*it)->name.compare(renderableName) == 0)
			return (*it);

	return 0;
}

void EGLRenderer::ClearRenderer()
{
	for (std::list<ESprite*>::iterator it = m_Sprites.begin(); it != m_Sprites.end(); ++it)
	{
		(*it)->Destroy();
		delete (*it);
	}

	for (std::list<ERenderable*>::iterator it = m_Renderables.begin(); it != m_Renderables.end(); ++it)
		delete (*it);

	for (std::list<EMesh*>::iterator it = m_Meshes.begin(); it != m_Meshes.end(); ++it)
	{
		(*it)->Destroy();
		delete (*it);
	}

	for (std::list<ETexture*>::iterator it = m_Textures.begin(); it != m_Textures.end(); ++it)
	{
		(*it)->Destroy();
		delete (*it);
	}

	for (std::list<EShader*>::iterator it = m_Shaders.begin(); it != m_Shaders.end(); ++it)
	{
		(*it)->Destroy();
		delete (*it);
	}

	m_Sprites.clear();
	m_Renderables.clear();
	m_Meshes.clear();
	m_Textures.clear();
	m_Shaders.clear();
}

void EGLRenderer::SetViewAndProjectionMatrix()
{
	for (std::list<EShader*>::iterator it = m_Shaders.begin(); it != m_Shaders.end(); ++it)
	{
		(*it)->SetUniform("camera", glm::value_ptr(m_CurrentCamera->GetViewMatrix()));
		(*it)->SetUniform("projection", glm::value_ptr(m_CurrentCamera->GetProjectionMatrix()));
	}
}

