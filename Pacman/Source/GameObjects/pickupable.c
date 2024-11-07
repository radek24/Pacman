#include "Pickupable.h"
#include <stdlib.h>

static void UpdatePickup(Pickupable* pickup, float deltaTime)
{
}

static void RenderPickup(Pickupable* pickup, float currentTime, SDL_Renderer* renderer)
{
}

static void DestroyPickup(Pickupable* pickup)
{
}

void InitPickups(Pickups* pickups, SDL_Renderer* renderer)
{
	pickups->SpriteSheet = IMG_LoadTexture(renderer, "Resources/Sprites/Pickups.png");
	if (pickups->SpriteSheet == NULL) { PAC_FATAL("Failed to load texture! IMG_Error: %s\n", IMG_GetError()); PAC_ASSERT(0); }
	
	pickups->size = 0;
	pickups->capacity = 20;
	pickups->pickups = (Pickupable*)malloc(sizeof(Pickupable) * pickups->capacity);
	pickups->spriteSize = 16;
	
}

/*Pickups processing*/
void AddPickup(Pickups* pickups, Vec2i* pos, PickupType type)
{
	PAC_ASSERT(pickups->capacity);
	//Grow array
	if (pickups->size == pickups->capacity) {
		pickups->capacity *= 2;
		Pickupable* tmp = (Pickupable*)realloc(pickups->pickups, sizeof(Pickupable) * pickups->capacity);
		PAC_ASSERT(tmp);
		pickups->pickups = tmp;
		PAC_LOG("Realloc pickups to %d", pickups->capacity);
	}
	pickups->pickups[pickups->size] = (Pickupable){ type,*pos };
	pickups->size++;
}

void UpdatePickups(Pickups* pickups, float deltaTime)
{
}

void RenderPickups(Pickups* pickups, float currentTime, SDL_Renderer* renderer)
{
	for (int i = 0; i < pickups->size; i++)
	{
		SDL_Rect tile = { pickups->pickups[i].type * pickups->spriteSize  ,0,pickups->spriteSize,pickups->spriteSize};
		SDL_Rect position = { TILE_SIZE +  TILE_SIZE* pickups->pickups[i].positionInGrid.x,TILE_SIZE+ TILE_SIZE * pickups->pickups[i].positionInGrid.y,TILE_SIZE,TILE_SIZE };
		
		if (pickups->pickups[i].type == Big && getSpriteIndexFromTime(currentTime/2, 2))SDL_RenderCopy(renderer, pickups->SpriteSheet, &tile, &position);
		if (pickups->pickups[i].type != Big)SDL_RenderCopy(renderer, pickups->SpriteSheet, &tile, &position);
	}
}

void DestroyPickups(Pickups* pickups)
{
	SDL_DestroyTexture(pickups->SpriteSheet);
	free(pickups->pickups);
	pickups->pickups = NULL;
	PAC_LOG("Pickups destroyed")
}
