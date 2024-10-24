#include "SDL_Wrapper.h"
#include "Core/Log.h"


void SDLWrapper_Init(const char* windowName, GraphicsState* state)
{
    if (SDL_Init(SDL_INIT_VIDEO)) {
        PAC_FATAL("SDL_Init Error: %s\n", SDL_GetError());
    }
    state->window = SDL_CreateWindow(windowName, state->windowTransform.position.x, state->windowTransform.position.y, state->windowTransform.size.x, state->windowTransform.size.y, SDL_WINDOW_SHOWN);
    if (state->window == NULL) {
        PAC_FATAL("SDL_CreateWindow Error: %s\n", SDL_GetError());
        SDL_Quit();
    }

    state->renderer = SDL_CreateRenderer((state->window), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (state->renderer == NULL) {
        SDL_DestroyWindow(state->window);
        PAC_FATAL("SDL_CreateRenderer Error: %s", SDL_GetError());
        SDL_Quit();
    }

}

void SDLWrapper_Destroy(GraphicsState* state) {
    SDL_DestroyRenderer(state->renderer);
    SDL_DestroyWindow(state->window);
    SDL_Quit();
}
