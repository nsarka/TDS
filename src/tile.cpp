#include "../include/tile.h"

Tile::Tile(std::string spr_name, SDL_Rect pos, int phys) {
	spr_sheet_name = spr_name;
	position = pos;
	physics = phys;
}

Tile::~Tile() {

}

// Will need fixing later so it iterates over animCycle
void Tile::Draw(SDL_Renderer* renderer, Spritesheet* sheet) {

	SDL_Rect camAdjusted = {
		position.x + cam->getOffsetX(),
		position.y + cam->getOffsetY(),
		position.w,
		position.h
	};

    SDL_RenderCopy(renderer, sheet->getTexture(std::string("ground")), &frame, &camAdjusted);
}

void Tile::SetAbsolutePosition(int x, int y) {
	position.x = x;
	position.y = y;
}

void Tile::move(int x, int y) {
	position.x += x;
	position.y += y;
}
