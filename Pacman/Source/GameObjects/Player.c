#include "Player.h"
#include "Core/Core.h"


void InitPlayer(Player* player, SDL_Renderer* renderer, Vec2i* StartingPos, tileChangeCallback callback)
{
	if (callback != NULL) { player->callback = callback; }
	player->currentTile = (*StartingPos);
	player->scale = 15;
	player->currentTile = *StartingPos;
	player->lastTile = *StartingPos;
	player->position.x = (float)StartingPos->x*TILE_SIZE;
	player->position.y = (float)StartingPos->y*TILE_SIZE+9;
	player->lastPosition = player->position;
	player->desiredOrientation = Left;
	player->orientation = Left;
	player->speed = 80.0f;
	player->currentSpeed = player->speed;
	player->SpriteSheet = IMG_LoadTexture(renderer, "Resources/Sprites/Pacman.png");
	if (player->SpriteSheet == NULL) {
		PAC_FATAL("Failed to load texture! IMG_Error: %s\n", IMG_GetError());
		PAC_ASSERT(0);
	}
	player->state = Alive;

}
void UpdatePlayer(Player* player, LevelManager* manager, float deltaTime, Maze* maze) {
	SDL_Event event = manager->inputEvent;
	if (manager->isInputActive && event.type == SDL_KEYDOWN) {
		if (event.key.keysym.sym == SDLK_UP) player->desiredOrientation = Up;
		if (event.key.keysym.sym == SDLK_DOWN) player->desiredOrientation = Down;
		if (event.key.keysym.sym == SDLK_LEFT) player->desiredOrientation = Left;
		if (event.key.keysym.sym == SDLK_RIGHT) player->desiredOrientation = Right;
	}
	PlayerImidiateInput(player, maze);
	
	// Colisin checking algorithm 
	// We only check collision if player enters new tile.
	if (IsPlayerPerfectlyOnTile(player)) {
		UpdateCurrentTile(player,manager);
		CheckPlayerCollision(player, maze);
		DelayedUpdatePlayerInput(player, maze);
	}
	
	UpdatePlayerLocation(player, deltaTime);

	if (deltaTime * player->currentSpeed > 1.0) PAC_WARN("Player is skipping pixels, this is very bad. Moved by %f", deltaTime * player->currentSpeed);

	player->lastPosition = player->position;
}

/*This function moves player only when its possible to turn, so the control seems more responsive*/
void DelayedUpdatePlayerInput(Player* player, Maze* maze)
{
	if (player->desiredOrientation != player->orientation)
	{
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
}

/*Check if player is pixel perfect on tile, this functin will be problematic if player moves by more than 2 pixel at once, but idk solution to this.*/
int IsPlayerPerfectlyOnTile(Player* player)
{
	return ((int)player->position.x) % (TILE_SIZE) == (TILE_SIZE / 2) + 1 && ((int)player->position.y) % (TILE_SIZE) == (TILE_SIZE / 2) + 1;
}

/*Sets current tile and last visited tile based on player location*/
void UpdateCurrentTile(Player* player,LevelManager* manager)
{
	if (player->currentTile.x != ((int)(player->position.x + (player->scale)) / (TILE_SIZE)) - 1 || player->currentTile.y != ((int)(player->position.y + (player->scale)) / (TILE_SIZE)) - 1) {
		player->lastTile = player->currentTile;
		player->currentTile.x = ((int)(player->position.x + (player->scale)) / (TILE_SIZE)) - 1;
		player->currentTile.y = ((int)(player->position.y + (player->scale)) / (TILE_SIZE)) - 1;

		player->callback(manager, &player->currentTile);
	}
}

/*This function moves player only if there are no obstacles in the way and only if current orientation is opposite. For precise turns check "DelayedUpdatePlayerInput" */
void PlayerImidiateInput(Player* player, Maze* maze)
{
	if (player->desiredOrientation != player->orientation) {
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

void UpdatePlayerLocation(Player* player, float deltaTime)
{
	switch (player->orientation)
	{
	case Left:	player->position.x += deltaTime * player->currentSpeed * -1;	break;
	case Right:	player->position.x += deltaTime * player->currentSpeed;	break;
	case Up:	player->position.y += deltaTime * player->currentSpeed * -1;	break;
	case Down:	player->position.y += deltaTime * player->currentSpeed;	break;

	default:PAC_CHECKNOENTRY(); break;
	}
}

void RenderPlayer(Player* player, float currentTime, SDL_Renderer* renderer)
{
	SDL_Rect position = { (int)player->position.x,(int)player->position.y,player->scale*2,player->scale*2 };
	SDL_Rect tile = { player->scale* getSpriteIndexFromTime(currentTime,2) ,player->orientation * player->scale ,player->scale,player->scale};
	SDL_RenderCopy(renderer, player->SpriteSheet, &tile, &position);

#if !defined(PAC_SHIPPING) 
	SDL_Rect currentTile = { (TILE_SIZE ) * (player->currentTile.x+1)  ,(TILE_SIZE ) * (player->currentTile.y+1),TILE_SIZE,TILE_SIZE };
	SDL_Rect playerPos = { (int)player->position.x  ,(int)player->position.y,4,4 };
	SDL_Rect playerPosCenter = { (int)player->position.x+player->scale  ,(int)player->position.y + player->scale,4,4 };
	SDL_Rect playerColision = { (int)player->position.x  ,(int)player->position.y,player->scale * 2,player->scale * 2 };
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 100);
	SDL_RenderFillRect(renderer, &playerColision);
	
	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
	SDL_RenderFillRect(renderer, &playerPos);
	SDL_SetRenderDrawColor(renderer, 0, 0, 255, 100);
	SDL_RenderFillRect(renderer, &playerPosCenter);
	SDL_RenderFillRect(renderer, &currentTile);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
#endif
}

void DestroyPlayer(Player* player)
{
	SDL_DestroyTexture(player->SpriteSheet);
}
