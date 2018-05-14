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
        //User requests quit
        if( event.type == SDL_QUIT ) {
            quit = true;
        }

        if( event.type == SDL_MOUSEMOTION ) {
            player.x = event.motion.x;
            player.y = event.motion.y;
        }

        else if( event.type == SDL_KEYDOWN ) {

            //Select surfaces based on key press
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

<<<<<<< HEAD
void Loop(){

    while(!quit) {
		//Timer tmer;
		// int start_time = tmer.start();
        //Events:
        Events();


		if (SDL_RenderClear(renderer)!=0) {
            cout<<"Fehler: "<<SDL_GetError()<<endl;
        }

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
=======
void update() {
>>>>>>> feb1142563c5cc3f0e709811ab2825ddfe4a661a

}

void render() {
    if( SDL_RenderClear(renderer) != 0 ) {
        cout << "Error: " << SDL_GetError() << endl;
    }

    // Reset screen by drawing black onto it
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

<<<<<<< HEAD
		// int end_time = tmer.end()
		// int difference = end - start
		// if(difference < 60 fps) then sleep 60 - difference

    }
=======
    // Set new draw color to red and draw player rect
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &player);
>>>>>>> feb1142563c5cc3f0e709811ab2825ddfe4a661a

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

    while(!quit) {
        handleEvents();
        update();
        render();

        // Framerate limit

    }

    cleanUp();
    return 0;
}