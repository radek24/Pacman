#pragma once
#include "Core/Math.h"
#include "Core/Core.h"
#include "Pickupable.h"

#include "SDL_Wrapper.h"

typedef enum
{
	space = -2,
	wall = -1,
	innerCornerLeftDown = 6,
	innerCornerRightDown = 7,
	innerCornerLeftUp = 0,
	innerCornerRightUp = 1,
	outerCornerLeftUp = 9,
	outerCornerRightDown = 2,
	outerCornerLeftDown = 3,
	outerCornerRightUp = 8,
	/*On which side is wall?*/
	lineTop = 4,
	lineBottom = 5,
	lineLeft = 10,
	lineRight = 11,
	solidmass = 12
}TileType;

typedef struct
{
	TileType Tiles[MAZE_DIMENSIONS_Y][MAZE_DIMENSIONS_X];
	SDL_Texture* SpriteSheet;
	int oneTileSize;
}Maze;

void InitMaze(const char* filePath,Maze* maze,Pickups* pickups ,SDL_Renderer* renderer);
void RenderMaze(SDL_Renderer* renderer, Maze* maze);
void DestroyMaze(Maze* maze);
int isMazeTileFilled(int x, int y, Maze* maze);