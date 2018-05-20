//
//  2DEngine
//  ETexture.cpp
//  Eric Fleming
//  4/4/2018
//

#include "ETexture.h"

bool ETexture::Create(const char * filename)
{
	m_Name = filename;

	glGenTextures(1, &m_ID);

	SDL_Surface* tempSurface = IMG_Load(filename);
	if (!tempSurface)
	{
		SDL_Log("ERROR: %s, %s %d", IMG_GetError(), __FILE__, __LINE__);
		return false;
	}

	int imageWidth = tempSurface->w;
	int imageHeight = tempSurface->h;
	unsigned imageSize = 0;
	GLubyte* imagePixels = 0;

	glBindTexture(GL_TEXTURE_2D, m_ID);

	int colorMode = 0;
	if (tempSurface->format->BytesPerPixel == 3)
	{
		colorMode = GL_RGB;
		imageSize = imageWidth * imageHeight * 3;
		imagePixels = new GLubyte[imageSize];
	}

	else if (tempSurface->format->BytesPerPixel == 4)
	{
		colorMode = GL_RGBA;
		imageSize = imageWidth * imageHeight * 4;
		imagePixels = new GLubyte[imageSize];
	}

	else
	{
		SDL_Log("Texture Failed To Load: Unsupported Color Mode %s %d", __FILE__, __LINE__);
		SDL_FreeSurface(tempSurface);
		return false;
	}

	glTexImage2D(GL_TEXTURE_2D, 0, colorMode, tempSurface->w, tempSurface->h, 0, colorMode, GL_UNSIGNED_BYTE, (GLubyte*)tempSurface->pixels);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	delete[] imagePixels;
	imagePixels = 0;

	SDL_FreeSurface(tempSurface);

	return true;
}

void ETexture::Destroy()
{
	glDeleteTextures(1, &m_ID);
}

GLuint ETexture::GetID()
{
	return m_ID;
}

std::string ETexture::GetName()
{
	return m_Name;
}