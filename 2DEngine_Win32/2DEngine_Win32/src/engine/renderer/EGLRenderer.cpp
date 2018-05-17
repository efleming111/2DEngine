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
#include "CShaderManager.h"
#include "CMeshManager.h"
#include "../gameobjects/CRenderableManager.h"

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
	for (unsigned i = 0; i < ShaderManager.size(); ++i)
	{
		ShaderManager->GetShader(i)->SetUniform("camera", glm::value_ptr(m_Camera->GetViewMatrix()));
		ShaderManager->GetShader(i)->SetUniform("projection", glm::value_ptr(m_Camera->GetProjectionMatrix()));
	}

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (unsigned i = 0; i < RenderableManager->Size(); ++i)
	{
		if (RenderableManager->GetRenderable(i)->rendered)
		{
			Renderable* renderable = RenderableManager->GetRenderable(i);

			// TODO: move this to renderable after renderer is working
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, renderable->transform.position);
			model = glm::rotate(model, glm::radians(renderable->transform.rotation), glm::vec3(0.0f, 0.0f, 1.0f));
			model = glm::scale(model, renderable->transform.scale);

			ShaderManager->GetShader(renderable->shader)->SetUniform("model", glm::value_ptr(model));

			glBindTexture(GL_TEXTURE_2D, renderable->textureID);
			MeshManager->GetMesh(renderable->meshIndex)->Draw();
		}
	}

	lilGLWindow->SwapBuffers();
}

void EGLRenderer::RegisterCamera(ECamera* camera)
{
	m_CurrentCamera = camera;
}

