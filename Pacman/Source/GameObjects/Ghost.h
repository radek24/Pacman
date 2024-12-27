#pragma once

#include "SDL_Wrapper.h"
#include "LevelManager.h"
#include "GameObjects/Maze.h"

typedef enum { Blinky, Pinky, Inky, Clyde} GhostType;

typedef struct {
	int currentIndex;
	int lastIndex;
	Vec2i currentTile;
	int scale;
	Orientation orientation;
	float speed;
	float currentSpeed;
	float timeWhenDied;
	EntityState state;
	GhostType type;
	SDL_Texture* spriteSheet;

	/*This gets loaded 4x even when the textures are the same, I should put it in some ghost manager */
	SDL_Texture* deadSprite;
	SDL_Texture* vonurableSprite;
}Ghost;

void InitGhost(Ghost* ghost, Vec2i StartingPos, GhostType type, LevelManager* manager);
void UpdateGhost(Ghost* ghost,LevelManager* manager,float deltaTime, Maze* maze);
void RenderGhost(Ghost* ghost,LevelManager* manager);
void DestroyGhost(Ghost* ghost);