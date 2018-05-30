//
//  2DEngine
//  EShaderManager.cpp
//  Eric Fleming
//  4/3/2018
//

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "EShaderManager.h"

EShaderManager* EShaderManager::s_Instance = 0;

EShaderManager* EShaderManager::Instance()
{
	if (!s_Instance)
		s_Instance = new EShaderManager();

	return s_Instance;
}

EShader* EShaderManager::AddShader(const char * filename)
{
	for (std::list<EShader*>::iterator it = m_Shaders.begin(); it != m_Shaders.end(); ++it)
		if ((*it)->GetName().compare(filename) == 0)
			return (*it);

	EShader* tempShader = new EShader();
	tempShader->Create(filename);
	m_Shaders.push_back(tempShader);

	return tempShader;
}

void EShaderManager::FreeShaders()
{
	for (std::list<EShader*>::iterator it = m_Shaders.begin(); it != m_Shaders.end(); ++it)
	{
		(*it)->Destroy();
		delete (*it);
	}

	m_Shaders.clear();
}

void EShaderManager::SetViewAndProjectionMatrix(glm::mat4& viewMatrix, glm::mat4& projectionMatrix)
{
	for (std::list<EShader*>::iterator it = m_Shaders.begin(); it != m_Shaders.end(); ++it)
	{
		(*it)->SetUniform("camera", glm::value_ptr(viewMatrix));
		(*it)->SetUniform("projection", glm::value_ptr(projectionMatrix));
	}
}

