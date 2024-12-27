#include "Ghost.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void InitGhost(Ghost* ghost, Vec2i StartingPos, GhostType type, LevelManager* manager)
{
	srand(time(NULL));
	ghost->timeWhenDied = 0;
	ghost->deadSprite = IMG_LoadTexture(manager->renderer,"Resources/Sprites/DeadGhost.png");
	ghost->vonurableSprite = IMG_LoadTexture(manager->renderer, "Resources/Sprites/Vunurable.png");
	PAC_ASSERT(ghost->deadSprite && ghost->vonurableSprite);
	ghost->orientation = Down;
	ghost->type = type;
	ghost->scale = 16;
	ghost->currentTile = StartingPos;
	ghost->state = Alive;

	switch (ghost->type)
	{
	case Blinky: { 
		ghost->spriteSheet = IMG_LoadTexture(manager->renderer, "Resources/Sprites/Blinky.png"); 
		ghost->speed = 4.0f;
	}break;
	case Pinky: { 
		ghost->spriteSheet = IMG_LoadTexture(manager->renderer, "Resources/Sprites/Pinky.png"); 
		ghost->speed = 5.0f;
	}break;
	case Inky: { 
		ghost->spriteSheet = IMG_LoadTexture(manager->renderer, "Resources/Sprites/Inky.png"); 
		ghost->speed = 5.0f;
	}break;
	case Clyde: {
		ghost->spriteSheet = IMG_LoadTexture(manager->renderer, "Resources/Sprites/Clyde.png"); 
		ghost->speed = 4.0f;
	}break;
	default: { PAC_CHECKNOENTRY(); }break;
	}
	ghost->currentSpeed = ghost->speed;
	PAC_ASSERT(ghost->spriteSheet);
}
int UpdateGhostLocation(Ghost* ghost, LevelManager* manager, float deltaTime)
{
	if (ghost->currentIndex != ghost->lastIndex && ghost->currentSpeed != 0.0)
	{
		switch (ghost->orientation)
		{
		case Left:	ghost->currentTile.x--; break;
		case Right:	ghost->currentTile.x++; break;
		case Up:	ghost->currentTile.y--; break;
		case Down:	ghost->currentTile.y++; break;
		default:PAC_CHECKNOENTRY(); break;
		}
		ghost->lastIndex = ghost->currentIndex;
		return 1;
	}
	return 0;
}

void CheckForCollisions(Ghost* ghost, Maze* maze) {
	switch (ghost->orientation) {
	case Left: {
		if (isMazeTileFilled(ghost->currentTile.x - 1, ghost->currentTile.y, maze)) {
			ghost->orientation = (rand() % 2) + 2;
		}
	} break;
	case Right: {
		if (isMazeTileFilled(ghost->currentTile.x + 1, ghost->currentTile.y, maze)) {
			ghost->orientation = (rand() % 2) + 2;
		}
	} break;
	case Up: {
		if (isMazeTileFilled(ghost->currentTile.x, ghost->currentTile.y - 1, maze)) {
			ghost->orientation = (rand() % 2) ;
		}
	} break;
	case Down: {
		if (isMazeTileFilled(ghost->currentTile.x, ghost->currentTile.y + 1, maze)) {
			ghost->orientation = (rand() % 2) ;
		}
	} break;
	default: PAC_CHECKNOENTRY(); break;
	}
}

void UpdateGhost(Ghost* ghost, LevelManager* manager,float deltaTime, Maze* maze)
{
	int callCallback = 0;
	ghost->currentIndex = ((int)(manager->gameTime * ghost->currentSpeed));
	callCallback = UpdateGhostLocation(ghost, manager, deltaTime);
	CheckForCollisions(ghost, maze);

	if (ghost->state == Dead && (manager->gameTime >  ghost->timeWhenDied + 5))
	{
		ghost->state = Alive;
		ghost->currentTile = (Vec2i){ 15,12 };
	}



}

void RenderGhost(Ghost* ghost, LevelManager* manager)
{
	SDL_Rect position = { (((int)ghost->currentTile.x + 1) * TILE_SIZE) - (TILE_SIZE / 2),((int)ghost->currentTile.y + 1) * TILE_SIZE - (TILE_SIZE / 2),ghost->scale * 2,ghost->scale * 2 };
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
