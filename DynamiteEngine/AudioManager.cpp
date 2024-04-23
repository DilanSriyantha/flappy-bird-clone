#include "AudioManager.h"
#include <sstream>

AudioManager::AudioManager(int wanted_freq, Uint16 wanted_format, int wanted_channels, int wanted_chunk_size)
	: frequency(wanted_freq), format(wanted_format), channels(wanted_channels), chunk_size(wanted_chunk_size)
{}

AudioManager::~AudioManager()
{
	music_sounds.clear();
	sfx_sounds.clear();
}

int AudioManager::init()
{
	// initialized only for .wav files
	// flags should be changed if we
	// need to use some other file types too
	if (Mix_Init(0) < 0)
	{
		std::stringstream ss_error;
		ss_error << "Couldn't initialize SDL_Mixer: " << Mix_GetError();

		return -1;
	}
	else
	{
		// audio channel is now open
		Mix_OpenAudio(frequency, format, channels, chunk_size);

		return 0;
	}
}

int AudioManager::addMusic(std::string id, std::string file_name)
{
	Mix_Music* music = Mix_LoadMUS(file_name.c_str());
	if (!music)
	{
		std::stringstream ss_error;
		ss_error << "Couldn't load music file: " << Mix_GetError();

		return -1;
	}
	music_sounds.emplace(id, std::move(music));

	return 0;
}

int AudioManager::addSfx(std::string id, std::string file_name)
{
	Mix_Chunk* sfx = Mix_LoadWAV(file_name.c_str());
	if (!sfx)
	{
		std::stringstream ss_error;
		ss_error << "Couldn't load sfx file: " << Mix_GetError();

		return -1;
	}
	sfx_sounds.emplace(id, std::move(sfx));

	return 0;
}

void AudioManager::playMusic(std::string id, int loops)
{
	// second argument is loop count
	// if we don't need to loop it at all
	// we can leave it like 0 or if
	// we need to loop it indefinetely 
	// we have to put it as -1 
	Mix_PlayMusic(music_sounds[id], loops);
}

void AudioManager::playSfx(std::string id, int loops)
{
	// first argument is channel
	// if we don't need it to play on 
	// specific channel we can just put
	// it like -1 and if we need to play
	// it on a specific channel, we 
	// are allowed to put the channel 
	Mix_PlayChannel(-1, sfx_sounds[id], loops);
}

int AudioManager::setVolumeChannel(int channel, int new_volume)
{
	if (Mix_Volume(channel, new_volume) < 0)
	{
		error_message = Mix_GetError();
		return -1;
	}
	return 0;
}

int AudioManager::setVolumeMusic(int new_volume)
{
	if (Mix_VolumeMusic(new_volume) < 0)
	{
		error_message = Mix_GetError();
		return -1;
	}
	music_volume = new_volume;
	return 0;
}

int AudioManager::setVolumeSfx(std::string sfx_id, int new_volume)
{
	if (Mix_VolumeChunk(sfx_sounds[sfx_id], new_volume) < 0)
	{
		error_message = Mix_GetError();
		return -1;
	}
	sfx_volume = new_volume;
	return 0;
}

int AudioManager::getVolumeMusic()
{
	return music_volume;
}

int AudioManager::getVolumeSfx()
{
	return sfx_volume;
}

std::string AudioManager::getError()
{
	return error_message;
}