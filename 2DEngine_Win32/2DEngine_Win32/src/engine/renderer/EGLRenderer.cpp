//
//  2DEngine
//  EGLRenderer.cpp
//  Eric Fleming
//  4/2/2018
//

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "EGLRenderer.h"
#include "EGLWindow.h"
#include "../components/subcomponents/EShaderManager.h"
#include "../components/subcomponents/EMeshManager.h"

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

	// TODO: depth testing not working
	glEnable(GL_DEPTH_TEST);

	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

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
	for (unsigned i = 0; i < lilShaderManager->Size(); ++i)
	{
		lilShaderManager->GetShader(i)->SetUniform("camera", glm::value_ptr(m_CurrentCamera->GetViewMatrix()));
		lilShaderManager->GetShader(i)->SetUniform("projection", glm::value_ptr(m_CurrentCamera->GetProjectionMatrix()));
	}

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (unsigned i = 0; i < m_Sprites.size(); ++i)
	{
		if (m_Sprites[i]->isRendered)
		{
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, m_Sprites[i]->m_Transform.position);
			model = glm::rotate(model, glm::radians(m_Sprites[i]->m_Transform.rotation), glm::vec3(0.0f, 0.0f, 1.0f));
			model = glm::scale(model, m_Sprites[i]->m_Transform.scale);

			lilShaderManager->GetShader(m_Sprites[i]->shaderIndex)->SetUniform("model", glm::value_ptr(model));

			glBindTexture(GL_TEXTURE_2D, m_Sprites[i]->textureID);
			lilMeshManager->GetMesh(m_Sprites[i]->meshIndex)->Draw();
		}
	}

	lilGLWindow->SwapBuffers();
}

void EGLRenderer::RegisterCamera(ECameraComponent* camera)
{
	m_CurrentCamera = camera;
}

void EGLRenderer::AddSprite(ESpriteComponent* sprite)
{
	if (sprite)
		m_Sprites.push_back(sprite);
}

void EGLRenderer::FreeSprites()
{
	for (unsigned i = 0; i < m_Sprites.size(); ++i)
	{
		m_Sprites[i]->Destroy();
		delete m_Sprites[i];
	}
}

