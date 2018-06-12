#pragma once

#include <vector>
#include <sstream>
#include <string>
#include <queue>

#include "SDL2/SDL.h"

extern class std::vector<SDL_Rect*> collisionEntities;

class Physics {
    public:
		static bool checkCollision(SDL_Rect ent1, SDL_Rect ent2);
        static bool checkMouseCollision(SDL_Rect ent, SDL_Point point);
        static void setCollisionRect(SDL_Point, SDL_Point);
        static std::string serializeColliders(SDL_Rect* rect);
        static void deserializeColliders(std::string lineData, SDL_Rect* col);

	// Physics meant to be a static class. No constructing!
    private:
        Physics() {};
};