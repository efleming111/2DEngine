//
//  2DEngine
//  ETextureManager.cpp
//  Eric Fleming
//  4/4/2018
//

#include "ETextureManager.h"

ETextureManager* ETextureManager::s_Instance = 0;

ETextureManager* ETextureManager::Instance()
{
	if (!s_Instance)
		s_Instance = new ETextureManager();

	return s_Instance;
}

ETexture* ETextureManager::AddTexture(const char* filename)
{
	for (unsigned i = 0; i < m_Textures.size(); ++i)
		if (m_Textures[i]->GetName().compare(filename) == 0)
			return m_Textures[i];

	ETexture* tempTexture = new ETexture();
	tempTexture->Create(filename);
	m_Textures.push_back(tempTexture);

	return m_Textures.back();
}

void ETextureManager::FreeTextures()
{
	for (unsigned i = 0; i < m_Textures.size(); ++i)
	{
		m_Textures[i]->Destroy();
		delete m_Textures[i];
		m_Textures[i] = 0;
	}

	m_Textures.resize(0);
}

