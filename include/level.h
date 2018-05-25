#pragma once

#include "entity.h"
#include "tile.h"

#include <iostream>
#include <fstream>
#include <cstring>

class Level {
    private:
        Level() {}

    public:
        static void saveLevel(std::string levelname, std::vector<Entity*> gameEntities);
        static void loadLevel(std::string levelname, std::vector<Entity*> * gameEntities);
};