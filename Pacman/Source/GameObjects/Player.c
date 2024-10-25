#include "Player.h"
#include "../Core/Core.h"


void InitPlayer(Player* player, SDL_Renderer* renderer, Vec2i* StartingPos)
{
	
	player->currentTile = (*StartingPos);
	player->scale = 15;
	player->position.x = (float)StartingPos->x*TILE_SIZE;
	player->position.y = (float)StartingPos->y*TILE_SIZE+9;
	player->desiredOrientation = Left;
	player->orientation = Left;
	player->speed = 20.0f;
	player->SpriteSheet = IMG_LoadTexture(renderer, "Resources/Sprites/Pacman.png");
	player->state = Alive;

}
void UpdatePlayer(Player* player, LevelManager* manager, float deltaTime, Maze* maze) {
	SDL_Event event = manager->inputEvent;
	if (manager->isInputActive && event.type == SDL_KEYDOWN) {
		if (event.key.keysym.sym == SDLK_UP) player->desiredOrientation = Up;
		if (event.key.keysym.sym == SDLK_DOWN) player->desiredOrientation = Down;
		if (event.key.keysym.sym == SDLK_LEFT) player->desiredOrientation = Left;
		if (event.key.keysym.sym == SDLK_RIGHT) player->desiredOrientation = Right;
		
		PAC_LOG("Changed desired orientation to %d", player->desiredOrientation);
	}

	int currentTileX = ((int)(player->position.x + (player->scale)) / (TILE_SIZE)) - 1;
	int currentTileY = ((int)(player->position.y + (player->scale)) / (TILE_SIZE)) - 1;
	if (currentTileX != player->currentTile.x)
	{
		player->currentTile.x = currentTileX;

		PAC_LOG("Updated player collisions Left: %d Right: %d Up: %d Down: %d", isMazeTileFilled(player->currentTile.x - 1, player->currentTile.y, maze), isMazeTileFilled(player->currentTile.x + 1, player->currentTile.y, maze), isMazeTileFilled(player->currentTile.x, player->currentTile.y-1, maze), isMazeTileFilled(player->currentTile.x, player->currentTile.y+1, maze));
		
		if (isMazeTileFilled(player->currentTile.x - 1, player->currentTile.y, maze))
		{
			PAC_LOG("colided");
			player->speed = 0.0f;
		}
		

		
	}
	if (currentTileY != player->currentTile.y)
	{
		player->currentTile.y = currentTileY;
		PAC_LOG("Updated player collisions");
	}
	
	
	


	switch (player->orientation)
	{
	case Left:	player->position.x += deltaTime * player->speed*-1;	break;
	case Right:	player->position.x += deltaTime * player->speed;	break;
	case Up:	player->position.y += deltaTime * player->speed*-1;	break;
	case Down:	player->position.y += deltaTime * player->speed;	break;

	default:
		PAC_CHECKNOENTRY();
		break;
	}
	

	
	


	
}

void RenderPlayer(Player* player, float currentTime, SDL_Renderer* renderer)
{
	
	SDL_Rect position = { player->position.x,player->position.y,player->scale*2,player->scale*2 };
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
}
