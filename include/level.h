#pragma once

#include "entity.h"
#include "tile.h"
#include "physics.h"

#include <iostream>
#include <fstream>
#include <cstring>
#include <sstream>

class Level {
    private:
        Level() {}

    public:
        static void saveLevel(std::string levelname, std::vector<Entity*> gameEntities);
        static void loadLevel(std::string levelname, std::vector<Entity*> * gameEntities);
        static void saveLevelColliders(std::string levelname, std::vector<SDL_Rect*> collisionEntities);
        static void loadLevelColliders(std::string levelname, std::vector<SDL_Rect*> * collisionEntities);
};