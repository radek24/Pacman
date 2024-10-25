#pragma once
#include "../Core/Core.h"
#include "../SDL_Wrapper.h"

typedef enum {Score,Big,Cherry}PickupType;
typedef enum {normal,picked}PickupState;

typedef struct
{
	PickupType type;
	PickupState state;
	Vec2i positionInGrid;
	int size;
}Pickupable;


void InitPickup(Pickupable* pickup, SDL_Renderer* renderer, Vec2i* Pos);
void UpdatePickup(Pickupable* pickup, float deltaTime);
void RenderPickup(Pickupable* pickup, float currentTime, SDL_Renderer* renderer);
void DestroyPickup(Pickupable* pickup);