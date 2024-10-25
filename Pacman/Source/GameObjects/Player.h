#pragma once

#include "../SDL_Wrapper.h"
#include "../LevelManager.h"
#include "../GameObjects/Maze.h"

typedef enum { Alive, Dead }PlayerState;

typedef struct {
	Vec2f position;
	Vec2i currentTile;
	int scale;
	Orientation desiredOrientation;
	Orientation orientation;
	float speed;
	PlayerState state;
	SDL_Texture* SpriteSheet;
}Player;

void InitPlayer(Player* player,SDL_Renderer* renderer,Vec2i *StartingPos);
void UpdatePlayer(Player* player, LevelManager* manager, float deltaTime,Maze *maze);
void RenderPlayer(Player* player,float currentTime, SDL_Renderer* renderer);
void DestroyPlayer(Player* player);