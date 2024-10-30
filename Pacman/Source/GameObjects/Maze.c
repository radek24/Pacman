#include "Maze.h"
#include <stdio.h>
#include <stdlib.h>
#include "Core/Core.h"

int isMazeTileFilled(int x, int y, Maze* maze) {
	PAC_ASSERT(maze);
	if (x >= MAZE_DIMENSIONS_X || x < 0 || y >= MAZE_DIMENSIONS_Y || y < 0) return 1;
	
	if (maze->Tiles[y][x] == space) return 0;

	return 1;
}

TileType CalculateMazeTile(int x, int y, Maze* maze) {
	if (!isMazeTileFilled(x, y, maze)) { return space; }

	int top = isMazeTileFilled(x, y - 1, maze);
	int down = isMazeTileFilled(x, y + 1, maze);
	int left = isMazeTileFilled(x-1, y, maze);
	int right = isMazeTileFilled(x + 1, y, maze);

	int topLeft = isMazeTileFilled(x-1, y - 1, maze);
	int topRight = isMazeTileFilled(x+1, y - 1, maze);
	int downLeft = isMazeTileFilled(x - 1, y+1, maze);
	int downRight = isMazeTileFilled(x + 1, y+1, maze);

	if (top && left && right && down && topLeft && topRight && downLeft && downRight) { return solidmass; }
	
	if (top && left && !right && !down) { return outerCornerLeftUp; }
	if (top && !left && right && !down) { return outerCornerRightUp; }
	if (!top && left && !right && down) { return outerCornerLeftDown; }
	if (!top && !left && right && down) { return outerCornerRightDown; }

	if (top && left && right && down && !topLeft && topRight && downLeft && downRight) { return innerCornerLeftUp; }
	if (top && left && right && down && topLeft && !topRight && downLeft && downRight) { return innerCornerRightUp; }
	if (top && left && right && down && topLeft && topRight && !downLeft && downRight) { return innerCornerLeftDown; }
	if (top && left && right && down && topLeft && topRight && downLeft && !downRight) { return innerCornerRightDown; }

	if (down && left && right && !top) { return lineBottom; }
	if (!down && left && right && top) { return lineTop; }
	if (down && !left && right && top) { return lineLeft; }
	if (down && left && !right && top) { return lineRight; }
	
	return lineTop;
}

void InitMaze(const char* filePath, Maze* maze, Pickups* pickups,SDL_Renderer* renderer)
{
	FILE* mazefile;
	mazefile = fopen(filePath, "r");
	PAC_ASSERT(mazefile);
	
	maze->SpriteSheet = IMG_LoadTexture(renderer, "Resources/Sprites/LevelTileSet.png");
	maze->oneTileSize = 16;
	if (maze->SpriteSheet == NULL) {
		PAC_FATAL("Failed to load texture! IMG_Error: %s\n", IMG_GetError());
		PAC_ASSERT(0);
	}

	char ch;
	int currentIndex=0;
	while ((ch = fgetc(mazefile)) != EOF) {
		int currentX = currentIndex%MAZE_DIMENSIONS_X;
		int currentY = currentIndex/MAZE_DIMENSIONS_X;

		switch (ch)
		{
		case '#':	maze->Tiles[currentY][currentX] = outerCornerRightUp;
		break;
		case '.': { 
			maze->Tiles[currentY][currentX] = space; 
			Vec2i pos = { currentX ,currentY };
			AddPickup(pickups,&pos,Score);

		}
		break;
		case 'O': {
			maze->Tiles[currentY][currentX] = space;
			Vec2i pos = { currentX ,currentY };
			AddPickup(pickups, &pos, Big);

		}
		break;
		case '*':	maze->Tiles[currentY][currentX] = space;
		break;
		case '\n':	continue;
		break;
		default:	PAC_CHECKNOENTRY();
		break;
		}
		currentIndex++;
	}
	fclose(mazefile);

	for (int y = 0; y < MAZE_DIMENSIONS_Y; y++)
	{
		for (int x = 0; x < MAZE_DIMENSIONS_X; x++)
		{
			maze->Tiles[y][x] = CalculateMazeTile(x,y,maze);
		}
	}
	PAC_LOG("Maze loaded from %s", filePath);
}

void RenderMaze(SDL_Renderer* renderer,Maze* maze)
{
	SDL_Rect Position = {TILE_SIZE,TILE_SIZE,TILE_SIZE,TILE_SIZE};
	SDL_Rect Tile= { 0 ,0,maze->oneTileSize,maze->oneTileSize };
	for (int y = 0; y < MAZE_DIMENSIONS_Y; y++)
	{
		for (int x = 0; x < MAZE_DIMENSIONS_X; x++)
		{
			Tile.x = maze->oneTileSize * (int)maze->Tiles[y][x];
			if (maze->Tiles[y][x] == space) Tile.x = maze->oneTileSize * 12;
			Position.x = TILE_SIZE * x + TILE_SIZE;
			Position.y = TILE_SIZE * y + TILE_SIZE;
			SDL_RenderCopy(renderer, maze->SpriteSheet, &Tile, &Position);
		}
	}
}

void DestroyMaze(Maze* maze)
{
	SDL_DestroyTexture(maze->SpriteSheet);
}
