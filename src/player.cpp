#include "../include/player.h"

Player::Player(Spritesheet* sheet, std::string spr_path, int pclass, SDL_Rect pos) {
	currentFrame = 0;
	spr_sheet_name = std::string("player");
	player_class = pclass;
	position = pos;
	hitbox = new SDL_Rect();
	hitbox->x = position.x + 32;
	hitbox->y = position.y + 85; 
	hitbox->w = 72;
	hitbox->h = 40;

	sheet->loadTexture(spr_path, spr_sheet_name);

	for(int i = 0; i <= MAX_PLAYER_FRAMES; i++) {
		SDL_Rect frame = {i*19, 0, 19, 24};
		animCycle.push_back(frame);
	}
}

Player::~Player() {

}

void Player::Update() {

	SDL_Rect testPos = *hitbox;

	testPos.x += 5;

	if(movingRight && !collision(testPos)) {
		position.x += 5;
		hitbox->x += 5;
	}

	testPos.x -= 10;

	if(movingLeft && !collision(testPos)) {
		position.x -= 5;
		hitbox->x -= 5;
	}

	testPos.x += 5;
	testPos.y -= 5;

	if(movingUp && !collision(testPos)) {
		position.y -= 5;
		hitbox->y -= 5;
	}

	testPos.y += 10;
	
	if(movingDown && !collision(testPos)) {
		position.y += 5;
		hitbox->y += 5;
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

bool Player::collision(SDL_Rect pos) {
	bool isCollision = false;
	for(auto col : collisionEntities) {
		if((isCollision = Physics::checkCollision(&pos, col))) {
			break;
		}
	}
	return isCollision;
}

void Player::drawHitBox(SDL_Renderer* renderer) {
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);

	SDL_Rect* playerbox = new SDL_Rect();
	playerbox->x = hitbox->x + cam->getOffsetX();
	playerbox->y = hitbox->y + cam->getOffsetY();
	playerbox->w = hitbox->w;
	playerbox->h = hitbox->h; 

	SDL_RenderDrawRect(renderer, playerbox);
	
}