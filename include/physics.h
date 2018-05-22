#pragma once

#include "SDL2/SDL.h"

class Physics {
    public:
		static bool checkCollision(SDL_Rect ent1, SDL_Rect ent2);
        static bool checkMouseCollision(SDL_Rect ent, SDL_Point point);

	// Physics meant to be a static class. No constructing!
    private:
        Physics() {};
};