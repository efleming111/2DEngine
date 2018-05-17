//
//  2DEngine
//  EFileIO.cpp
//  Eric Fleming
//  4/2/2018
//

#include <sstream>

#include <SDL.h>

#include "EFileIO.h"

char* EFileIO::ReadFile(const char* filename, const char* mode)
{
	char* buffer = 0;

	SDL_RWops* read = SDL_RWFromFile(filename, mode);
	if (!read)
	{
		SDL_Log("ERROR: %s, %s %d", SDL_GetError(), __FILE__, __LINE__);
		return 0;
	}

	Uint64 sizeOfFile = SDL_RWsize(read);
	buffer = new char[(unsigned)sizeOfFile + 1];

	SDL_RWread(read, buffer, (size_t)sizeOfFile, 1);
	SDL_RWclose(read);

	buffer[sizeOfFile] = '\0';

	return buffer;
}

bool EFileIO::WriteFile(const char* filename, const char* mode, char* data)
{
	SDL_RWops* write = SDL_RWFromFile(filename, mode);
	if (!write)
	{
		SDL_Log("ERROR: %s, %s %d", SDL_GetError(), __FILE__, __LINE__);
		return false;
	}

	size_t lengthOfData = SDL_strlen(data);
	if (SDL_RWwrite(write, data, 1, lengthOfData) != lengthOfData)
	{
		SDL_Log("ERROR: %s, %s %d", SDL_GetError(), __FILE__, __LINE__);
		SDL_RWclose(write);
		return false;
	}

	SDL_RWclose(write);

	return true;
}

