#pragma once

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

#include <string>

// TODO: Make this class use a container to hold/access all spritesheets

/*
    spritesheet map:

    player1: assets/filenameforplayer1.png
    grasstile: assets/environment/grass.png

    SDL_Texture* playerText = getTexture('player1');
*/

class Spritesheet {
    public:
        Spritesheet(SDL_Renderer* renderer, std::string path);
		~Spritesheet();

		SDL_Texture* getTexture() { return txt; }

    private:
        SDL_Texture *txt;
		int w, h;
};