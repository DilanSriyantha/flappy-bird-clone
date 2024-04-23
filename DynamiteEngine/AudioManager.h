#pragma once

#include <SDL_mixer.h>
#include <map>
#include <string>

class AudioManager
{
public:
	AudioManager(int wanted_freq, Uint16 wanted_format, int wanted_channels, int wanted_chunk_size);

	~AudioManager();

	int init();
	int addMusic(std::string id, std::string file_name);
	int addSfx(std::string id, std::string file_name);
	void playMusic(std::string id, int loops);
	void playSfx(std::string id, int loops);
	int setVolumeChannel(int channel, int new_volume);
	int setVolumeMusic(int new_volume);
	int setVolumeSfx(std::string sfx_id , int new_volume);
	int getVolumeMusic();
	int getVolumeSfx();
	std::string getError();

private:
	int frequency;
	Uint16 format;
	int channels; // 2 - stereo
	int chunk_size; // like sample rate
	int music_volume = MIX_MAX_VOLUME;
	int sfx_volume = MIX_MAX_VOLUME;
	std::string error_message;
	std::map <std::string, Mix_Music*> music_sounds;
	std::map <std::string, Mix_Chunk*> sfx_sounds;
};