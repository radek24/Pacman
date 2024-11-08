#include "Ghost.h"

void InitGhost(Ghost* ghost, Vec2i StartingPos, GhostType type, LevelManager* manager)
{
	ghost->deadSprite = IMG_LoadTexture(manager->renderer,"Resources/Sprites/DeadGhost.png");
	ghost->vonurableSprite = IMG_LoadTexture(manager->renderer, "Resources/Sprites/Vunurable.png");
	PAC_ASSERT(ghost->deadSprite && ghost->vonurableSprite);
	ghost->orientation = Right;
	ghost->type = type;
	ghost->scale = 16;
	ghost->currentTile = StartingPos;
	ghost->position.x = (float)StartingPos.x * TILE_SIZE + TILE_SIZE/2;
	ghost->position.y = (float)StartingPos.y * TILE_SIZE + TILE_SIZE / 2;
	ghost->state = Alive;

	switch (ghost->type)
	{
	case Blinky: { ghost->spriteSheet = IMG_LoadTexture(manager->renderer, "Resources/Sprites/Blinky.png"); }break;
	case Pinky: { ghost->spriteSheet = IMG_LoadTexture(manager->renderer, "Resources/Sprites/Pinky.png"); }break;
	case Inky: { ghost->spriteSheet = IMG_LoadTexture(manager->renderer, "Resources/Sprites/Inky.png"); }break;
	case Clyde: { ghost->spriteSheet = IMG_LoadTexture(manager->renderer, "Resources/Sprites/Clyde.png"); }break;
	default: { PAC_CHECKNOENTRY(); }break;
	}
	PAC_ASSERT(ghost->spriteSheet);
}

void UpdateGhost(Ghost* ghost, LevelManager* manager)
{
}

void RenderGhost(Ghost* ghost, LevelManager* manager)
{
	SDL_Rect position = { (int)ghost->position.x,(int)ghost->position.y,ghost->scale * 2,ghost->scale * 2 };
	switch (ghost->state)
	{
	case Alive: {
		SDL_Rect tile = { ghost->scale * getSpriteIndexFromTime(manager->gameTime,2) ,ghost->orientation * ghost->scale ,ghost->scale,ghost->scale };
		SDL_RenderCopy(manager->renderer, ghost->spriteSheet, &tile, &position);
	}break;
	case Vunurable: {
		SDL_Rect tile = { ghost->scale * getSpriteIndexFromTime(manager->gameTime,2) ,getSpriteIndexFromTime(manager->gameTime/3.0,2)* ghost->scale,ghost->scale,ghost->scale };
		SDL_RenderCopy(manager->renderer, ghost->vonurableSprite, &tile, &position);
	}break;
	case Dead: {
		SDL_Rect tile = { 0 ,ghost->orientation * ghost->scale ,ghost->scale,ghost->scale };
		SDL_RenderCopy(manager->renderer, ghost->deadSprite, &tile, &position);
	}break;
	default: PAC_CHECKNOENTRY(); break;
	}
}

void DestroyGhost(Ghost* ghost)
{
	SDL_DestroyTexture(ghost->deadSprite);
	SDL_DestroyTexture(ghost->vonurableSprite);
	SDL_DestroyTexture(ghost->spriteSheet);
}
