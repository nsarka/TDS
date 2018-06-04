#pragma once

#include "SDL2/SDL.h"
#include "SDL2/SDL_mixer.h"

#include <string>
#include <iostream>
#include <map>

class Sound {
    public:
        Sound();
		~Sound();

		void playSound(std::string name);
        void loadSound(std::string path, std::string name);

		void playMusic(std::string name);
		void loadMusic(std::string path, std::string name);

		bool isMusicPlaying() { return Mix_PlayingMusic(); }

        void printAllSoundsLoaded();
		void printAllMusicLoaded();

    private:
        std::map <std::string, Mix_Chunk*> sound_list;
		std::map <std::string, Mix_Music*> music_list;
};