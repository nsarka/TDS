/*
	** TDS v1.0 **
	Nick Sarkauskas, Drew Dimmick, and Mack Blaurock
	Copyright 2018
*/

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

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
#include "../include/camera.h"
#include "../include/level.h"
#include "../include/editor.h"
#include "../include/menu.h"

const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 768;
const int FPS = 60;
const int TICKS_PER_FRAME = 1000 / FPS;

bool quit = false;
bool inMainMenu = true;

// SDL2 stuff
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

// TDS stuff
Spritesheet* sheet = NULL;
Text* textHandler = NULL;
std::vector<Entity*> gameEntities;
Player* plyr = NULL;
Editor* editor = NULL;
Camera* cam = NULL;
Menu* mainMenu = NULL;

int xMouse = 0, yMouse = 0;

// FPS counter stuff
char buffer [128];
int count = 0;
bool drawFPS = true;

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

    // Set up camera
    cam = new Camera();

    // Set up editor
    editor = new Editor();
        
    // Load all the sprites
    editor->loadSprites();

    // Load Level '01'
    Level::loadLevel("01", &gameEntities);

    // Set up spritesheet handler and load all spritesheets
    sheet = new Spritesheet(renderer);
    sheet->loadTexture(std::string("../assets/environment/darkdimension.png"), std::string("environment"));
    sheet->loadTexture(std::string("../assets/menu/background.png"), std::string("mainmenu_background"));
    sheet->loadTexture(std::string("../assets/menu/button.png"), std::string("button"));
    sheet->loadTexture(std::string("../assets/menu/button_hover.png"), std::string("button_hover"));
    sheet->loadTexture(std::string("../assets/menu/button_click.png"), std::string("button_click"));

    SDL_Rect p_pos = {1024/2, 768/2, 128, 128};

    // Set up player
    plyr = new Player(sheet, std::string("../assets/characters/2_south2.png"), 0, p_pos);

    // Set up text handler, load font
    textHandler = new Text(std::string("../assets/font/m5x7.ttf"));

    sheet->printAllTexturesLoaded();

    // Set up main menu
    mainMenu = new Menu();

    MenuItem start;

	start.hoverSound            = std::string("button_hover");
    start.clickSound            = std::string("button_click");

	SDL_Rect pos = {512, 384, 200, 100};
    start.pos = pos;

    start.Click = buttonFuncs::start_singleplayer;

    mainMenu->background_texture = std::string("mainmenu_background");
    mainMenu->AddItem(start);

	return 0;
}

void handleEvents() {
    SDL_Event event;
    std::string levelname = "";

    while( SDL_PollEvent( &event ) != 0 ) {
        // User requests quit
        if( event.type == SDL_QUIT ) {
            quit = true;
        } else if( event.type == SDL_MOUSEMOTION ) {
            xMouse = event.motion.x;
            yMouse = event.motion.y;
        } else if( event.type == SDL_KEYDOWN ) {

            // Out of the switch to prevent some blockiness when rapidly switching keys
            if(event.key.keysym.sym == SDLK_w) {
                plyr->SetMovingUp(true);
                plyr->is_moving = true;
            }

            if(event.key.keysym.sym == SDLK_d) {
                plyr->SetMovingRight(true);
                plyr->is_moving = true;
            }

            if(event.key.keysym.sym == SDLK_s) {
                plyr->SetMovingDown(true);
                plyr->is_moving = true;
            }

            if(event.key.keysym.sym == SDLK_a) {
                plyr->SetMovingLeft(true);
                plyr->is_moving = true;
            }


            switch( event.key.keysym.sym ) {
                case SDLK_ESCAPE:
                break;

                case SDLK_F1:
                drawFPS = !drawFPS;
                std::cout << "FPS Draw: " << ( drawFPS ? "On" : "Off" ) << std::endl;
                break;

                case SDLK_F3:
                std::cout << "Enter name for level: ";
                std::cin >> levelname;
                std::cout << "Saving level '" << levelname << "' ..." << std::endl;
                Level::saveLevel(levelname, gameEntities);
                levelname = "";
                break;

                case SDLK_F4:
                std::cout << "Enter Level Name: ";
                std::cin >> levelname;
                Level::loadLevel(levelname, &gameEntities);
                levelname = "";
                break;

                default:
                //std::cout << "Default key??" << std::endl;
                break;
            }
        }
        else if( event.type == SDL_KEYUP ) {

            if(event.key.keysym.sym == SDLK_w) {
                plyr->SetMovingUp(false);
                plyr->is_moving = false;
            }

            if(event.key.keysym.sym == SDLK_d) {
                plyr->SetMovingRight(false);
                plyr->is_moving = false;
            }

            if(event.key.keysym.sym == SDLK_s) {
                plyr->SetMovingDown(false);
                plyr->is_moving = false;
            }

            if(event.key.keysym.sym == SDLK_a) {
                plyr->SetMovingLeft(false);
                plyr->is_moving = false;
            }

            switch( event.key.keysym.sym ) {
                case SDLK_ESCAPE:
                inMainMenu = true;
                break;

                default:
                //std::cout << "Default key??" << std::endl;
                break;
            }
        }

        editor->handleEvents(event);
    }
}

void update() {
    // Update frame count
    count++;

    plyr->Update();

    cam->absoluteMoveCameraX(512 - 64 - (plyr->position.x));
    cam->absoluteMoveCameraY(384 - 64 - (plyr->position.y));
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

    plyr->Draw(renderer, sheet);

    if(drawFPS) {
        editor->drawGrid(renderer);
        textHandler->DrawTextToScreen(renderer, std::string(buffer));
        editor->drawSelected(renderer, xMouse, yMouse);
    }

    // Draw to screen
    SDL_RenderPresent(renderer);
}

void cleanUp() {
    SDL_DestroyRenderer(renderer);
    renderer = NULL;

    SDL_DestroyWindow(window);
    window = NULL;

    // Free all textures
    sheet->~Spritesheet();

    // Free game font
    textHandler->~Text();

    SDL_Quit();
}

int main( int argc, char* args[] ) {
    if( init() != 0 ) {
        std::cerr << "Could not initialize SDL2" << std::endl;
        return -1;
    }

    Timer fps;
    fps.start();

mainmenu_label:
    while(inMainMenu) {
        mainMenu->HandleEvents();
        mainMenu->Draw(renderer);

        // Wait till 60 fps
        fps.waitFPS(TICKS_PER_FRAME);
    }

    while(!quit && !inMainMenu) {

        // Update game debug text
        if(drawFPS) {
            snprintf(buffer, 128, "FPS: %2.2f X: %i Y: %i Ents: %i", fps.fr, plyr->position.x, plyr->position.y, gameEntities.size());
        }

        handleEvents();
        update();
        render();

        // Wait till 60 fps
        fps.waitFPS(TICKS_PER_FRAME);
    }

    if(inMainMenu) {
        goto mainmenu_label;
    }

    cleanUp();
    return 0;
}