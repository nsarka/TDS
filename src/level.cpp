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

void Level::loadLevel(std::string levelname, std::vector<Entity*> * gameEntities) {
    std::ifstream level_file;
    level_file.open(levelname + ".level");

    // if(!level_file.is_open()) {
    //     std::cout << "Level not found" << std::endl;
    //     return;
    // }

    getline(level_file, levelname);
    std::cout << "Openning " << levelname << "..." << std::endl;

    std::string data;

    gameEntities->clear();
    
    while(!level_file.eof()) {
        Tile *ent = new Tile();
        getline(level_file, data);
        ent->Deserialize(data);
        gameEntities->push_back(ent);
    }
    
    
}