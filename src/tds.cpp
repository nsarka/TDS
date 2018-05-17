/*
	** TDS v1.0 **
	Nick Sarkauskas and Drew Dimmick
	Copyright 2018
*/

#include <iostream>
#include <string>

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

using namespace std;

const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 768;
const int FPS = 60;
const int TICKS_PER_FRAME = 1000 / FPS;

bool quit = false;

int count = 0;

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

SDL_Rect player = {0, 0, 10, 10};
const SDL_Rect fps = {0, 0, 50, 25};

Spritesheet* sheet = NULL;
Text* textHandler = NULL;

SDL_Texture* sample;

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
    count++;
    cout << count << endl;
}

void render() {
    if( SDL_RenderClear(renderer) != 0 ) {
        cout << "Error: " << SDL_GetError() << endl;
    }

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);

    // Reset screen by drawing black onto it
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);

    SDL_RenderDrawRect(renderer, &player);

	SDL_RenderCopy(renderer, sheet->getTexture(), NULL, NULL);
    SDL_RenderCopy(renderer, sample, NULL, &fps);

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

    sheet = new Spritesheet(renderer, std::string("../assets/characters/1.png"));
    textHandler = new Text(std::string("../assets/font/m5x7.ttf"));

    Timer fps;

    fps.start();

	Uint32 frameStart;
    int frameTime;

    char buffer [8];
    float fr;

    // While application is running
    while(!quit) {

        // Get the time in miliseconds game's been running
        frameStart = SDL_GetTicks();

        fr = count / (fps.getTicks() / 1000.f);

        snprintf(buffer, 8, "%2.2f", fr);
        sample = textHandler->RenderText(renderer, std::string(buffer));

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