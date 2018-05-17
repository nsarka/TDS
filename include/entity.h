#pragma once

#include "SDL2/SDL.h"

#include "spritesheet.h"


// Abstract base class
class Entity {

	protected:

	SDL_Texture* spr_sheet;

	// Spritesheet source rect
	SDL_Rect source;

	// Game destination rect
	SDL_Rect dest;

	// Physics type
	int physics;

	public:

	virtual int Draw() =0;
};