#include "Text.h"

void InitText(Text* text, SDL_Color color, char* textToRender, Vec2i location, LevelManager* manager)
{
	strcpy(text->text, textToRender);
	text->color = color;
	text->location = location;
	SDL_Surface* surface = TTF_RenderText_Solid(manager->font, text->text, text->color);
	text->_currentTexture = SDL_CreateTextureFromSurface(manager->renderer, surface);
	SDL_FreeSurface(surface);
	SDL_QueryTexture(text->_currentTexture, NULL, NULL, &(text->_textDimensions.x), &(text->_textDimensions.y));

}

void UpdateText(Text* text, char* textToRender, LevelManager* manager)
{
	strcpy(text->text, textToRender);
	SDL_Surface* surface = TTF_RenderText_Solid(manager->font, text->text, text->color);
	SDL_DestroyTexture(text->_currentTexture);
	text->_currentTexture = SDL_CreateTextureFromSurface(manager->renderer, surface);
	SDL_FreeSurface(surface);
	SDL_QueryTexture(text->_currentTexture, NULL, NULL, &(text->_textDimensions.x), &(text->_textDimensions.y));
}

void RenderText(Text* text, SDL_Renderer* renderer)
{
	SDL_Rect dstrect = { text->location.x, text->location.y, text->_textDimensions.x, text->_textDimensions.y };
	SDL_RenderCopy(renderer, text->_currentTexture, NULL, &dstrect);
}

void DestroyText(Text* text)
{
	SDL_DestroyTexture(text->_currentTexture);
	PAC_LOG("Destroyed text renderer: %s", text->text);
}
