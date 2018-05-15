#include "SDL2/SDL.h"

// Abstract base class
class Entity {

	protected:

	Spritesheet* spr_sheet;

	// Spritesheet source rect
	SDL_Rect source;

	// Game destination rect
	SDL_Rect dest;

	// Physics type
	int physics;

	public:

	void LoadSpriteSheet(int a, int b) {
		width=a; height=b;
	}

	virtual int Draw() =0;
};