//
//  2DEngine
//  lilTexture.h
//  Eric Fleming
//  4/4/2018
//

#pragma once

#include <string>

#include "../../../thirdpartysrc/glad/glad/glad.h"
#include <SDL.h>
#include <SDL_image.h>

class lilTexture
{
public:
	lilTexture() {}
	~lilTexture() {}

	// Creates texture
	// @ filename - name of texture image
	bool Create(const char* filename);

	// Closes texture and frees its memory
	void Destroy();

	// Returns texture id
	GLuint GetID();

	// Returns filename of texture
	std::string GetName();

private:
	GLuint m_ID;
	std::string m_Name;

private:
	// No copying
	lilTexture(const lilTexture& texture) {}
	void operator=(const lilTexture& texture) {}
};

