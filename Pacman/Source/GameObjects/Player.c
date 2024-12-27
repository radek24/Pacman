#include "Player.h"
#include "Core/Core.h"


void InitPlayer(Player* player,int lives, SDL_Renderer* renderer, Vec2i* StartingPos, PlayerCallbacks callbacks)
{
	if (callbacks.onTileChanged != NULL) { player->callbacks.onTileChanged = callbacks.onTileChanged; }
	player->currentIndex = 0;
	player->lastIndex = 0;
	player->currentTile = (*StartingPos);
	player->scale = 16;
	player->desiredOrientation = Right;
	player->orientation = Right;
	player->speed = 5.0f;
	player->currentSpeed = player->speed;
	player->SpriteSheet = IMG_LoadTexture(renderer, "Resources/Sprites/Pacman.png");
	if (player->SpriteSheet == NULL) {
		PAC_FATAL("Failed to load texture! IMG_Error: %s\n", IMG_GetError());
		PAC_ASSERT(0);
	}
	player->state = Alive;
	player->lives = lives;
}

void UpdatePlayer(Player* player, LevelManager* manager, float deltaTime, Maze* maze) {
	int callCallback = 0;
	player->currentIndex = ((int)(manager->gameTime * player->currentSpeed));
	callCallback = UpdatePlayerLocation(player, manager, deltaTime);
	

	SDL_Event event = manager->inputEvent;
	if (manager->isInputActive && event.type == SDL_KEYDOWN) {
		if (event.key.keysym.sym == SDLK_UP) player->desiredOrientation = Up;
		if (event.key.keysym.sym == SDLK_DOWN) player->desiredOrientation = Down;
		if (event.key.keysym.sym == SDLK_LEFT) player->desiredOrientation = Left;
		if (event.key.keysym.sym == SDLK_RIGHT) player->desiredOrientation = Right;
	}

	PlayerImidiateInput(player,maze);
	CheckPlayerCollision(player, maze);
	DelayedUpdatePlayerInput(player, maze);
	
	// Due to reasons
	if (callCallback) 
	{
		player->callbacks.onTileChanged(manager, &player->currentTile);
		callCallback = 0;
	}
}

/*This function moves player only when its possible to turn, so the control seems more responsive*/
void DelayedUpdatePlayerInput(Player* player, Maze* maze)
{
	if (player->desiredOrientation == player->orientation) return;
	
	switch (player->desiredOrientation) {
	case Left: {
		if (!isMazeTileFilled(player->currentTile.x - 1, player->currentTile.y, maze)) {
			player->currentSpeed = player->speed;
			player->orientation = Left;
		}
	} break;
	case Right: {
		if (!isMazeTileFilled(player->currentTile.x + 1, player->currentTile.y, maze)) {
			player->currentSpeed = player->speed;
			player->orientation = Right;
		}
	} break;
	case Up: {
		if (!isMazeTileFilled(player->currentTile.x, player->currentTile.y - 1, maze)) {
			player->currentSpeed = player->speed;
			player->orientation = Up;
		}
	} break;
	case Down: {
		if (!isMazeTileFilled(player->currentTile.x, player->currentTile.y + 1, maze)) {
			player->currentSpeed = player->speed;
			player->orientation = Down;
		}
	} break;
	default: PAC_CHECKNOENTRY(); break;
	}
	
}

/*This function moves player only if there are no obstacles in the way and only if current orientation is opposite. For precise turns check "DelayedUpdatePlayerInput" */
void PlayerImidiateInput(Player* player, Maze* maze)
{
	if (player->desiredOrientation == player->orientation) return;
	switch (player->desiredOrientation) {
	case Left: {
		if (!isMazeTileFilled(player->currentTile.x - 1, player->currentTile.y, maze) && player->currentSpeed != 0 && player->orientation == Right) { 
			player->orientation = Left;   
		}
	} break;
	case Right: {
		if (!isMazeTileFilled(player->currentTile.x + 1, player->currentTile.y, maze) && player->currentSpeed != 0 && player->orientation == Left) { 
			player->orientation = Right;
		}
	} break;
	case Up: {
		if (!isMazeTileFilled(player->currentTile.x, player->currentTile.y - 1, maze) && player->currentSpeed != 0 && player->orientation == Down) { 
			player->orientation = Up;
		}
	} break;
	case Down: {
		if (!isMazeTileFilled(player->currentTile.x, player->currentTile.y + 1, maze) && player->currentSpeed != 0 && player->orientation == Up) {
			player->orientation = Down;
		}
	} break;
	default: PAC_CHECKNOENTRY(); break;
	}
}




/*Check player colision based on current tile*/
void CheckPlayerCollision(Player* player, Maze* maze)
{
	switch (player->orientation) {
	case Left: {
		if (isMazeTileFilled(player->currentTile.x - 1, player->currentTile.y, maze)) {
			player->currentSpeed = 0;
		}
	} break;
	case Right: {
		if (isMazeTileFilled(player->currentTile.x + 1, player->currentTile.y, maze)) {
			player->currentSpeed = 0;
		}
	} break;
	case Up: {
		if (isMazeTileFilled(player->currentTile.x, player->currentTile.y - 1, maze)) {
			player->currentSpeed = 0;
		}
	} break;
	case Down: {
		if (isMazeTileFilled(player->currentTile.x, player->currentTile.y + 1, maze)) {
			player->currentSpeed = 0;
		}
	} break;
	default: PAC_CHECKNOENTRY(); break;
	}
	
}

int UpdatePlayerLocation(Player* player, LevelManager* manager, float deltaTime)
{
	if (player->currentIndex != player->lastIndex && player->currentSpeed != 0.0)
	{
		switch (player->orientation)
		{
		case Left:	player->currentTile.x--; break;
		case Right:	player->currentTile.x++; break;
		case Up:	player->currentTile.y--; break;
		case Down:	player->currentTile.y++; break;
		default:PAC_CHECKNOENTRY(); break;
		}
		player->lastIndex = player->currentIndex;
		return 1;
	}
	return 0;
}

void RenderPlayer(Player* player, float currentTime, SDL_Renderer* renderer)
{
	SDL_Rect position = { (((int)player->currentTile.x + 1) * TILE_SIZE) - (TILE_SIZE/2),((int)player->currentTile.y + 1) * TILE_SIZE - (TILE_SIZE / 2),player->scale * 2,player->scale * 2};
	SDL_Rect tile = { player->scale* getSpriteIndexFromTime(currentTime,2) ,player->orientation * player->scale ,player->scale,player->scale};
	SDL_RenderCopy(renderer, player->SpriteSheet, &tile, &position);
}

void DestroyPlayer(Player* player)
{
	SDL_DestroyTexture(player->SpriteSheet);
}
