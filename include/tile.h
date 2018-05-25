#pragma once

#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
#include <locale>

#include "spritesheet.h"
#include "entity.h"

class Tile: public Entity {
    public:
        Tile(std::string spr_name, SDL_Rect pos, int phys);
        Tile(){}
		~Tile();

        void Draw(SDL_Renderer* renderer, Spritesheet* sheet);
        std::string Serialize();
        void Deserialize(std::string data);
        void SetAbsolutePosition(int x, int y);
        void move(int x, int y);
		SDL_Rect frame;
        SDL_Rect position;

    private:
        std::string spr_sheet_name;

        // Rectangles that correspond to each frame in that entity's animation cycle
        std::vector<SDL_Rect> animCycle;

        // Physics type
        int physics;
};