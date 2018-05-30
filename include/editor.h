#pragma once

#include <vector>
#include <string>

#include "SDL2/SDL.h"

#include "spritesheet.h"
#include "camera.h"
#include "player.h"
#include "tile.h"

extern class Camera* cam;
extern class Player* plyr;
extern class std::vector<Entity*> gameEntities;
extern class Spritesheet* sheet;

class Editor {
    public:
        Editor();
		~Editor();

        SDL_Rect getSourceRect() { return sourceRectList.at(source_rect_counter); };

		int getSourceRectCounter() { return source_rect_counter; };
		void setSourceRectCounter(int counter) { source_rect_counter = counter; };

		void handleEvents(SDL_Event event);
		void drawGrid(SDL_Renderer* renderer);
		void drawSelected(SDL_Renderer* renderer, int x, int y);

		void addSourceRectToList(SDL_Rect rect) { sourceRectList.push_back(rect); }

    private:

        //SDL_Rect sheet_source_rect = { 32, 16, 16, 16 };

		int source_rect_counter = 0;
		std::vector<SDL_Rect> sourceRectList;
		std::string spr_sheet_name = "environment";
};