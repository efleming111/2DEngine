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
	{
		if ((*it)->isRendered)
		{
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, (*it)->m_Transform.position);
			model = glm::rotate(model, glm::radians((*it)->m_Transform.rotation), glm::vec3(0.0f, 0.0f, 1.0f));
			model = glm::scale(model, (*it)->m_Transform.scale);

			(*it)->shader->SetUniform("model", glm::value_ptr(model));

			glBindTexture(GL_TEXTURE_2D, (*it)->textureID);

			(*it)->mesh->Draw();
		}
	}

	lilGLWindow->SwapBuffers();
}

void EGLRenderer::RegisterCamera(ECamera* camera)
{
	m_CurrentCamera = camera;
}

void EGLRenderer::AddSprite(ESprite* sprite)
{
	if (sprite)
		m_Sprites.push_back(sprite);
}

void EGLRenderer::FreeSprites()
{
	for (std::list<ESprite*>::iterator it = m_Sprites.begin(); it != m_Sprites.end(); ++it)
	{
		(*it)->Destroy();
		delete (*it);
	}

	m_Sprites.clear();
}

