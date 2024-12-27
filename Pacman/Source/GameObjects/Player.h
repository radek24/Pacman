#pragma once

#include "SDL_Wrapper.h"
#include "LevelManager.h"
#include "GameObjects/Maze.h"



typedef void (*tileChangeCallback)(LevelManager*, Vec2i*);
typedef void (*livesChangedCallback)(LevelManager*, int);

typedef struct {
	tileChangeCallback onTileChanged;
	livesChangedCallback onLivesChanged;
}PlayerCallbacks;



typedef struct {
	int currentIndex;
	int lastIndex;
	Vec2i lastTile;
	Vec2i currentTile;
	int scale;
	Orientation desiredOrientation;
	Orientation orientation;
	float speed;
	float currentSpeed;
	EntityState state;
	SDL_Texture* SpriteSheet;
	PlayerCallbacks callbacks;
	int lives;
}Player;

void InitPlayer(Player* player,  int lives,SDL_Renderer* renderer,Vec2i *StartingPos, PlayerCallbacks callbacks);
void UpdatePlayer(Player* player, LevelManager* manager, float deltaTime,Maze *maze);
void DelayedUpdatePlayerInput(Player* player, Maze* maze);
void PlayerImidiateInput(Player* player, Maze* maze);
void CheckPlayerCollision(Player* player, Maze* maze);
int UpdatePlayerLocation(Player* player, LevelManager* manager, float deltaTime);
void RenderPlayer(Player* player,float currentTime, SDL_Renderer* renderer);
void DestroyPlayer(Player* player);