#pragma once

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

#include <string>

// TODO: Make this class use a container to hold/access all spritesheets

class Spritesheet {
    public:
        Spritesheet(SDL_Renderer* renderer, std::string path);
		~Spritesheet();

		SDL_Texture* getTexture() { return txt; }

    private:
        SDL_Texture *txt;
		int w, h;
};