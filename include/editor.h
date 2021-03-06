#pragma once

#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include <locale>
#include <queue>
#include <fstream>

#include "SDL2/SDL.h"

#include "spritesheet.h"
#include "camera.h"
#include "player.h"
#include "tile.h"
#include "physics.h"

extern class Camera* cam;
extern class Player* plyr;
extern class std::vector<Entity*> gameEntities;
extern class std::vector<SDL_Rect*> collisionEntities;
extern class Spritesheet* sheet;
extern class Sound* sound;
extern int xMouse, yMouse;
extern bool drawCol;

class Editor {
    public:
        Editor();
		~Editor();

        SDL_Rect getSourceRect() { return sourceRectList.at(source_rect_counter); };

		int getSourceRectCounter() { return source_rect_counter; };
		void setSourceRectCounter(int counter) { source_rect_counter = counter; };

		void handleEvents(SDL_Event event);
		void drawGrid(SDL_Renderer* renderer);
		void drawColliders(SDL_Renderer* renderer);
		void drawSelected(SDL_Renderer* renderer, int x, int y);
		void loadSprites();
		void Deserialize(std::string data);

		void addSourceRectToList(SDL_Rect rect) { sourceRectList.push_back(rect); }

    private:

        //SDL_Rect sheet_source_rect = { 32, 16, 16, 16 };

		int source_rect_counter = 0;
		bool buttonDown = true;
		bool colliderMode = false;
		SDL_Point pointDown, pointUp;
		std::vector<SDL_Rect> sourceRectList;
		std::string spr_sheet_name = "environment";
};