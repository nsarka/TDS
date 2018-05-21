#pragma once

#include <vector>

#include "SDL2/SDL.h"

#include "spritesheet.h"
#include "camera.h"

extern class Camera* cam; // we have one in global scope, so let everything that inherits Entity stuff use that one

// Abstract base class
class Entity {

	protected:

	std::string spr_sheet_name;

	// Rectangles that correspond to each frame in that entity's animation cycle
	std::vector<SDL_Rect> animCycle;

	// Game destination rect
	SDL_Rect position;

	// Physics type
	int physics;

	public:

	virtual void Draw(SDL_Renderer* renderer, Spritesheet* sheet) =0;
	void AddFrame(SDL_Rect frame) { animCycle.push_back(frame); }
};