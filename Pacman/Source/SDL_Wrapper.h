#pragma once
#include <SDL2/SDL.h>
#include "Core/Core.h"
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "LevelManager.h"

typedef struct {
	Rect2Di windowTransform;
	SDL_Window* window;
	SDL_Renderer* renderer;
}GraphicsState;

void SDLWrapper_Init(const char* windowName, GraphicsState* state);
void SDLWrapper_Destroy(GraphicsState* state);
