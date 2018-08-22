//
//  2DEngine
//  lilGLRenderer.cpp
//  Eric Fleming
//  4/2/2018
//

#include <string>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "lilGLRenderer.h"
#include "lilGLWindow.h"

laGLRenderer* laGLRenderer::s_Instance = 0;

laGLRenderer* laGLRenderer::Instance()
{
	if (!s_Instance)
		s_Instance = new laGLRenderer();

	return s_Instance;
}

bool laGLRenderer::Initialize()
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

void laGLRenderer::ResizeViewport(int width, int height)
{
	glViewport(0, 0, width, height);
}

void laGLRenderer::SetClearColor(float red, float green, float blue, float alpha)
{
	glClearColor(red, green, blue, alpha);
}

void laGLRenderer::DrawFrame()
{
	SetViewAndProjectionMatrix();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (std::list<lilSprite*>::iterator it = m_Sprites.begin(); it != m_Sprites.end(); ++it)
		(*it)->Draw();

	lilGLWindow->SwapBuffers();
}

void laGLRenderer::RegisterCamera(lilCamera* camera)
{
	m_CurrentCamera = camera;
}

lilRenderable* laGLRenderer::AddSprite(lilSprite* sprite)
{
	lilRenderable* renderable = 0;
	for (std::list<lilRenderable*>::iterator it = m_Renderables.begin(); it != m_Renderables.end(); ++it)
		if (sprite->renderableName.compare((*it)->name) == 0)
			renderable = (*it);
	
	m_Sprites.push_back(sprite);

	return renderable;
}

void laGLRenderer::AddRenderable(TiXmlElement* element, float pixelsPerGameUnit)
{
	lilRenderable* renderable = new lilRenderable();
	renderable->Create(element, pixelsPerGameUnit);
	m_Renderables.push_back(renderable);
}

lilMesh* laGLRenderer::AddMesh(float * vertexData, int vertexCount, unsigned short * indices, int indicesCount)
{
	lilMesh* mesh;
	mesh = new lilMesh();
	mesh->Create(vertexData, vertexCount, indices, indicesCount);

	m_Meshes.push_back(mesh);

	return mesh;
}

unsigned laGLRenderer::AddTexture(const char * filename)
{
	for (std::list<lilTexture*>::iterator it = m_Textures.begin(); it != m_Textures.end(); ++it)
		if ((*it)->GetName().compare(filename) == 0)
			return (*it)->GetID();

	lilTexture* tempTexture = new lilTexture();
	tempTexture->Create(filename);
	m_Textures.push_back(tempTexture);

	return tempTexture->GetID();
}

lilShader* laGLRenderer::AddShader(const char * filename)
{
	for (std::list<lilShader*>::iterator it = m_Shaders.begin(); it != m_Shaders.end(); ++it)
		if ((*it)->GetName().compare(filename) == 0)
			return (*it);

	lilShader* tempShader = new lilShader();
	tempShader->Create(filename);
	m_Shaders.push_back(tempShader);

	return tempShader;
}

lilRenderable* laGLRenderer::GetRenderable(const char* renderableName)
{
	for (std::list<lilRenderable*>::iterator it = m_Renderables.begin(); it != m_Renderables.end(); ++it)
		if ((*it)->name.compare(renderableName) == 0)
			return (*it);

	return 0;
}

void laGLRenderer::ClearRenderer()
{
	for (std::list<lilSprite*>::iterator it = m_Sprites.begin(); it != m_Sprites.end(); ++it)
	{
		(*it)->Destroy();
		delete (*it);
	}

	for (std::list<lilRenderable*>::iterator it = m_Renderables.begin(); it != m_Renderables.end(); ++it)
		delete (*it);

	for (std::list<lilMesh*>::iterator it = m_Meshes.begin(); it != m_Meshes.end(); ++it)
	{
		(*it)->Destroy();
		delete (*it);
	}

	for (std::list<lilTexture*>::iterator it = m_Textures.begin(); it != m_Textures.end(); ++it)
	{
		(*it)->Destroy();
		delete (*it);
	}

	for (std::list<lilShader*>::iterator it = m_Shaders.begin(); it != m_Shaders.end(); ++it)
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

void laGLRenderer::SetViewAndProjectionMatrix()
{
	for (std::list<lilShader*>::iterator it = m_Shaders.begin(); it != m_Shaders.end(); ++it)
	{
		(*it)->SetUniform("camera", glm::value_ptr(m_CurrentCamera->GetViewMatrix()));
		(*it)->SetUniform("projection", glm::value_ptr(m_CurrentCamera->GetProjectionMatrix()));
	}
}

