#include "Sprite.h"

void InitSprite(Sprite* sprite, const char* path, Vec2i size, Vec2i pos, SDL_Renderer* renderer)
{
	sprite->texture = IMG_LoadTexture(renderer, path);
	if (sprite->texture == NULL) { PAC_FATAL("Failed to load texture! IMG_Error: %s\n", IMG_GetError()); PAC_ASSERT(0); }
	sprite->position = pos;
	sprite->size = size;
}

void RenderSprite(Sprite* sprite, SDL_Renderer* renderer)
{
	PAC_ASSERT(sprite->texture);
	SDL_Rect position = { sprite->position.x,sprite->position.y,sprite->size.x,sprite->size.y };
	SDL_RenderCopy(renderer, sprite->texture, NULL, &position);
}

void DestroySprite(Sprite* sprite)
{
	SDL_DestroyTexture(sprite->texture);
}
