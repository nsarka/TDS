#include "../include/physics.h"

bool Physics::checkCollision(SDL_Rect ent1, SDL_Rect ent2) {
	if(ent1.x >= ent2.x && ent1.x <= (ent2.x + ent2.w)) {
		if(ent1.y >= ent2.y && ent1.y <= (ent2.y + ent2.h)) {
			return true;
		}
	}
	return false;
}

bool Physics::checkMouseCollision(SDL_Rect ent, SDL_Point point) {
	if(point.x >= ent.x && point.x <= (ent.x + ent.w)) {
		if(point.y >= ent.y && point.y <= (ent.y + ent.h)) {
			return true;
		}
	}
	return false;
}