//
//  2DEngine
//  EShaderManager.h
//  Eric Fleming
//  4/3/2018
//

#pragma once

#include <list>

#include "EShader.h"

#define lilShaderManager EShaderManager::Instance()

class EShaderManager
{
public:
	// Returns only instance of shader manager
	static EShaderManager* Instance();

	// Adds shader to manager
	// Returns a pointer to created shader, if shader exists, returns pointer to that shader
	// @ filename - name of shader file, both vert and frag shader must be named the same
	EShader* AddShader(const char* filename);

	// Frees all loaded shaders
	void FreeShaders();

	// Sets the view and projection matrix for all shaders
	void SetViewAndProjectionMatrix(glm::mat4& viewMatrix, glm::mat4& projectionMatrix);

private:
	static EShaderManager* s_Instance;

	std::list<EShader*> m_Shaders;

private:
	// Only one copy
	EShaderManager() {}
	~EShaderManager() {}
	EShaderManager(const EShaderManager& shaderManager) {}
	void operator=(const EShaderManager& shaderManager) {}
};

