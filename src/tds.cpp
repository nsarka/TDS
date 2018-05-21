/*
	** TDS v1.0 **
	Nick Sarkauskas and Drew Dimmick
	Copyright 2018
*/

#include <iostream>
#include <string>
#include <vector>

#include "windows.h"

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL_mixer.h"
#include "SDL2/SDL_net.h"

#include "../include/timer.h"
#include "../include/player.h"
#include "../include/physics.h"
#include "../include/spritesheet.h"
#include "../include/text.h"
#include "../include/tile.h"

const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 768;
const int FPS = 60;
const int TICKS_PER_FRAME = 1000 / FPS;

bool quit = false;

// SDL2 stuff
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

// TDS stuff
Spritesheet* sheet = NULL;
Text* textHandler = NULL;
std::vector<Entity*> gameEntities;

// FPS counter stuff
SDL_Texture* fps_texture;
int count = 0;

int init() {
    if( SDL_Init( SDL_INIT_VIDEO ) != 0 ) {
        std::cout << "SDL could not be initialized! SDL_Error: " << SDL_GetError() << std::endl;
        return 1;
    }

	window = SDL_CreateWindow(
		"Game",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		SCREEN_WIDTH,
		SCREEN_HEIGHT,
		SDL_WINDOW_SHOWN);

	if( window == NULL ) {
        std::cout << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
		return -1;
	}

    // Set up renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    // Set up spritesheet handler and load all spritesheets
    sheet = new Spritesheet(renderer);
    sheet->loadTexture(std::string("../assets/characters/1.png"), std::string("player"));
    sheet->loadTexture(std::string("../assets/environment/darkdimension.png"), std::string("ground"));

    sheet->printAllTexturesLoaded();

    // Set up text handler, load font
    textHandler = new Text(std::string("../assets/font/m5x7.ttf"));

	return 0;
}

void handleEvents() {
    SDL_Event event;

    while( SDL_PollEvent( &event ) != 0 ) {
        // User requests quit
        if( event.type == SDL_QUIT ) {
            quit = true;
        }

        if( event.type == SDL_MOUSEBUTTONDOWN ) {
            //If the left mouse button was released
            if( event.button.button == SDL_BUTTON_LEFT ) {
                SDL_Rect tile_rect = { event.button.x-64, event.button.y-64, 128, 128 };
                SDL_Rect source_txt_pos = { 32, 16, 16, 16 };

                Tile* t = new Tile("ground", tile_rect, 0);
                //t->AddFrame(source_txt_pos);
                t->frame = source_txt_pos;

                gameEntities.push_back(t);
            }
        }

        else if( event.type == SDL_KEYDOWN ) {

            // Select surfaces based on key press
            switch( event.key.keysym.sym ) {
                case SDLK_UP:
                std::cout << "Up key" << std::endl;
                break;

                case SDLK_DOWN:
                std::cout << "Down key" << std::endl;
                break;

                case SDLK_LEFT:
                std::cout << "Left key" << std::endl;
                break;

                case SDLK_RIGHT:
                std::cout << "Right key" << std::endl;
                break;

                case SDLK_ESCAPE:
                std::cout << "Escape key" << std::endl;
                break;

                default:
                std::cout << "Default key??" << std::endl;
                break;
            }
        }
    }
}

void update() {
    // Update frame count
    count++;
}

void render() {
    if( SDL_RenderClear(renderer) != 0 ) {
        std::cout << "Error: " << SDL_GetError() << std::endl;
    }

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);

    // Reset screen by drawing black onto it
    SDL_RenderClear(renderer);

    for (auto ent : gameEntities) {
        ent->Draw(renderer, sheet);
    }

	//SDL_RenderCopy(renderer, sheet->getTexture(std::string("player")), NULL, NULL);
    //SDL_RenderCopy(renderer, fps_texture, NULL, &textHandler->fps);

    // Draw renderer
    SDL_RenderPresent(renderer);
}

void cleanUp() {
    SDL_DestroyRenderer(renderer);
    renderer = NULL;

    SDL_DestroyWindow(window);
    window = NULL;

    // Free all textures
    sheet->~Spritesheet();

    SDL_Quit();
}

int main( int argc, char* args[] ) {
    if( init() != 0 ) {
        std::cerr << "Could not initialize SDL2" << std::endl;
        return -1;
    }

    Timer fps;

    fps.start();

	Uint32 frameStart;
    int frameTime;

    char buffer [8];
    float fr;

    while(!quit) {

        // Get the time in miliseconds game's been running
        frameStart = SDL_GetTicks();

        fr = count / (fps.getTicks() / 1000.f);

        snprintf(buffer, 8, "%2.2f", fr);
        fps_texture = textHandler->RenderText(renderer, std::string(buffer));

        handleEvents();
        update();
        render();

        // Calculating frame time
        frameTime = SDL_GetTicks() - frameStart;

        // Check to see if we need to delay
        if(TICKS_PER_FRAME > frameTime) {
            SDL_Delay(TICKS_PER_FRAME - frameTime);
        }
    }

    cleanUp();
    return 0;
}