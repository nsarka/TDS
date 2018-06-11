#pragma once

#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
#include <locale>
#include <queue>

#include "spritesheet.h"
#include "entity.h"

class Tile: public Entity {
    public:
        Tile(std::string spr_name, SDL_Rect pos, int phys);
        // Tile(int num, SDL_Rect col, int phys);
        Tile(){}
		~Tile();

        void Draw(SDL_Renderer* renderer, Spritesheet* sheet);
        std::string Serialize();
        void Deserialize(std::string lineData);
        void SetAbsolutePosition(int x, int y);
        void move(int x, int y);
        // Collider
        SDL_Rect position;
        // Rectangles that correspond to each frame in that entity's animation cycle
        std::vector<SDL_Rect> animCycle;
        void DebugPrint();

    private:
        std::string spr_sheet_name;

        

        // Physics type
        int physics;
};