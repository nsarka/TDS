#pragma once

#include <string>

#include "SDL2/SDL_ttf.h"

#define PT_SIZE 80

class Text {
    public:
        Text(std::string path);
		~Text();

		SDL_Texture* SurfaceToTexture(SDL_Renderer* renderer, SDL_Surface* surf);
		SDL_Texture* RenderText(SDL_Renderer* renderer, std::string text);

        // Where to draw the fps counter
        SDL_Rect fps = {0, 0, 128, 128};
        TTF_Font* font;
};