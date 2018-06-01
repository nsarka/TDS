#pragma once

#include <vector>
#include <string>
#include <iostream>

#include "SDL2/SDL.h"

#include "spritesheet.h"
#include "physics.h"

extern Spritesheet* sheet;

extern bool inMainMenu;
extern bool quit;

enum buttonState {
	NORMAL = 0,
	HOVER,
	CLICK
};

namespace buttonFuncs {
	void start_singleplayer();
	void start_multiplayer();
	void options();
	void quit_game();
}

class MenuItem {

	public:

	MenuItem();
	~MenuItem();

	void (*Click)();

	int state = NORMAL;

	// Menu sounds
	std::string hoverSound;
	std::string clickSound;

	// Menu position
	SDL_Rect pos;

	std::string getTextureString() {
		std::string text;
		switch(state) {
			case NORMAL:
				text = "button";
				break;
			case HOVER:
				text = "button_hover";
				break;
			case CLICK:
				text = "button_click";
				break;
		}

		return text;
	}
};

class Menu {

	public:

	Menu();
	~Menu();

	// Splash background
	std::string background_texture;

	/* Where on the screen this menu should be drawn.
	   In the future menus will be able to be used in game.
	   NULL for the entire screen */
	SDL_Rect* location = NULL;

	// All menu items--Draw() draws in order
	std::vector<MenuItem> menuItems;

	void Draw(SDL_Renderer* renderer);
	void HandleEvents();
	void AddItem(MenuItem item);
};