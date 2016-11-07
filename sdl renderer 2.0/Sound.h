#ifndef SOUND_H
#define SOUND_H

#include "SDL_mixer.h"

#include <iostream>

class Sound
{
public:
	//Load in Sound
	Sound();
	//Initialize - Initializes the sound library.
	//@return bool - true if successful.
	bool Initialize();
	//LoadFile - Loads the file.
	//@param char* - filename to load.
	//@return bool - true if loading was successful, false otherwise.
	bool LoadFile(char* filename);
	//Play - Plays the sound.
	void Play();
	//Pause - Pauses the sound.
	void Pause();
	//ChangeTrack - Change the track.
	//@param char* - filename to change the track to.
	void ChangeTrack(char* filename);
	//GetPlaying - tells if sound is playing.
	//@return bool - true if playing, false otherwise.
	bool GetPlaying();
	//Shutdown - Deletes the sound from memory and nulls the pointer.
	void Shutdown();
private:
	//Location of sound file in memory.
	Mix_Music* music;
};

#endif