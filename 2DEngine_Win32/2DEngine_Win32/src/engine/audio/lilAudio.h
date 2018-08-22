//
//  2DEngine
//  lilAudio.h
//  Eric Fleming
//  5/10/2018
//

#pragma once

#include <vector>

#include <SDL.h>
#include <SDL_mixer.h>

#define lilAudio laAudio::Instance()

class laAudio
{
public:
	// Returns only instance of class
	static laAudio* Instance();

	// Initialize in audio player, both music and soundfx
	bool Initialize();

	// Shoutdown audio player
	void Shutdown();

	// Adds music to the audio player
	// @ filename - name of music file
	void AddMusic(const char* filename);

	// Adds a sounfx to the audio player
	// @ filename - name of soundfx file
	void AddSound(const char* filename);

	// Frees all music in the audio player
	void FreeMusic();

	// Frees all soundfx in the audio player
	void FreeSounds();

	// Start playing music
	// @ index - index of the music to play
	void PlayMusic(unsigned index);

	// Pauses currently playing music
	void PauseMusic();

	// Stops currently playing music
	void StopMusic();

	// Plays a soundfx
	// @ index - index of the soundfx to play
	void PlaySound(unsigned index);

private:
	static laAudio* s_Instance;

	std::vector<Mix_Music*> m_Music;
	std::vector<Mix_Chunk*> m_Sounds;

private:
	// Only one instance of class and no copying
	laAudio() {}
	~laAudio() {}
	laAudio(const laAudio& audio) {}
	void operator=(const laAudio& audio) {}
};

