//
//  2DEngine
//  EAudio.cpp
//  Eric Fleming
//  5/10/2018
//

#include "EAudio.h"

EAudio* EAudio::s_Instance = 0;

EAudio* EAudio::Instance()
{
	if (!s_Instance)
		s_Instance = new EAudio();

	return s_Instance;
}

bool EAudio::Initialize()
{
	if (!SDL_WasInit(SDL_INIT_AUDIO))
		SDL_InitSubSystem(SDL_INIT_AUDIO);

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048))
	{
		SDL_Log("ERROR: Audio Failed To Initialize %s, %s %d", Mix_GetError(), __FILE__, __LINE__);
		return false;
	}

	return true;
}

void EAudio::Shutdown()
{
	FreeMusic();
	FreeSounds();

	Mix_CloseAudio();
	Mix_Quit();
}

void EAudio::AddMusic(const char* filename)
{
	Mix_Music* music = Mix_LoadMUS(filename);
	m_Music.push_back(music);
}

void EAudio::AddSound(const char* filename)
{
	Mix_Chunk* sound = Mix_LoadWAV(filename);
	m_Sounds.push_back(sound);
}

void EAudio::FreeMusic()
{
	for (unsigned i = 0; i < m_Music.size(); ++i)
		Mix_FreeMusic(m_Music[i]);

	m_Music.resize(0);
}

void EAudio::FreeSounds()
{
	for (unsigned i = 0; i < m_Sounds.size(); ++i)
		Mix_FreeChunk(m_Sounds[i]);

	m_Sounds.resize(0);
}

void EAudio::PlayMusic(unsigned index)
{
	if (index < m_Music.size())
	{
		if (!Mix_PlayingMusic())
			Mix_PlayMusic(m_Music[index], -1);

		else if (Mix_PausedMusic())
			Mix_ResumeMusic();
	}

}

void EAudio::PauseMusic()
{
	if (Mix_PlayingMusic())
		Mix_PauseMusic();
}

void EAudio::StopMusic()
{
	Mix_HaltMusic();
}

void EAudio::PlaySound(unsigned index)
{
	if (index < m_Sounds.size())
		Mix_PlayChannel(-1, m_Sounds[index], 0);
}

