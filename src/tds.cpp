/*
	** TDS v1.0 **
	Nick Sarkauskas and Drew Dimmick
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
Player* plyr = NULL;

Tile* theCrystal = NULL;
bool theCrystalDirectionRight = true;

Camera* cam = NULL;

std::string levelname;

// Mouse position variables
int mouseX, mouseY;
SDL_Point cursor;

// FPS counter stuff
SDL_Texture* fps_texture;
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

    // Set up cursor
    cursor = { mouseX, mouseY };

    // Set up spritesheet handler and load all spritesheets
    sheet = new Spritesheet(renderer);
    sheet->loadTexture(std::string("../assets/environment/darkdimension.png"), std::string("environment"));

    SDL_Rect p_pos = {1024/2, 768/2, 128, 128};

    // Set up player
    plyr = new Player(sheet, std::string("../assets/characters/2_south2.png"), 0, p_pos);

    // Set up text handler, load font
    textHandler = new Text(std::string("../assets/font/m5x7.ttf"));

    // Set up basic world (TODO: read from file)
    for(int x = 0; x < 1600/128; x++) {
        for(int y = 0; y < 1200/128; y++) {
            SDL_Rect tile_rect = { x*128, y*128, 128, 128 };
            SDL_Rect source_txt_pos = { 32, 16, 16, 16 };

            Tile* t = new Tile("environment", tile_rect, 0);
            //t->AddFrame(source_txt_pos);
            t->frame = source_txt_pos;

            gameEntities.push_back(t);
        }
    }

    // Set up theCrystal
    SDL_Rect tile_rect = { 600, 400, 128, 128 };
    SDL_Rect source_txt_pos = { 400, 25, 16, 36 };

    theCrystal = new Tile("environment", tile_rect, 0);
    //t->AddFrame(source_txt_pos);
    theCrystal->frame = source_txt_pos;

    gameEntities.push_back(theCrystal);

    sheet->printAllTexturesLoaded();

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
                SDL_Rect tile_rect = { (event.button.x-64) - cam->getOffsetX(), (event.button.y-64) - cam->getOffsetY(), 128, 128 };
                SDL_Rect source_txt_pos = { 112, 35, 31, 27 };

                Tile* t = new Tile("environment", tile_rect, 0);
                //t->AddFrame(source_txt_pos);
                t->frame = source_txt_pos;

                gameEntities.push_back(t);
            } else {
                SDL_Rect tile_rect = { (event.button.x-64) - cam->getOffsetX(), (event.button.y-64) - cam->getOffsetY(), 128, 128 };
                SDL_Rect source_txt_pos = { 112, 67, 31, 26 };

                Tile* t = new Tile("environment", tile_rect, 0);
                //t->AddFrame(source_txt_pos);
                t->frame = source_txt_pos;

                gameEntities.push_back(t);
            }
        }

        else if( event.type == SDL_KEYDOWN ) {

            // Select surfaces based on key press
            switch( event.key.keysym.sym ) {
                case SDLK_UP:
                plyr->is_moving = true;
                plyr->Move(0,-5);
                break;

                case SDLK_DOWN:
                plyr->is_moving = true;
                plyr->Move(0,5);
                break;

                case SDLK_LEFT:
                plyr->is_moving = true;
                plyr->Move(-5,0);
                break;

                case SDLK_RIGHT:
                plyr->is_moving = true;
                plyr->Move(5,0);
                break;

                case SDLK_ESCAPE:
                break;

                case SDLK_z:
                cam->absoluteMoveCameraX(512 - 48 - (theCrystal->position.x));
                cam->absoluteMoveCameraY(384 - 72 - (theCrystal->position.y));
                break;

                case SDLK_SPACE:
                if(Physics::checkMouseCollision(theCrystal->position, cursor)) {
                    std::cout << "true" << std::endl;
                }
                else {
                    std::cout << "false" << std::endl;
                }
                break;

                case SDLK_F1:
                drawFPS = !drawFPS;
                std::cout << "Toggled FPS Draw" << std::endl;
                break;

                case SDLK_F3:
                std::cout << "Enter name for level: ";
                std::cin >> levelname;
                std::cout << "Saving level '" << levelname << "' ..." << std::endl;
                Level::saveLevel(levelname, gameEntities);
                break;

                case SDLK_F4:
                std::cout << "Enter Level Name: ";
                std::cin >> levelname;
                Level::loadLevel(levelname, &gameEntities);
                break;

                default:
                //std::cout << "Default key??" << std::endl;
                break;
            }
        }
        else if( event.type == SDL_KEYUP ) {

            // Select surfaces based on key press
            switch( event.key.keysym.sym ) {
                case SDLK_UP:
                plyr->is_moving = false;
                break;

                case SDLK_DOWN:
                plyr->is_moving = false;
                break;

                case SDLK_LEFT:
                plyr->is_moving = false;
                break;

                case SDLK_RIGHT:
                plyr->is_moving = false;
                break;

                default:
                //std::cout << "Default key??" << std::endl;
                break;
            }
        }
    }
}

void update() {
    // Update frame count
    count++;

    cam->absoluteMoveCameraX(512 - 64 - (plyr->position.x));
    cam->absoluteMoveCameraY(384 - 64 - (plyr->position.y));

    // Update mouse position variables
    SDL_GetMouseState(&mouseX, &mouseY);

    // Update the offset of camera to cursor
    mouseX -= cam->getOffsetX();
    mouseY -= cam->getOffsetY();

    // Update cursor
    cursor = { mouseX, mouseY };

    if(theCrystalDirectionRight) {
        if(theCrystal->position.x >= 800) {
            theCrystalDirectionRight = false;
        }

        theCrystal->move(1,0);
    } else {
        if(theCrystal->position.x <= 200) {
            theCrystalDirectionRight = true;
        }

        theCrystal->move(-1,0);
    }
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
        SDL_RenderCopy(renderer, fps_texture, NULL, &textHandler->fps);
    }

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