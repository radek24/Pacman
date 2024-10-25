
#include "SDL_Wrapper.h"
#include <SDL_image.h>
#include "Core/Core.h"
#include "LevelManager.h"
#include "Levels/TestLevel.h"
#include "GameObjects/GameObjects.h"


int main(int argc, char* argv[])
{
    GraphicsState graphicsState = {
    .windowTransform = { {SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED}, {WINDOW_SIZE_X, WINDOW_SIZE_Y} },
    .window = NULL,
    .renderer = NULL
    };
    SDLWrapper_Init("Pacman", &graphicsState);
    
    Level testLevel = { TestLevel_Init,TestLevel_Update,TestLevel_Render,TestLevel_Destroy };
    LevelManager manager = { .currentLevel= NULL,.data=NULL,.renderer=graphicsState.renderer ,.inputEvent=NULL,.isInputActive =0};
    
    LevelManager_SetNewLevel(&manager,testLevel);

    GameState state = Playing;
    Uint32 lastTick = SDL_GetTicks();
    float deltaTime = 0.0f;
    while (state == Playing)
    {
        Uint32 currentTick = SDL_GetTicks();
        deltaTime = (currentTick - lastTick) / 1000.0f;

        manager.isInputActive = SDL_PollEvent(&(manager.inputEvent));
        if (manager.isInputActive && manager.inputEvent.type == SDL_QUIT)state = End;

        LevelManager_Update(&manager, deltaTime);
        LevelManager_Render(&manager, deltaTime);
        
        lastTick = currentTick;
    }
    LevelManager_Destroy(&manager);
    SDLWrapper_Destroy(&graphicsState);
   
    return 0;
}