#include "LivesDisplay.h"

void InitLivesDisplay(LivesDisplay* display, int lives, Vec2i pos, SDL_Renderer* renderer)
{
	display->sprite = IMG_LoadTexture(renderer, "Resources/Sprites/Pacman.png");
	display->pos = pos;
	display->currentLives = lives;
}

void UpdateLivesDisplay(LivesDisplay* display, int lives)
{
	display->currentLives = lives;
}

void RenderLivesDisplay(LivesDisplay* display, SDL_Renderer* renderer)
{
	for (int i = 0; i < display->currentLives; i++)
	{
		SDL_Rect position = { TILE_SIZE * display->pos.x - ((TILE_SIZE * 2) * i) ,TILE_SIZE * display->pos.y,15 * 2,15 * 2};
		SDL_Rect tile = { 15,15,15,15 };
		SDL_RenderCopy(renderer, display->sprite, &tile, &position);
	}
}

void DestroyLivesDisplay(LivesDisplay* display)
{
	SDL_DestroyTexture(display->sprite);
}
