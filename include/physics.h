#include "SDL2/SDL.h"

class Physics {
    public:
		bool checkCollision(SDL_Rect ent1, SDL_Rect ent2);

	// Physics meant to be a static class. No constructing!
    private:
        Physics() {};
};