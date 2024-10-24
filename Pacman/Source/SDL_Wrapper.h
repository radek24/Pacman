#pragma once
#include <SDL2/SDL.h>
#include "Core/Math.h"

typedef struct {
	Rect2Di windowTransform;
	SDL_Window* window;
	SDL_Renderer* renderer;
}GraphicsState;

typedef enum {
	Playing,Stopped,End
}GameState;


void SDLWrapper_Init(const char* windowName, GraphicsState* state);
void SDLWrapper_Destroy(GraphicsState* state);
