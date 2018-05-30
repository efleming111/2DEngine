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

unsigned ETextureManager::AddTexture(const char* filename)
{
	for (std::list<ETexture*>::iterator it = m_Textures.begin(); it != m_Textures.end(); ++it)
		if ((*it)->GetName().compare(filename) == 0)
			return (*it)->GetID();

	ETexture* tempTexture = new ETexture();
	tempTexture->Create(filename);
	m_Textures.push_back(tempTexture);

	return tempTexture->GetID();
}

void ETextureManager::FreeTextures()
{
	for (std::list<ETexture*>::iterator it = m_Textures.begin(); it != m_Textures.end(); ++it)
	{
		(*it)->Destroy();
		delete (*it);
	}

	m_Textures.clear();
}

