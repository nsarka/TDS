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

    SDL_RenderCopy(renderer, sheet->getTexture(spr_sheet_name), &frame, &camAdjusted);
}

std::string Tile::Serialize() {
	std::stringstream ss;

	ss << spr_sheet_name << ",";

	ss << frame.x << ",";
	ss << frame.y << ",";
	ss << frame.w << ",";
	ss << frame.h << ",";

	//ss << currentFrame << "|";

	// for(SDL_Rect rect : animCycle) {
	// 	ss << rect.x << ",";
	// 	ss << rect.y << ",";
	// 	ss << rect.w << ",";
	// 	ss << rect.h << ",";
	// }

	//ss << currentFrame << "|";

	ss << currentFrame << ",";

	ss << physics << ",";

	ss << position.x << ",";
	ss << position.y << ",";
	ss << position.w << ",";
	ss << position.h << ",";

	return ss.str();
}

void Tile::Deserialize(std::string data) {
	std::string temp;
	int length = data.length();
	char comma = ',';

	int index = data.find(comma);
	length -= index;

	spr_sheet_name = data.substr(0, index);
	temp = data.substr(index + 1, length);
	data = temp;

	index = data.find(comma);
	length -= index + 1;
	temp = data.substr(0, index);
	std::istringstream convert6(temp);
	if(!(convert6 >> frame.x)) 
		frame.x = 0;
	temp = data.substr(index + 1, length);
	data = temp;

	index = data.find(comma);
	length -= index + 1;
	temp = data.substr(0, index);
	std::istringstream convert7(temp);
	if(!(convert7 >> frame.y)) 
		frame.y = 0;
	temp = data.substr(index + 1, length);
	data = temp;

	index = data.find(comma);
	length -= index + 1;
	temp = data.substr(0, index);
	std::istringstream convert8(temp);
	if(!(convert8 >> frame.w)) 
		frame.w = 0;
	temp = data.substr(index + 1, length);
	data = temp;

	index = data.find(comma);
	length -= index + 1;
	temp = data.substr(0, index);
	std::istringstream convert9(temp);
	if(!(convert9 >> frame.h)) 
		frame.h = 0;
	temp = data.substr(index + 1, length);
	data = temp;

	index = data.find(comma);
	length -= index + 1;
	temp = data.substr(0, index);
	std::istringstream convert(temp);
	if(!(convert >> currentFrame)) 
		currentFrame = 0;
	temp = data.substr(index + 1, length);
	data = temp;

	index = data.find(comma);
	length -= index + 1;
	temp = data.substr(0, index);
	std::istringstream convert1(temp);
	if(!(convert1 >> physics)) 
		physics = 0;
	temp = data.substr(index + 1, length);
	data = temp;

	index = data.find(comma);
	length -= index + 1;
	temp = data.substr(0, index);
	std::istringstream convert2(temp);
	if(!(convert2 >> position.x)) 
		position.x = 0;
	temp = data.substr(index + 1, length);
	data = temp;

	index = data.find(comma);
	length -= index + 1;
	temp = data.substr(0, index);
	std::istringstream convert3(temp);
	if(!(convert3 >> position.y)) 
		position.y = 0;
	temp = data.substr(index + 1, length);
	data = temp;

	index = data.find(comma);
	length -= index + 1;
	temp = data.substr(0, index);
	std::istringstream convert4(temp);
	if(!(convert4 >> position.w)) 
		position.w = 0;
	temp = data.substr(index + 1, length);
	data = temp;

	index = data.find(comma);
	length -= index + 1;
	temp = data.substr(0, index);
	std::istringstream convert5(temp);
	if(!(convert5 >> position.h)) 
		position.h = 0;
	temp = data.substr(index + 1, length);
	data = temp;

}

void Tile::SetAbsolutePosition(int x, int y) {
	position.x = x;
	position.y = y;
}

void Tile::move(int x, int y) {
	position.x += x;
	position.y += y;
}
