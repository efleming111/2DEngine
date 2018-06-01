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
#include "../components/subcomponents/EShaderManager.h"
#include "../components/subcomponents/EMeshManager.h"
#include "../components/subcomponents/ETextureManager.h"

EGLRenderer* EGLRenderer::s_Instance = 0;

void ERenderable::Create(TiXmlElement* element, float pixelsPerGameUnit)
{
	m_PixelsPerGameUnit = pixelsPerGameUnit;

	name = element->Attribute("name");

	double texLeft, texRight, texTop, texBottom;

	element->Attribute("texleft", &texLeft);
	element->Attribute("texright", &texRight);
	element->Attribute("textop", &texTop);
	element->Attribute("texbottom", &texBottom);

	float halfWidth = m_PixelsPerGameUnit * .5f;
	float halfHeight = m_PixelsPerGameUnit * .5f;

	float vertexData[20] = {
		-halfWidth, -halfHeight, 0.0f,		(float)texLeft, (float)texTop,
		halfWidth, -halfHeight, 0.0f,		(float)texRight, (float)texTop,
		halfWidth, halfHeight, 0.0f,		(float)texRight, (float)texBottom,
		-halfWidth, halfHeight, 0.0f,		(float)texLeft, (float)texBottom
	};

	unsigned short indices[6] = { 0, 1, 3, 3, 1, 2 };

	m_Mesh = lilMeshManager->AddMesh(vertexData, 20, indices, 6);

	std::string textureFile = element->Attribute("texturefile");
	m_TextureID = lilTextureManager->AddTexture(textureFile.c_str());

	std::string shaderFile = element->Attribute("shaderfile");
	m_Shader = lilShaderManager->AddShader(shaderFile.c_str());
}

void ERenderable::Draw(ESprite* sprite)
{
	if (sprite->isRendered)
	{
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, sprite->transform.position * m_PixelsPerGameUnit);
		model = glm::rotate(model, glm::radians(sprite->transform.rotation), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, sprite->transform.scale);

		m_Shader->SetUniform("model", glm::value_ptr(model));

		glBindTexture(GL_TEXTURE_2D, m_TextureID);

		m_Mesh->Draw();
	}
}

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

	// TODO: depth testing not working
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
	lilShaderManager->SetViewAndProjectionMatrix(m_CurrentCamera->GetViewMatrix(), m_CurrentCamera->GetProjectionMatrix());

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (std::list<ESprite*>::iterator it = m_Sprites.begin(); it != m_Sprites.end(); ++it)
		(*it)->Draw();

	lilGLWindow->SwapBuffers();
}

void EGLRenderer::RegisterCamera(ECamera* camera)
{
	m_CurrentCamera = camera;
}

ERenderable* EGLRenderer::AddSprite(ESprite* sprite, TiXmlElement* element, float pixelsPerGameUnit)
{
	std::string renderableName = element->Attribute("name");

	ERenderable* renderable = 0;
	bool createRenderable = true;
	for (std::list<ERenderable*>::iterator it = m_Renderables.begin(); it != m_Renderables.end(); ++it)
		if (renderableName.compare((*it)->name) == 0)
		{
			renderable = (*it);
			createRenderable = false;
		}

	if (createRenderable)
	{
		renderable = new ERenderable();
		renderable->Create(element, pixelsPerGameUnit);
		m_Renderables.push_back(renderable);
	}
	
	m_Sprites.push_back(sprite);

	return renderable;
}

void EGLRenderer::FreeRenderer()
{
	for (std::list<ESprite*>::iterator it = m_Sprites.begin(); it != m_Sprites.end(); ++it)
	{
		(*it)->Destroy();
		delete (*it);
	}

	for (std::list<ERenderable*>::iterator it = m_Renderables.begin(); it != m_Renderables.end(); ++it)
		delete (*it);

	m_Sprites.clear();
	m_Renderables.clear();
}

