#include "SDL_Wrapper.h"


void SDLWrapper_Init(const char* windowName, GraphicsState* state)
{
    if (SDL_Init(SDL_INIT_VIDEO)) {
        PAC_FATAL("SDL_Wrapper: SDL_Init Error: %s\n", SDL_GetError());
        return;
    }
    state->window = SDL_CreateWindow(windowName, state->windowTransform.position.x, state->windowTransform.position.y, state->windowTransform.size.x, state->windowTransform.size.y, SDL_WINDOW_SHOWN);
    if (state->window == NULL) {
        PAC_FATAL("SDL_Wrapper: SDL_CreateWindow Error: %s\n", SDL_GetError());
        SDL_Quit();
        return;
    }

    state->renderer = SDL_CreateRenderer((state->window), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (state->renderer == NULL) {
        SDL_DestroyWindow(state->window);
        PAC_FATAL("SDL_Wrapper: SDL_CreateRenderer Error: %s", SDL_GetError());
        SDL_Quit();
        return;
    }

    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        PAC_FATAL("SDL_Wrapper: SDL_image could not initialize! IMG_Error: %s\n", IMG_GetError());
        return;
    }
    SDL_SetRenderDrawBlendMode(state->renderer, SDL_BLENDMODE_BLEND);
    PAC_LOG("SDL_Wrapper: Sucesfully initialized SDL");
    PAC_LOG("SDL_Wrapper: Sucesfully initialized SDL image");
}

void SDLWrapper_Destroy(GraphicsState* state) {
    SDL_DestroyRenderer(state->renderer);
    SDL_DestroyWindow(state->window);
    SDL_Quit();
    PAC_LOG("SDL_Wrapper: Sucesfully destroyed SDL");
}
