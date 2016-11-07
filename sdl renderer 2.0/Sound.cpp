#include "Sound.h"

Sound::Sound()
{
	music = NULL;
}

bool Sound::Initialize()
{
	if(Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
	{
		std::cerr << "Failed to intialize audio library." << std::endl;
		return false;
	}
	return true;
}

bool Sound::LoadFile(char* filename)
{
	music = Mix_LoadMUS(filename);

	if(music == NULL)
	{
		std::cerr << "Failed to load music file, was it 22050hz, .wav, and 4096 in chunk size?" << std::endl;
		return false;
	}
	return true;
}

bool Sound::GetPlaying()
{
	if(Mix_PlayingMusic() == 0)
	{
		return false;
	}
	else
	{
		return true;
	}
	return false;
}

void Sound::ChangeTrack(char* filename)
{
	Mix_FreeMusic(music);
	Sound::LoadFile(filename);
	Sound::Play();
}

void Sound::Shutdown()
{
	Mix_FreeMusic(music);
	Mix_CloseAudio();
	music = NULL;
}

void Sound::Play()
{
	if(Mix_PlayMusic(music, -1) == -1)
	{
		std::cerr << "Unable to play music." << std::endl;
	}
}

void Sound::Pause()
{
	if(Mix_PausedMusic() == 1)
	{
		Mix_ResumeMusic();
	}
	else
	{
		Mix_PauseMusic();
	}
}