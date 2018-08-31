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

laGLRenderer* laGLRenderer::sInstance = 0;

laGLRenderer* laGLRenderer::Instance()
{
	if (!sInstance)
		sInstance = new laGLRenderer();

	return sInstance;
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

	for (std::list<lilSprite*>::iterator it = mSprites.begin(); it != mSprites.end(); ++it)
		(*it)->Draw();

	lilGLWindow->SwapBuffers();
}

void laGLRenderer::RegisterCamera(lilCamera* camera)
{
	mCurrentCamera = camera;
}

lilRenderable* laGLRenderer::AddSprite(lilSprite* sprite)
{
	lilRenderable* renderable = 0;
	for (std::list<lilRenderable*>::iterator it = mRenderables.begin(); it != mRenderables.end(); ++it)
		if (sprite->renderableName.compare((*it)->name) == 0)
			renderable = (*it);
	
	mSprites.push_back(sprite);

	return renderable;
}

void laGLRenderer::AddRenderable(TiXmlElement* element, float pixelsPerGameUnit)
{
	lilRenderable* renderable = new lilRenderable();
	renderable->Create(element, pixelsPerGameUnit);
	mRenderables.push_back(renderable);
}

lilMesh* laGLRenderer::AddMesh(float * vertexData, int vertexCount, unsigned short * indices, int indicesCount)
{
	lilMesh* mesh;
	mesh = new lilMesh();
	mesh->Create(vertexData, vertexCount, indices, indicesCount);

	mMeshes.push_back(mesh);

	return mesh;
}

unsigned laGLRenderer::AddTexture(const char * filename)
{
	for (std::list<lilTexture*>::iterator it = mTextures.begin(); it != mTextures.end(); ++it)
		if ((*it)->GetName().compare(filename) == 0)
			return (*it)->GetID();

	lilTexture* tempTexture = new lilTexture();
	tempTexture->Create(filename);
	mTextures.push_back(tempTexture);

	return tempTexture->GetID();
}

lilShader* laGLRenderer::AddShader(const char * filename)
{
	for (std::list<lilShader*>::iterator it = mShaders.begin(); it != mShaders.end(); ++it)
		if ((*it)->GetName().compare(filename) == 0)
			return (*it);

	lilShader* tempShader = new lilShader();
	tempShader->Create(filename);
	mShaders.push_back(tempShader);

	return tempShader;
}

lilRenderable* laGLRenderer::GetRenderable(const char* renderableName)
{
	for (std::list<lilRenderable*>::iterator it = mRenderables.begin(); it != mRenderables.end(); ++it)
		if ((*it)->name.compare(renderableName) == 0)
			return (*it);

	return 0;
}

void laGLRenderer::ClearRenderer()
{
	for (std::list<lilSprite*>::iterator it = mSprites.begin(); it != mSprites.end(); ++it)
	{
		(*it)->Destroy();
		delete (*it);
	}

	for (std::list<lilRenderable*>::iterator it = mRenderables.begin(); it != mRenderables.end(); ++it)
		delete (*it);

	for (std::list<lilMesh*>::iterator it = mMeshes.begin(); it != mMeshes.end(); ++it)
	{
		(*it)->Destroy();
		delete (*it);
	}

	for (std::list<lilTexture*>::iterator it = mTextures.begin(); it != mTextures.end(); ++it)
	{
		(*it)->Destroy();
		delete (*it);
	}

	for (std::list<lilShader*>::iterator it = mShaders.begin(); it != mShaders.end(); ++it)
	{
		(*it)->Destroy();
		delete (*it);
	}

	mSprites.clear();
	mRenderables.clear();
	mMeshes.clear();
	mTextures.clear();
	mShaders.clear();
}

void laGLRenderer::SetViewAndProjectionMatrix()
{
	for (std::list<lilShader*>::iterator it = mShaders.begin(); it != mShaders.end(); ++it)
	{
		(*it)->SetUniform("camera", glm::value_ptr(mCurrentCamera->GetViewMatrix()));
		(*it)->SetUniform("projection", glm::value_ptr(mCurrentCamera->GetProjectionMatrix()));
	}
}

