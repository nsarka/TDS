#include "../include/level.h"

void Level::saveLevel(Entity* ent, std::ofstream& lvlFile) {
    lvlFile << ent->position.x;
    lvlFile << ent->position.y;
    lvlFile << ent->position.w;
    lvlFile << ent->position.h << ",";
}