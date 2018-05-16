/*
	** TDS v1.0 **
	Nick Sarkauskas and Drew Dimmick
	Copyright 2018
*/

#include <iostream>

#include "windows.h"

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL_mixer.h"
#include "SDL2/SDL_net.h"

#include "../include/timer.h"

using namespace std;

const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 768;
const int FPS = 60;
const int TICKS_PER_FRAME = 1000 / FPS;

bool quit = false;

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

SDL_Rect player = {0, 0, 10, 10};

int init() {
    if( SDL_Init( SDL_INIT_VIDEO ) != 0 ) {
        cout << "SDL could not be initialized! SDL_Error: " << SDL_GetError() << endl;
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
        cout << "Window could not be created! SDL_Error: " << SDL_GetError() << endl;
		return -1;
	}

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

	return 0;
}

void handleEvents() {
    SDL_Event event;

    while( SDL_PollEvent( &event ) != 0 ) {
        // User requests quit
        if( event.type == SDL_QUIT ) {
            quit = true;
        }

        if( event.type == SDL_MOUSEMOTION ) {
            player.x = event.motion.x;
            player.y = event.motion.y;
        }

        else if( event.type == SDL_KEYDOWN ) {

            // Select surfaces based on key press
            switch( event.key.keysym.sym ) {
                case SDLK_UP:
                cout << "Up key" << endl;
                break;

                case SDLK_DOWN:
                cout << "Down key" << endl;
                break;

                case SDLK_LEFT:
                cout << "Left key" << endl;
                break;

                case SDLK_RIGHT:
                cout << "Right key" << endl;
                break;

                case SDLK_ESCAPE:
                cout << "Escape key" << endl;
                break;

                default:
                cout << "Default key??" << endl;
                break;
            }
        }
    }
}

void update() {

}

void render() {
    if( SDL_RenderClear(renderer) != 0 ) {
        cout << "Error: " << SDL_GetError() << endl;
    }

    // Reset screen by drawing black onto it
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Set new draw color to red and draw player rect
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &player);

    // Draw renderer
    SDL_RenderPresent(renderer);
}

void cleanUp() {
    SDL_DestroyRenderer(renderer);
    renderer = NULL;

    SDL_DestroyWindow(window);
    window = NULL;

    SDL_Quit();
}

int main( int argc, char* args[] ) {
    if( init() != 0 ) {
        cerr << "Could not initialize SDL2" << endl;
        return -1;
    }

	unsigned int frameStart;
    int frameTime;

    // While application is running
    while(!quit) {

        // Get the time in miliseconds game's been running
        frameStart = SDL_GetTicks();

        handleEvents();
        update();
        render();

        // Calculating frame time
        frameTime = SDL_GetTicks() - frameStart;

        // Check to see if we need to delay
        if(TICKS_PER_FRAME > frameTime) {
            SDL_Delay(TICKS_PER_FRAME - frameTime);
        }

        cout << frameStart << endl;

    }

    cleanUp();
    return 0;
}