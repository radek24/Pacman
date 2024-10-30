#pragma once

#include "Core/Core.h"
#include "SDL_Wrapper.h"


typedef struct {
	SDL_Texture* texture;
	Vec2i size;
	Vec2i position;
}Sprite;

void InitSprite(Sprite* sprite,const char* path,Vec2i size, Vec2i pos, SDL_Renderer* renderer);
void RenderSprite(Sprite* sprite, SDL_Renderer* renderer);
void DestroySprite(Sprite* sprite);