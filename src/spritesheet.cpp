#include "../include/spritesheet.h"

Spritesheet::Spritesheet(SDL_Renderer* r) {
	renderer = r;
}

void Spritesheet::loadTexture(std::string path, std::string name) {
	SDL_Texture* txt = IMG_LoadTexture(renderer, path.c_str());

	if ( txt == NULL ) {
        std::cout << "Failed to load texture " << name << " error : " << SDL_GetError() << std::endl;
    }

	spr_list.insert(std::pair <std::string, SDL_Texture*> (name, txt));
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
	return spr_list[name];
}

Spritesheet::~Spritesheet() {
	std::map <std::string, SDL_Texture*> :: iterator itr;

    for (itr = spr_list.begin(); itr != spr_list.end(); ++itr)
    {
		SDL_DestroyTexture(itr->second);
    }
	
}