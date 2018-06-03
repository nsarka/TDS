#include "../include/player.h"

Player::Player(Spritesheet* sheet, std::string spr_path, int pclass, SDL_Rect pos) {
	currentFrame = 0;
	spr_sheet_name = std::string("player");
	player_class = pclass;
	position = pos;
	sheet->loadTexture(spr_path, spr_sheet_name);

	for(int i = 0; i <= MAX_PLAYER_FRAMES; i++) {
		SDL_Rect frame = {i*19, 0, 19, 24};
		animCycle.push_back(frame);
	}
}

Player::~Player() {

}

void Player::Update() {

	if(movingRight) {
		position.x += 5;
	}

	if(movingLeft) {
		position.x -= 5;
	}

	if(movingUp) {
		position.y -= 5;
	}
	
	if(movingDown) {
		position.y += 5;
	}
}

void Player::Draw(SDL_Renderer* renderer, Spritesheet* sheet) {
	SDL_Rect camAdjusted = {
		position.x + cam->getOffsetX(),
		position.y + cam->getOffsetY(),
		position.w,
		position.h
	};

    SDL_RenderCopy(renderer, sheet->getTexture(spr_sheet_name), &animCycle.at(currentFrame), &camAdjusted);

	extern int count;

	if(count % animSpeed == 0) {
		if(is_moving) {
			if(currentFrame < MAX_PLAYER_FRAMES) {
				currentFrame++;
			} else {
				currentFrame = 0;
			}
		} else {
			// Not correct for all player spritesheets, but usually the first frame is the one where the character isnt in the middle of a run animation
			if(currentFrame != 0) {
				currentFrame = 0;
			}
		}
	}
}

void Player::handleEvents(SDL_Event event) {

	if( event.type == SDL_KEYDOWN ) {

		if(event.key.keysym.sym == SDLK_w) {
			SetMovingUp(true);
			is_moving = true;
		}

		if(event.key.keysym.sym == SDLK_d) {
			SetMovingRight(true);
			is_moving = true;
		}

		if(event.key.keysym.sym == SDLK_s) {
			SetMovingDown(true);
			is_moving = true;
		}

		if(event.key.keysym.sym == SDLK_a) {
			SetMovingLeft(true);
			is_moving = true;
		}

		if(event.key.keysym.sym == SDLK_e) {
			sound->playSound(std::string("energyshield"));
		}
	}
	else if( event.type == SDL_KEYUP ) {

		if(event.key.keysym.sym == SDLK_w) {
			SetMovingUp(false);
			is_moving = false;
		}

		if(event.key.keysym.sym == SDLK_d) {
			SetMovingRight(false);
			is_moving = false;
		}

		if(event.key.keysym.sym == SDLK_s) {
			SetMovingDown(false);
			is_moving = false;
		}

		if(event.key.keysym.sym == SDLK_a) {
			SetMovingLeft(false);
			is_moving = false;
		}

		switch( event.key.keysym.sym ) {
			case SDLK_ESCAPE:
			break;

			default:
			//std::cout << "Default key??" << std::endl;
			break;
		}
	}
}