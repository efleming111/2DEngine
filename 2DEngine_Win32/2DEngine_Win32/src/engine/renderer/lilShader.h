//
//  2DEngine
//  lilShader.h
//  Eric Fleming
//  4/3/2018
//

#pragma once

#include <string>

#include <glm/glm.hpp>

class lilShader
{
public:
	lilShader() {}
	~lilShader() {}

	// Creates shader
	// @ filename - filename of vertex/fragment shaders without ext.
	void Create(const char* filename);

	// Frees the shader program memory
	void Destroy();

	// Gets the id of the shader program
	unsigned GetID() { return m_ID; }

	// Gets the name of the shader program
	std::string GetName() { return m_Name; }

	// Sets this shader as the current shader being used
	void SetAsCurrent();

	// Set the uniform variable at name to value(s) passed
	void SetUniform(const char* name, bool value);
	// Set the uniform variable at name to value(s) passed
	void SetUniform(const char* name, int value);
	// Set the uniform variable at name to value(s) passed
	void SetUniform(const char* name, float value);
	// Set the uniform variable at name to value(s) passed
	void SetUniform(const char* name, float x, float y);
	// Set the uniform variable at name to value(s) passed
	void SetUniform(const char* name, float x, float y, float z);
	// Set the uniform variable at name to value(s) passed
	void SetUniform(const char* name, float x, float y, float z, float w);
	// Set the uniform variable at name to value(s) passed
	void SetUniform(const char* name, glm::vec3 vec);
	// Set the uniform variable at name to value(s) passed
	void SetUniform(const char* name, float* mat4);

private:
	unsigned m_ID;
	std::string m_Name;

private:
	char* LoadShaderToString(const char* filename);
	unsigned CompileVertexShader(const char* filename);
	unsigned ComplieFragmentShader(const char* filename);
	unsigned LinkShaderPrograms(unsigned vertexShader, unsigned fragmentShader);
};

