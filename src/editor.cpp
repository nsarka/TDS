#include "../include/editor.h"

Editor::Editor() {}
Editor::~Editor() {}

void Editor::handleEvents(SDL_Event event) {

    if(event.type == SDL_MOUSEWHEEL)
    {
        if(event.wheel.y > 0) {
			// Scroll Up
			std::cout << "Next sprite..." << std::endl;
			source_rect_counter++;
			if(source_rect_counter >= (int)sourceRectList.size()) {
				source_rect_counter = 0;
			}
        }
        else if(event.wheel.y < 0) {
			// Scroll Down
			std::cout << "Previous sprite..." << std::endl;
			source_rect_counter--;
			if(source_rect_counter < 0) {
				source_rect_counter = sourceRectList.size() - 1;
			}
        }
	} else if( event.type == SDL_MOUSEBUTTONDOWN ) {
		// Check if physics mode is on
		if( event.button.button == SDL_BUTTON_LEFT && colliderMode ) {
			if(event.button.state == SDL_PRESSED) {
				pointDown.x = xMouse - cam->getOffsetX();
				pointDown.y = yMouse - cam->getOffsetY();
				buttonDown = true;
				std::cout << pointDown.x << std::endl;
				std::cout << pointDown.y << std::endl;
			}
		}
		if( event.button.button == SDL_BUTTON_LEFT && !colliderMode) {

			int xPos = event.button.x - cam->getOffsetX();
			int yPos = event.button.y - cam->getOffsetY();

			// Snap x,y coordinates to the 128x128 pixel grid for left mouse click
			if (xPos > 0) {
				xPos -= xPos % 128;
			} else {
				xPos -= xPos % 128;
				xPos -= 128;
			}
			if (yPos > 0) {
				yPos -= yPos % 128;
			} else {
				yPos -= yPos % 128;
				yPos -= 128;
			}

			SDL_Rect tile_rect = { xPos, yPos, 128, 128 };

			Tile* t = new Tile("environment", tile_rect, 0);
			//t->AddFrame(sheet_source_rect);
			t->animCycle.push_back(sourceRectList.at(source_rect_counter));

			gameEntities.push_back(t);
		} else if(!colliderMode) {
			SDL_Rect tile_rect = { (event.button.x-64) - cam->getOffsetX(), (event.button.y-64) - cam->getOffsetY(), 128, 128 };

			Tile* t = new Tile("environment", tile_rect, 0);
			//t->AddFrame(sheet_source_rect);
			t->animCycle.push_back(sourceRectList.at(source_rect_counter));

			gameEntities.push_back(t);
		}
	//If the left mouse button was released
	} else if( event.type == SDL_MOUSEBUTTONUP) {
		// Check if physics mode is on
		if( event.button.button == SDL_BUTTON_LEFT && colliderMode ) {
			if(event.button.state == SDL_RELEASED) {
				pointUp.x = xMouse - cam->getOffsetX();
				pointUp.y = yMouse - cam->getOffsetY();
				buttonDown = false;
				std::cout << pointUp.x << std::endl;
				std::cout << pointUp.y << std::endl;
				Physics::setCollisionRect(pointDown, pointUp);
			}
		}
	} 
	else if( event.type == SDL_KEYDOWN ) {
		switch( event.key.keysym.sym ) {

			case SDLK_UP:
			std::cout << "Next sprite..." << std::endl;
			source_rect_counter++;
			if(source_rect_counter >= (int)sourceRectList.size()) {
				source_rect_counter = 0;
			}
			break;

			case SDLK_DOWN:
			std::cout << "Previous sprite..." << std::endl;
			source_rect_counter--;
			if(source_rect_counter < 0) {
				source_rect_counter = sourceRectList.size() - 1;
			}
			break;

			case SDLK_F5:
			drawCol = !drawCol;
			if(drawCol)
            	std::cout << "Drawing colliders..." << std::endl;
            break;

			case SDLK_p:
			colliderMode = !colliderMode;
			if(colliderMode)
				std::cout << "Collider mode ON..." << std::endl;
			else
				std::cout << "Collider mode OFF..." << std::endl;
			break;

			default:
			//std::cout << "Default key??" << std::endl;
			break;
		}
	} else if( event.type == SDL_KEYUP ) {
		switch( event.key.keysym.sym ) {
			default:
			//std::cout << "Default key??" << std::endl;
			break;
		}
	}
}

void Editor::drawSelected(SDL_Renderer* renderer, int x, int y) {
	SDL_Rect dest = { x, y, 128, 128 };
	SDL_RenderCopy(renderer, sheet->getTexture(spr_sheet_name), &sourceRectList.at(source_rect_counter), &dest);
}

void Editor::drawGrid(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, SDL_ALPHA_OPAQUE);

    int startX = (cam->getOffsetX() % 128) - 128;
    int startY = (cam->getOffsetY() % 128) - 128;

    for(int x = startX; x <= 1024 + startX + 128; x += 128) {
        for(int y = startY; y <= 768 + startY + 128; y += 128) {
            SDL_RenderDrawLine(renderer, x, y, x+128, y);
            SDL_RenderDrawLine(renderer, x, y, x, y+128);
        }
    }

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
}

void Editor::drawColliders(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 0, 255, 255, 0);

    for(auto col : collisionEntities) {

		SDL_Rect* rect = new SDL_Rect();

		rect->x = col->x + cam->getOffsetX();
		rect->y = col->y + cam->getOffsetY();
		rect->w = col->w;
		rect->h = col->h;

		SDL_RenderDrawRect(renderer, rect);
	}
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
}

void Editor::loadSprites() {
	std::ifstream level_file;
    level_file.open("../assets/environment/environment.txt");

    if (level_file.is_open()) {

        std::string data;
        
        while(!level_file.eof()) {

            getline(level_file, data);

            if(data.length() > 0) {
                Deserialize(data);
            }
        }

    } else {
        std::cout << "[!] Couldn't open 'environment.txt'" << std::endl;
	}
}
		
		
void Editor::Deserialize(std::string lineData) {
	SDL_Rect rect;
    
	std::stringstream ss;
	ss << lineData;
	std::queue<std::string> readData;

	while(ss.good()) {
		std::string substr;
		getline(ss, substr, ',');
		readData.push(substr);
	}

	readData.pop();
	rect.x 			= atoi(readData.front().c_str());
	readData.pop();

	rect.y 			= atoi(readData.front().c_str());
	readData.pop();

	rect.w 			= atoi(readData.front().c_str());
	readData.pop();

	rect.h 			= atoi(readData.front().c_str());

	addSourceRectToList(rect);
}