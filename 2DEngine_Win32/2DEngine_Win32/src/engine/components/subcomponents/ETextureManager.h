//
//  2DEngine
//  ETextureManager.h
//  Eric Fleming
//  4/4/2018
//

#pragma once

#include <vector>

#include "ETexture.h"

#define lilTextureManager ETextureManager::Instance()

class ETextureManager
{
public:
	// Returns only instance of texture manager
	static ETextureManager* Instance();

	// Adds texture to manager
	// Returns created texture, if texture exists, returns its texture ID
	// @ filename - name of texture image to add
	ETexture* AddTexture(const char* filename);

	// Frees all loaded textures
	void FreeTextures();

private:
	static ETextureManager* s_Instance;

	std::vector<ETexture*> m_Textures;

private:
	ETextureManager() {}
	~ETextureManager() {}
	ETextureManager(const ETextureManager& textureManager) {}
	void operator=(const ETextureManager& textureManager) {}
};

