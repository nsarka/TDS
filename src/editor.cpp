#include "../include/editor.h"

Editor::Editor() {}
Editor::~Editor() {}

void Editor::handleEvents(SDL_Event event) {

	if( event.type == SDL_MOUSEBUTTONDOWN ) {
		//If the left mouse button was released
		if( event.button.button == SDL_BUTTON_LEFT ) {

			int xPos = event.button.x - cam->getOffsetX();
			int yPos = event.button.y - cam->getOffsetY();

			// Snap x,y coordinates to the 128x128 pixel grid for left mouse click
			xPos -= xPos % 128;
			yPos -= yPos % 128;

			if(xPos % 128 > 64) {
				xPos += 128;
			}

			if(yPos % 128 > 64) {
				yPos += 128;
			}

			if(yPos < 0) {
				yPos -= 128;
			}

			if(xPos < 0) {
				xPos -= 128;
			}
			
			SDL_Rect tile_rect = { xPos, yPos, 128, 128 };

			Tile* t = new Tile("environment", tile_rect, 0);
			//t->AddFrame(sheet_source_rect);
			t->animCycle.push_back(sourceRectList.at(source_rect_counter));

			gameEntities.push_back(t);
		} else {
			SDL_Rect tile_rect = { (event.button.x-64) - cam->getOffsetX(), (event.button.y-64) - cam->getOffsetY(), 128, 128 };

			Tile* t = new Tile("environment", tile_rect, 0);
			//t->AddFrame(sheet_source_rect);
			t->animCycle.push_back(sourceRectList.at(source_rect_counter));

			gameEntities.push_back(t);
		}
	} else if( event.type == SDL_KEYDOWN ) {
		switch( event.key.keysym.sym ) {

			case SDLK_p:
			std::cout << "Next sprite..." << std::endl;
			source_rect_counter++;
			if(source_rect_counter >= sourceRectList.size()) {
				source_rect_counter = 0;
			}
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