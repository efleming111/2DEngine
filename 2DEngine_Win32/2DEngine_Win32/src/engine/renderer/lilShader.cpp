//
//  2DEngine
//  lilShader.cpp
//  Eric Fleming
//  4/3/2018
//

#include "../../../thirdpartysrc/glad/glad/glad.h"
#include <SDL.h>

#include "lilShader.h"
#include "../utilities/lilFileIO.h"

void lilShader::Create(const char* filename)
{
	m_Name = filename;
	std::string vertexShader = filename;
	std::string fragmentShader = filename;
	vertexShader += ".vert";
	fragmentShader += ".frag";

	unsigned vertexID = CompileVertexShader(vertexShader.c_str());
	unsigned fragmentID = ComplieFragmentShader(fragmentShader.c_str());

	m_ID = LinkShaderPrograms(vertexID, fragmentID);

	glDeleteShader(vertexID);
	glDeleteShader(fragmentID);
}

void lilShader::Destroy()
{
	glDeleteProgram(m_ID);
}

void lilShader::SetAsCurrent()
{
	glUseProgram(m_ID);
}

void lilShader::SetUniform(const char * name, bool value)
{
	int location = glGetUniformLocation(m_ID, name);
	glUseProgram(m_ID);
	glUniform1i(location, (int)value);
}

void lilShader::SetUniform(const char * name, int value)
{
	int location = glGetUniformLocation(m_ID, name);
	glUseProgram(m_ID);
	glUniform1i(location, value);
}

void lilShader::SetUniform(const char * name, float value)
{
	int location = glGetUniformLocation(m_ID, name);
	glUseProgram(m_ID);
	glUniform1f(location, value);
}

void lilShader::SetUniform(const char * name, float x, float y)
{
	int location = glGetUniformLocation(m_ID, name);
	glUseProgram(m_ID);
	glUniform2f(location, x, y);
}

void lilShader::SetUniform(const char * name, float x, float y, float z)
{
	int location = glGetUniformLocation(m_ID, name);
	glUseProgram(m_ID);
	glUniform3f(location, x, y, z);
}

void lilShader::SetUniform(const char* name, float x, float y, float z, float w)
{
	int location = glGetUniformLocation(m_ID, name);
	glUseProgram(m_ID);
	glUniform4f(location, x, y, z, w);
}

void lilShader::SetUniform(const char * name, glm::vec3 vec)
{
	int location = glGetUniformLocation(m_ID, name);
	glUseProgram(m_ID);
	glUniform3f(location, vec.x, vec.y, vec.z);
}

void lilShader::SetUniform(const char* name, float* mat4)
{
	int location = glGetUniformLocation(m_ID, name);
	glUseProgram(m_ID);
	glUniformMatrix4fv(location, 1, GL_FALSE, mat4);
}

char* lilShader::LoadShaderToString(const char* filename)
{
	return lilFileIO::ReadFile(filename, "r");
}

unsigned lilShader::CompileVertexShader(const char* filename)
{
	char* vertexShaderData = LoadShaderToString(filename);

	unsigned vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderData, NULL);
	glCompileShader(vertexShader);

	int result;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		char shaderLog[512];
		glGetShaderInfoLog(vertexShader, 512, NULL, shaderLog);
		SDL_Log("ERROR: Vertex Shader Failed: %s, %s %d", shaderLog, __FILE__, __LINE__);
	}

	delete[] vertexShaderData;
	vertexShaderData = 0;

	return vertexShader;
}

unsigned lilShader::ComplieFragmentShader(const char* filename)
{
	char* fragmentShaderData = LoadShaderToString(filename);

	unsigned fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderData, NULL);
	glCompileShader(fragmentShader);

	int result;
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		char shaderLog[512];
		glGetShaderInfoLog(fragmentShader, 512, NULL, shaderLog);
		SDL_Log("ERROR: Fragment Shader Failed: %s, %s %d", shaderLog, __FILE__, __LINE__);
	}

	delete[] fragmentShaderData;
	fragmentShaderData = 0;

	return fragmentShader;
}

unsigned lilShader::LinkShaderPrograms(unsigned vertexShader, unsigned fragmentShader)
{
	unsigned shaderProgram = glCreateProgram();

	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	int result;
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &result);
	if (!result)
	{
		char shaderLog[512];
		glGetProgramInfoLog(shaderProgram, 512, NULL, shaderLog);
		SDL_Log("ERROR: Shader Linking Failed: %s, %s %d", shaderLog, __FILE__, __LINE__);
	}

	return shaderProgram;
}

