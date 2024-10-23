#include <SDL2/SDL.h>
#include "Core/Log.h"
#include "Core/Assert.h"
#include <stdio.h>


int main(int argc, char* argv[])
{
    if (SDL_Init(SDL_INIT_VIDEO)) {
        PAC_FATAL("SDL_Init Error: %s\n", SDL_GetError());
        return 1;
    }
    SDL_Window* window = SDL_CreateWindow("SDL experiments", 100, 100, 800, 600, SDL_WINDOW_SHOWN);
    if (!window) {
        PAC_FATAL("SDL_CreateWindow Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer) {
        SDL_DestroyWindow(window);
        PAC_FATAL("SDL_CreateRenderer Error: %s", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    int line_x = 100;

    SDL_Event event;
    int running = 1;

    while (running == 1)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                running = 0;
            }
        }

        line_x++;

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Nastavení barvy na èernou
        SDL_RenderClear(renderer);                      // Vykreslení pozadí

        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Nastavení barvy na èervenou
        SDL_RenderDrawLine(renderer, line_x, 50, line_x, 250); // Vykreslení èáry

        SDL_RenderPresent(renderer);  // Prezentace kreslítka
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}