/*
	** TDS v1.0 **
	Nick Sarkauskas, Drew Dimmick, and Mack Blaurock
	Copyright 2018
*/

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

//#include "windows.h"

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
#include "../include/sound.h"

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
std::vector<SDL_Rect*> collisionEntities;
Player* plyr = NULL;
Editor* editor = NULL;
Camera* cam = NULL;
Menu* mainMenu = NULL;
Sound* sound = NULL;

int xMouse = 0, yMouse = 0;

// FPS counter stuff
char buffer [128];
int count = 0;
bool drawFPS = true;
bool drawCol = false;

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

    // Set up sound handler
    sound = new Sound();

    sound->loadMusic(std::string("../assets/d2sounds/music/jungle.wav"), std::string("jungle"));
    sound->loadSound(std::string("../assets/d2sounds/skill/sorceress/energyshield.wav"), std::string("energyshield"));
    sound->loadSound(std::string("../assets/d2sounds/skill/amazon/handofathena.wav"), std::string("handofathena"));

    sound->printAllSoundsLoaded();
    sound->printAllMusicLoaded();

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

    // Menu items
    MenuItem start;
	start.hoverSound            = std::string("button_hover");
    start.clickSound            = std::string("button_click");
    start.pos = {412, 384, 200, 100};
    start.Click = buttonFuncs::start_singleplayer;

    MenuItem quit;
	quit.hoverSound            = std::string("button_hover");
    quit.clickSound            = std::string("button_click");
    quit.pos = {412, 584, 200, 100};
    quit.Click = buttonFuncs::quit_game;

    mainMenu->background_texture = std::string("mainmenu_background");
    mainMenu->AddItem(start);
    mainMenu->AddItem(quit);

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

            switch( event.key.keysym.sym ) {
                case SDLK_ESCAPE:
                inMainMenu = true;
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
                Level::saveLevelColliders(levelname, collisionEntities);
                levelname = "";
                break;

                case SDLK_F4:
                std::cout << "Enter Level Name: ";
                std::cin >> levelname;
                Level::loadLevel(levelname, &gameEntities);
                Level::loadLevelColliders(levelname, &collisionEntities);
                levelname = "";
                break;

                default:
                //std::cout << "Default key??" << std::endl;
                break;
            }
        }

        plyr->handleEvents(event);
        editor->handleEvents(event);
    }
}

void update() {
    // Update frame count
    count++;

    plyr->Update();

    cam->absoluteMoveCameraX(512 - 64 - (plyr->position.x));
    cam->absoluteMoveCameraY(384 - 64 - (plyr->position.y));

    if(!sound->isMusicPlaying()) {
        sound->playMusic(std::string("jungle"));
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
        editor->drawGrid(renderer);
        textHandler->DrawTextToScreen(renderer, std::string(buffer), textHandler->fps);
        editor->drawSelected(renderer, xMouse, yMouse);
    }

    if(drawCol) {
        editor->drawColliders(renderer);
        plyr->drawHitBox(renderer);
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

    // Free all sounds
    sound->~Sound();

	// quit SDL_mixer
	Mix_CloseAudio();

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
    while(inMainMenu && !quit) {
        count++;
        mainMenu->HandleEvents();
        mainMenu->Draw(renderer);

        // Wait till 60 fps
        fps.waitFPS(TICKS_PER_FRAME);
    }

    while(!quit) {

        // Update game debug text
        if(drawFPS) {
            snprintf(buffer, 128, "FPS: %2.2f X: %i Y: %i Ents: %i", fps.fr, plyr->position.x, plyr->position.y, gameEntities.size());
        }

        handleEvents();
        update();
        render();

        // Wait till 60 fps
        fps.waitFPS(TICKS_PER_FRAME);

        if(inMainMenu) {
            goto mainmenu_label;
        }
    }

    cleanUp();

    return 0;
}
