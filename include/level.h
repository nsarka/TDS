#pragma once

#include "entity.h"

#include <iostream>
#include <fstream>

class Level {
    private:
        Level() {}

    public:
        static void saveLevel(std::string levelname, std::vector<Entity*> gameEntities);
};