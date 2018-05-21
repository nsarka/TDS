#include "../include/spritesheet.h"

Spritesheet::Spritesheet() { }

void Spritesheet::loadTexture(std::string path, std::string name) {
	SDL_Texture* txt = IMG_LoadTexture(renderer, path.c_str());

	spr_list.insert(pair <std::string, SDL_Texture*> (name, txt));
}

void Spritesheet::printAllTexturesLoaded() {
	std::map <std::string, SDL_Texture*> :: iterator itr;

    std::cout << "\nThe map spr_list is : \n";
    std::cout << "\tKEY\tELEMENT\n";

    for (itr = spr_list.begin(); itr != spr_list.end(); ++itr)
    {
        std::cout  <<  '\t' << itr->first 
              <<  '\t' << itr->second << '\n';
    }
}

SDL_Texture* Spritesheet::getTexture(std::string name) {
	std::map::const_iterator pos = spr_list.find(name);

	if (spr_list == map.end()) {
		std::cout << name << " doesnt exist" << endl;
	} else {
		return pos->second;
	}
}

Spritesheet::~Spritesheet() {
	std::map <std::string, SDL_Texture*> :: iterator itr;

    for (itr = spr_list.begin(); itr != spr_list.end(); ++itr)
    {
		SDL_DestroyTexture(itr->second);
    }
	
}