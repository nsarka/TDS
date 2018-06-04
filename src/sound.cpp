#include "../include/sound.h"

Sound::Sound() {
	//Initialize SDL_mixer 
	if( Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1 ) 
		std::cout << "[!] SDL_Mixer could not be initialized." << std::endl;
}

Sound::~Sound() {
    for (auto itr = sound_list.begin(); itr != sound_list.end(); ++itr) {
		Mix_FreeChunk(itr->second);
    }

    for (auto itr1 = music_list.begin(); itr1 != music_list.end(); ++itr1) {
		Mix_FreeMusic(itr1->second);
    }
}

void Sound::playSound(std::string name) {
	Mix_PlayChannel(-1, sound_list[name], 0);
}

void Sound::loadSound(std::string path, std::string name) {
	Mix_Chunk* wave = Mix_LoadWAV(path.c_str());

	if (wave != NULL)
		sound_list.insert(std::pair <std::string, Mix_Chunk*> (name, wave));
	else {
		std::cout << "[!] " << path << " sound not found" << std::endl;
	}
}

void Sound::playMusic(std::string name) {
	Mix_PlayMusic(music_list[name], -1);
}

void Sound::loadMusic(std::string path, std::string name) {
	Mix_Music* music = Mix_LoadMUS(path.c_str());

	if (music != NULL)
		music_list.insert(std::pair <std::string, Mix_Music*> (name, music));
	else {
		std::cout << "[!] " << path << " music not found" << std::endl;
	}
}

void Sound::printAllSoundsLoaded() {
	std::map <std::string, Mix_Chunk*> :: iterator itr;

    std::cout << "\nThe map sound_list is : \n";
    std::cout << "\tKEY\tELEMENT\n";

    for (itr = sound_list.begin(); itr != sound_list.end(); ++itr) {
        std::cout  <<  '\t' << itr->first 
              <<  '\t' << itr->second << '\n';
    }
}

void Sound::printAllMusicLoaded() {
	std::map <std::string, Mix_Music*> :: iterator itr;

    std::cout << "\nThe map music_list is : \n";
    std::cout << "\tKEY\tELEMENT\n";

    for (itr = music_list.begin(); itr != music_list.end(); ++itr) {
        std::cout  <<  '\t' << itr->first 
              <<  '\t' << itr->second << '\n';
    }
}