#include "../include/tile.h"

Tile::Tile(std::string spr_name, SDL_Rect pos, int phys) {
	spr_sheet_name = spr_name;
	position = pos;
	physics = phys;
	currentFrame = 0;
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

    SDL_RenderCopy(renderer, sheet->getTexture(spr_sheet_name), &animCycle.at(currentFrame), &camAdjusted);

	extern int count;

	if(count % animSpeed == 0) {
		if(currentFrame < animCycle.size()) {
			//currentFrame++;
		} else {
			currentFrame = 0;
		}
	}
}

std::string Tile::Serialize() {
	std::stringstream ss;

	ss << position.x << ",";
	ss << position.y << ",";
	ss << position.w << ",";
	ss << position.h << ",";
	ss << physics << ",";
	ss << spr_sheet_name << ",";
	ss << currentFrame << ",";
	ss << animSpeed << ",";

	ss << "|,";		// Using | to denote that the next field has variable # data values

	for(SDL_Rect rect : animCycle) {
		ss << rect.x << ",";
		ss << rect.y << ",";
		ss << rect.w << ",";
		ss << rect.h << ",";
	}

	//ss << "|,";

	return ss.str();
}

void Tile::Deserialize(std::string lineData) {
	std::stringstream ss;
	ss << lineData;
	std::queue<std::string> readData;

	while(ss.good()) {
		std::string substr;
		getline(ss, substr, ',');
		readData.push(substr);
	}

	position.x 			= atoi(readData.front().c_str());
	readData.pop();

	position.y 			= atoi(readData.front().c_str());
	readData.pop();

	position.w 			= atoi(readData.front().c_str());
	readData.pop();

	position.h 			= atoi(readData.front().c_str());
	readData.pop();

	physics 			= atoi(readData.front().c_str());
	readData.pop();

	spr_sheet_name 		= readData.front();
	readData.pop();

	currentFrame 		= atoi(readData.front().c_str());
	readData.pop();

	animSpeed 			= atoi(readData.front().c_str());
	readData.pop();

	// "|"
	readData.pop();

	while(!readData.empty()) {
		SDL_Rect readAnimFrame;

		readAnimFrame.x 	= atoi(readData.front().c_str());
		readAnimFrame.y 	= atoi(readData.front().c_str());
		readAnimFrame.w 	= atoi(readData.front().c_str());
		readAnimFrame.h 	= atoi(readData.front().c_str());

		animCycle.push_back(readAnimFrame);
	}
}

void Tile::SetAbsolutePosition(int x, int y) {
	position.x = x;
	position.y = y;
}

void Tile::move(int x, int y) {
	position.x += x;
	position.y += y;
}
