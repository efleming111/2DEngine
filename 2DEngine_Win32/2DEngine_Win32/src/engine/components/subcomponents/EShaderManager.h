//
//  2DEngine
//  EShaderManager.h
//  Eric Fleming
//  4/3/2018
//

#pragma once

#include <vector>

#include "EShader.h"

#define lilShaderManager EShaderManager::Instance()

class EShaderManager
{
public:
	// Returns only instance of shader manager
	static EShaderManager* Instance();

	// Adds shader to manager
	// Returns index of shader, if shader exists, returns its shader ID
	// @ filename - name of shader file, both vert and frag shader must be named the same
	unsigned AddShader(const char* filename);

	// Frees all loaded shaders
	void FreeShaders();

	// Get shader requested by index
	EShader* GetShader(unsigned index);

	unsigned Size() { return (unsigned)m_Shaders.size(); }

private:
	static EShaderManager* s_Instance;

	std::vector<EShader*> m_Shaders;

private:
	EShaderManager() {}
	~EShaderManager() {}
	EShaderManager(const EShaderManager& shaderManager) {}
	void operator=(const EShaderManager& shaderManager) {}
};

