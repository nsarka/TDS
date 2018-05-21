#pragma once

#include "entity.h"

class Player: public Entity {
    public:
        Player();
		~Player();

        void Draw(SDL_Renderer* renderer, Spritesheet* sheet);

    private:
        // For when we get to it
        int player_class;

        std::string spr_sheet_name;

        // Rectangles that correspond to each frame in that entity's animation cycle
        std::vector<SDL_Rect> animCycle;

        // Game destination rect
        SDL_Rect position;

        // Physics type
        int physics;
};