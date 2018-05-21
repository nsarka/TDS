#pragma once

#include <iostream>

#include "spritesheet.h"
#include "entity.h"

class Camera {
    public:
        Camera() {};
		~Camera() {};

        int getOffsetX() { return camera_view.x; }
		int getOffsetY() { return camera_view.y; }

		void moveCameraX(int amount) { camera_view.x += amount; }
		void moveCameraY(int amount) { camera_view.y += amount; }

		void absoluteMoveCameraX(int amount) { camera_view.x = amount; }
		void absoluteMoveCameraY(int amount) { camera_view.y = amount; }
		
		bool isInWindow(SDL_Rect r) { return true; }

    private:
		SDL_Rect camera_view = {0, 0, 0, 0}; // change w and h to window w and h
};