#pragma once

#include "../SDL_Wrapper.h"
#include "../LevelManager.h"
#include "../GameObjects/Maze.h"

typedef enum { Alive, Dead }PlayerState;

typedef struct {
	Vec2f position;
	Vec2i lastTile;
	Vec2i currentTile;
	int scale;
	Orientation desiredOrientation;
	Orientation orientation;
	float speed;
	float currentSpeed;
	PlayerState state;
	SDL_Texture* SpriteSheet;
}Player;

void InitPlayer(Player* player,SDL_Renderer* renderer,Vec2i *StartingPos);
void UpdatePlayer(Player* player, LevelManager* manager, float deltaTime,Maze *maze);
void DelayedUpdatePlayerInput(Player* player, Maze* maze);
int IsPlayerPerfectlyOnTile(Player* player);
void UpdateCurrentTile(Player* player);
void PlayerImidiateInput(Player* player, Maze* maze);
void CheckPlayerCollision(Player* player, Maze* maze);
void UpdatePlayerLocation(Player* player, float deltaTime);
void RenderPlayer(Player* player,float currentTime, SDL_Renderer* renderer);
void DestroyPlayer(Player* player);