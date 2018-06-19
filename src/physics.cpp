#include "../include/physics.h"

bool Physics::checkCollision(SDL_Rect* rect1, SDL_Rect* rect2) {
	SDL_Rect res;
	return SDL_IntersectRect(rect1, rect2, &res);
}

bool Physics::checkMouseCollision(SDL_Rect ent, SDL_Point point) {
	if(point.x >= ent.x && point.x <= (ent.x + ent.w)) {
		if(point.y >= ent.y && point.y <= (ent.y + ent.h)) {
			return true;
		}
	}
	return false;
}

void Physics::setCollisionRect(SDL_Point point1, SDL_Point point2) {
	SDL_Rect* collisionRect;
	collisionRect = new SDL_Rect();
	collisionRect->x = point1.x;
	collisionRect->y = point1.y;
	collisionRect->w = point2.x - point1.x;
	collisionRect->h = point2.y - point1.y;

	collisionEntities.push_back(collisionRect);
}

std::string Physics::serializeColliders(SDL_Rect* rect) {
	std::stringstream ss;

	ss << rect->x << ",";
	ss << rect->y << ",";
	ss << rect->w << ",";
	ss << rect->h << ",";

	return ss.str();
}

void Physics::deserializeColliders(std::string lineData, SDL_Rect* col) {
	std::stringstream ss;
	ss << lineData;
	std::queue<std::string> readData;

	while(ss.good()) {
		std::string substr;
		getline(ss, substr, ',');
		readData.push(substr);
	}

	col->x 			= atoi(readData.front().c_str());
	readData.pop();

	col->y 			= atoi(readData.front().c_str());
	readData.pop();

	col->w 			= atoi(readData.front().c_str());
	readData.pop();

	col->h 			= atoi(readData.front().c_str());
	readData.pop();
}