#pragma once

#include "entity.h"

// Zero indexed, so there's 4 frames 0-3
#define MAX_PLAYER_FRAMES 3

class Player: public Entity {
    public:
        Player(Spritesheet* sheet, std::string spr_path, int pclass, SDL_Rect pos);
		~Player();

        void Draw(SDL_Renderer* renderer, Spritesheet* sheet);
        void Move(int x, int y);
        std::string Serialize() { return std::string(""); };

        SDL_Rect position;

        bool is_moving = false;

    private:
        // For when we get to it
        int player_class;

        std::string spr_sheet_name;

        // Rectangles that correspond to each frame in that entity's animation cycle
        std::vector<SDL_Rect> animCycle;
        int animFrame = 0;
        int count = 0;

        // Physics type
        int physics = 0;
};