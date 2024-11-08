#pragma once

#include "Core/Core.h"
#include "SDL_Wrapper.h"

typedef struct {
	/*Lives are rendererd from right to left, so this is most right position!*/
	Vec2i pos;
	SDL_Texture* sprite;
	int currentLives;
}LivesDisplay;

void InitLivesDisplay(LivesDisplay* display,int lives, Vec2i pos, SDL_Renderer* renderer);
void UpdateLivesDisplay(LivesDisplay* display, int lives);
void RenderLivesDisplay(LivesDisplay* display, SDL_Renderer* renderer);
void DestroyLivesDisplay(LivesDisplay* display);