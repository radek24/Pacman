#pragma once

#include "Core/Core.h"
#include "GameObjects/Player.h"
#include "SDL_Wrapper.h"

typedef struct {
	/*Lives are rendererd from right to left, so this is most right position!*/
	Vec2i pos;
	SDL_Texture* sprite;

}LivesDisplay;

void InitLivesDisplay(LivesDisplay* display, Vec2i pos, SDL_Renderer* renderer);
void RenderLivesDisplay(LivesDisplay* display, SDL_Renderer* renderer,Player* player);
void DestroyLivesDisplay(LivesDisplay* display);