#include <SDL2/SDL.h>
#include <stdlib.h>
#include "Core/Assert.h"
#include "Core/Log.h"
#include <SDL_image.h>
#include "SDL_Wrapper.h"
#include "LevelManager.h"
#include "Levels/TestLevel.h"

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

    GraphicsState graphicsState = {
    .windowTransform = { {SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED}, {800, 600} },
    .window = NULL,
    .renderer = NULL
    };

    SDLWrapper_Init("My SDL game", &graphicsState);

    /*
    LevelManager manager = { .currentLevel = NULL,.data = NULL };
    
    */
    /*
    void* x = malloc(sizeof(int));
    x = 5;
    PAC_LOG("%d", x);
    free(x);

    
    
    void* x = malloc(sizeof(int));
    *(int*)x = 5;    // Cast to int* before dereferencing
    PAC_LOG("%d", *(int*)x);
    free(x);
    */
    
    Level testLevel = { TestLevel_Init,TestLevel_Update,TestLevel_Render,TestLevel_Destroy };
    LevelManager manager = { .currentLevel= NULL,.data=NULL };
    SDL_Event event;
    
    LevelManager_SetNewLevel(&manager,testLevel);

    GameState state = Playing;
    while (state == Playing)
    {
        LevelManager_Update(&manager, 0.2f);
        LevelManager_Render(&manager, 0.2f);
        
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                LevelManager_Destroy(&manager);
                state = End;
            }
        }

        // Initialize SDL_image
        if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
            PAC_FATAL("SDL_image could not initialize! IMG_Error: %s\n", IMG_GetError());
            return 1;
        }

        // Render the image
        renderImage(graphicsState.renderer, "Resources/Sprites/TestImage.png"); // Change to your image path

    }
   
    SDLWrapper_Destroy(&graphicsState);
   
   return 0;
}