#include "../include/level.h"

void Level::saveLevel(std::string levelname, std::vector<Entity*> gameEntities) {
    std::ofstream level_file;
    level_file.open(levelname + ".level");
    level_file << levelname << std::endl;

    for (auto ent : gameEntities) {
        level_file << ent->Serialize() << std::endl;
    }

    level_file.close();

    std::cout << "Saved." << std::endl;
}