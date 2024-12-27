#include "LivesDisplay.h"


void InitLivesDisplay(LivesDisplay* display, Vec2i pos, SDL_Renderer* renderer)
{
	display->sprite = IMG_LoadTexture(renderer, "Resources/Sprites/Pacman.png");
	display->pos = pos;
}

void RenderLivesDisplay(LivesDisplay* display, SDL_Renderer* renderer, Player* player)
{
	for (int i = 0; i < player->lives; i++)
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
