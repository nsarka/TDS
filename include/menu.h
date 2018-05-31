#pragma once

#include <vector>
#include <string>

#include "SDL2/SDL.h"

#include "spritesheet.h"

class MenuItem {

	public:

	MenuItem();
	~MenuItem();

	// Menu images
	std::string source_texture;
	std::string source_texture_hover;
	std::string source_texture_click;

	// Menu sounds
	std::string hoverSound;
	std::string clickSound;

	// Menu position
	SDL_Rect dest;
};

class MainMenu {

	public:

	MainMenu();
	~MainMenu();

	// Splash background
	std::string background_texture;

	// All menu items--Draw() draws in order
	std::vector<MenuItem> menuItems;

	void Draw(SDL_Renderer* renderer);
	void Click(SDL_Point point);
};