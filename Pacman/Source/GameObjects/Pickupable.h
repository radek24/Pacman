#pragma once
#include "Core/Core.h"
#include "SDL_Wrapper.h"

typedef enum {Big, Score,Cherry}PickupType;

typedef struct
{
	PickupType type;
	Vec2i positionInGrid;
	
}Pickupable;

typedef struct {
	SDL_Texture* SpriteSheet;
	int spriteSize;
	Pickupable* pickups;
	int size;
	int capacity;
}Pickups;


void InitPickups(Pickups* pickups, SDL_Renderer* renderer);
void AddPickup(Pickups* pickups, Vec2i* pos, PickupType type);
void UpdatePickups(Pickups* pickups, float deltaTime);
void RenderPickups(Pickups* pickups, float currentTime, SDL_Renderer* renderer);
void DestroyPickups(Pickups* pickups);