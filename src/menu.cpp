#include "../include/menu.h"

void buttonFuncs::start_singleplayer() {
	inMainMenu = false;
}

void buttonFuncs::start_multiplayer() {

}

void buttonFuncs::options() {

}

void buttonFuncs::exit() {

}

// MenuItem
MenuItem::MenuItem() {

}

MenuItem::~MenuItem() {

}

// Menu
Menu::Menu() {

}

Menu::~Menu() {

}

void Menu::Draw(SDL_Renderer* renderer) {

    if( SDL_RenderClear(renderer) != 0 ) {
        std::cout << "Error: " << SDL_GetError() << std::endl;
    }

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);

    // Reset screen by drawing black onto it
    SDL_RenderClear(renderer);

	SDL_RenderCopy(renderer, sheet->getTexture(background_texture), NULL, NULL);

	for(MenuItem item : menuItems) {
		SDL_RenderCopy(renderer, sheet->getTexture(item.getTextureString()), NULL, &item.pos);
	}

    // Draw to screen
    SDL_RenderPresent(renderer);
}

void Menu::HandleEvents() {
    SDL_Event event;

    while( SDL_PollEvent( &event ) != 0 ) {

		if( event.type == SDL_MOUSEBUTTONDOWN ) {
			//If the left mouse button was released
			if( event.button.button == SDL_BUTTON_LEFT ) {

				int xPos = event.button.x;
				int yPos = event.button.y;

				SDL_Point p = {xPos, yPos};

				for(MenuItem item : menuItems) {
					if(Physics::checkMouseCollision(item.pos, p)) {
						item.Click();
					}
				}

			} else {

			}
		} else if( event.type == SDL_KEYDOWN ) {
            switch( event.key.keysym.sym ) {
				case SDLK_ESCAPE:
				inMainMenu = false;
				break;
				
                default:
                break;
            }
        } else if( event.type == SDL_KEYUP ) {
            switch( event.key.keysym.sym ) {
                default:
                break;
            }
        }
    }
}

void Menu::AddItem(MenuItem item) {
	menuItems.push_back(item);
}