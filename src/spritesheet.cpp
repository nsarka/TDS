#include "../include/spritesheet.h"

Spritesheet::Spritesheet(SDL_Renderer* renderer, std::string path) {
	txt = IMG_LoadTexture(renderer, path.c_str());
	SDL_QueryTexture(txt, NULL, NULL, &w, &h);
}

Spritesheet::~Spritesheet() {
	SDL_DestroyTexture(txt);
}