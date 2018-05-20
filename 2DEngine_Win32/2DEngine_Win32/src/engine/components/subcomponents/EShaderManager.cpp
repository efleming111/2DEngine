//
//  2DEngine
//  EShaderManager.cpp
//  Eric Fleming
//  4/3/2018
//

#include "EShaderManager.h"

EShaderManager* EShaderManager::s_Instance = 0;

EShaderManager* EShaderManager::Instance()
{
	if (!s_Instance)
		s_Instance = new EShaderManager();

	return s_Instance;
}

unsigned EShaderManager::AddShader(const char * filename)
{
	for (unsigned i = 0; i < m_Shaders.size(); ++i)
		if (m_Shaders[i]->GetName().compare(filename) == 0)
			return i;

	EShader* tempShader = new EShader();
	tempShader->Create(filename);
	m_Shaders.push_back(tempShader);

	return (unsigned)(m_Shaders.size() - 1);
}

void EShaderManager::FreeShaders()
{
	for (unsigned i = 0; i < m_Shaders.size(); ++i)
	{
		m_Shaders[i]->Destroy();
		delete m_Shaders[i];
		m_Shaders[i] = 0;
	}

	m_Shaders.resize(0);
}

EShader* EShaderManager::GetShader(unsigned index)
{
	if (index < m_Shaders.size())
		return m_Shaders[index];

	return 0;
}

