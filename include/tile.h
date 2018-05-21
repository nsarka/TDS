#pragma once

#include <iostream>

#include "spritesheet.h"
#include "entity.h"

class Tile: public Entity {
    public:
        Tile(std::string spr_name, SDL_Rect pos, int phys);
		~Tile();

        void Draw(SDL_Renderer* renderer, Spritesheet* sheet);
		SDL_Rect frame;

    private:
        std::string spr_sheet_name;

        // Rectangles that correspond to each frame in that entity's animation cycle
        std::vector<SDL_Rect> animCycle;

        // Game destination rect
        SDL_Rect position;

        // Physics type
        int physics;
};