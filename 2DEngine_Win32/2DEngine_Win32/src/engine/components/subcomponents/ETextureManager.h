//
//  2DEngine
//  ETextureManager.h
//  Eric Fleming
//  4/4/2018
//

#pragma once

#include <list>

#include "ETexture.h"

#define lilTextureManager ETextureManager::Instance()

class ETextureManager
{
public:
	// Returns only instance of texture manager
	static ETextureManager* Instance();

	// Adds texture to manager
	// Returns created textures id, if texture exists, returns that texture id
	// @ filename - name of texture image to add
	unsigned AddTexture(const char* filename);

	// Frees all loaded textures
	void FreeTextures();

private:
	static ETextureManager* s_Instance;

	std::list<ETexture*> m_Textures;

private:
	// Only one copy
	ETextureManager() {}
	~ETextureManager() {}
	ETextureManager(const ETextureManager& textureManager) {}
	void operator=(const ETextureManager& textureManager) {}
};

