#include "../include/tile.h"

Tile::Tile(std::string spr_name, SDL_Rect pos, int phys) {
	spr_sheet_name = spr_name;
	position = pos;
	physics = phys;
}

Tile::~Tile() {

}

// Will need fixing later
void Tile::Draw(SDL_Renderer* renderer, Spritesheet* sheet) {
	//for(SDL_Rect frame : animCycle) {
        SDL_RenderCopy(renderer, sheet->getTexture(std::string("ground")), &frame, &position);
    //}
}