#pragma once

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

#include <string>
#include <iostream>
#include <map>

class Spritesheet {
    public:
        Spritesheet(SDL_Renderer* r);
		~Spritesheet();

		SDL_Texture* getTexture(std::string name);
        void loadTexture(std::string path, std::string name);
        void printAllTexturesLoaded();

    private:
        std::map <std::string, SDL_Texture*> spr_list;
        SDL_Renderer* renderer;
};