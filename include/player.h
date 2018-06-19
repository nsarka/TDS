#pragma once

#include "entity.h"
#include "physics.h"
#include "sound.h"
#include <sstream>

extern class Sound* sound;
extern class std::vector<SDL_Rect*> collisionEntities;

// Zero indexed, so there's 4 frames 0-3
#define MAX_PLAYER_FRAMES 3

class Player: public Entity {
    public:
        Player(Spritesheet* sheet, std::string spr_path, int pclass, SDL_Rect pos);
		~Player();

        void Draw(SDL_Renderer* renderer, Spritesheet* sheet);
        void handleEvents(SDL_Event event);

        void SetMovingRight(bool val) { movingRight = val; };
        void SetMovingLeft(bool val) { movingLeft = val; };
        void SetMovingUp(bool val) { movingUp = val; };
        void SetMovingDown(bool val) { movingDown = val; };

        // bool GetMovingRight() { return movingRight; };
        // bool GetMovingLeft() { return movingLeft; };
        // bool GetMovingUp() { return movingUp; };
        // bool GetMovingDown() { return movingDown; };

        std::string Serialize() { return std::string(""); };
        void Deserialize(std::string data){};
        void Update();
        void drawHitBox(SDL_Renderer* renderer);
        bool collision(SDL_Rect pos);
        
        SDL_Rect position;

        SDL_Rect* hitbox;

        bool is_moving = false;

    private:

        // For when we get to it
        int player_class;

        std::string spr_sheet_name;

        bool movingRight = false;
        bool movingLeft = false;
        bool movingUp = false;
        bool movingDown = false;

        // Rectangles that correspond to each frame in that entity's animation cycle
        std::vector<SDL_Rect> animCycle;
        int currentFrame = 0;
        int count = 0;

        // Physics type
        int physics = 0;
};