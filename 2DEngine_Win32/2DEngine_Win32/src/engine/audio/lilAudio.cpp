//
//  2DEngine
//  lilAudio.cpp
//  Eric Fleming
//  5/10/2018
//

#include "lilAudio.h"

laAudio* laAudio::sInstance = 0;

laAudio* laAudio::Instance()
{
	if (!sInstance)
		sInstance = new laAudio();

	return sInstance;
}

bool laAudio::Initialize()
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

void laAudio::Shutdown()
{
	FreeMusic();
	FreeSounds();

	Mix_CloseAudio();
	Mix_Quit();
}

void laAudio::AddMusic(const char* filename)
{
	Mix_Music* music = Mix_LoadMUS(filename);
	mMusic.push_back(music);
}

void laAudio::AddSound(const char* filename)
{
	Mix_Chunk* sound = Mix_LoadWAV(filename);
	mSounds.push_back(sound);
}

void laAudio::FreeMusic()
{
	for (unsigned i = 0; i < mMusic.size(); ++i)
		Mix_FreeMusic(mMusic[i]);

	mMusic.resize(0);
}

void laAudio::FreeSounds()
{
	for (unsigned i = 0; i < mSounds.size(); ++i)
		Mix_FreeChunk(mSounds[i]);

	mSounds.resize(0);
}

void laAudio::PlayMusic(unsigned index)
{
	if (index < mMusic.size())
	{
		if (!Mix_PlayingMusic())
			Mix_PlayMusic(mMusic[index], -1);

		else if (Mix_PausedMusic())
			Mix_ResumeMusic();
	}

}

void laAudio::PauseMusic()
{
	if (Mix_PlayingMusic())
		Mix_PauseMusic();
}

void laAudio::StopMusic()
{
	Mix_HaltMusic();
}

void laAudio::PlaySound(unsigned index)
{
	if (index < mSounds.size())
		Mix_PlayChannel(-1, mSounds[index], 0);
}

