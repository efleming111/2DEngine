//
//  2DEngine
//  EAudio.h
//  Eric Fleming
//  5/10/2018
//

#pragma once

#include <vector>

#include <SDL.h>
#include <SDL_mixer.h>

#define lilAudio EAudio::Instance()

class EAudio
{
public:
	// Returns only instance of class
	static EAudio* Instance();

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
	static EAudio* s_Instance;

	std::vector<Mix_Music*> m_Music;
	std::vector<Mix_Chunk*> m_Sounds;

private:
	// Only one instance of class and no copying
	EAudio() {}
	~EAudio() {}
	EAudio(const EAudio& audio) {}
	void operator=(const EAudio& audio) {}
};

