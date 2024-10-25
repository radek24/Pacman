#pragma once
#include "Math.h"
#include "../SDL_Wrapper.h"

typedef struct {
	char sprite[128];
	Rect2Di transform;
}SpriteComponent;

typedef enum{Blinky,Pinky,Inky,Clyde}GhostType;


void RenderSprite(SpriteComponent* sprite, SDL_Renderer* renderer);
