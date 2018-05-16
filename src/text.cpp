#include "../include/text.h"



Text::Text(std::string path) {
    TTF_Init();
	font = TTF_OpenFont(path.c_str(), PT_SIZE);
}

Text::~Text() {
	TTF_CloseFont(font);
}

SDL_Texture* Text::RenderText(SDL_Renderer* renderer, std::string text)
{
	SDL_Color textColor = { 255, 255, 255, 255 }; // white
	SDL_Texture* solidTexture;

	SDL_Surface* solid = TTF_RenderText_Solid( font, text.c_str(), textColor );
	solidTexture = SurfaceToTexture(renderer, solid);

	/*SDL_Rect solidRect;
	solidRect.x = 0;
	solidRect.y = 0;
	SDL_QueryTexture( solidTexture, NULL, NULL, &solidRect.w, &solidRect.h );*/

	return solidTexture;
}

SDL_Texture* Text::SurfaceToTexture(SDL_Renderer* renderer, SDL_Surface* surf)
{
	SDL_Texture* text;
	text = SDL_CreateTextureFromSurface( renderer, surf );
	SDL_FreeSurface( surf );

	return text;
}