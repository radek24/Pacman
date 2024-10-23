#include <SDL2/SDL.h>
#include "Core/Log.h"
#include "Core/Assert.h"
#include <stdio.h>

#include <SDL_image.h>

void renderImage(SDL_Renderer* renderer, const char* filePath) {
    SDL_Texture* texture = IMG_LoadTexture(renderer, filePath);
    if (texture == NULL) {
        PAC_WARN("Failed to load texture! IMG_Error: %s\n", IMG_GetError());
        return;
    }

    // Clear the screen
    SDL_RenderClear(renderer);

    // Copy the texture to the renderer
    SDL_RenderCopy(renderer, texture, NULL, NULL);

    // Present the backbuffer
    SDL_RenderPresent(renderer);

    // Cleanup
    SDL_DestroyTexture(texture);
}

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

        // Initialize SDL_image
        if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
            printf("SDL_image could not initialize! IMG_Error: %s\n", IMG_GetError());
            return 1;
        }

        // Render the image
        renderImage(renderer, "Resources/Sprites/TestImage.png"); // Change to your image path

    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}