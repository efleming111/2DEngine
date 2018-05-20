//
//  2DEngine
//  EShader.h
//  Eric Fleming
//  4/3/2018
//

#pragma once

#include <string>

#include <glm/glm.hpp>

class EShader
{
public:
	EShader() {}
	~EShader() {}

	void Create(const char* filename);
	void Destroy();

	unsigned GetID() { return m_ID; }
	std::string GetName() { return m_Name; }

	void SetAsCurrent();

	void SetUniform(const char* name, bool value);
	void SetUniform(const char* name, int value);
	void SetUniform(const char* name, float value);
	void SetUniform(const char* name, float x, float y);
	void SetUniform(const char* name, float x, float y, float z);
	void SetUniform(const char* name, float x, float y, float z, float w);
	void SetUniform(const char* name, glm::vec3 vec);
	void SetUniform(const char* name, float *mat4);

private:
	unsigned m_ID;
	std::string m_Name;

private:
	char* LoadShaderToString(const char* filename);
	unsigned CompileVertexShader(const char* filename);
	unsigned ComplieFragmentShader(const char* filename);
	unsigned LinkShaderPrograms(unsigned vertexShader, unsigned fragmentShader);
};

