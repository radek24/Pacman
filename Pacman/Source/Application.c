#include <stdlib.h>
#include "SDL_Wrapper.h"
#include "Core/Core.h"
#include "LevelManager.h"
#include "Levels/GameLevel.h"
#include "Levels/MainMenuLevel.h"

#include "ini/ini_file.h"

int main()
{
    PrintCurrentConfiguration();
    
    GraphicsState graphicsState = {
    .windowTransform = { {SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED}, {WINDOW_SIZE_X, WINDOW_SIZE_Y} },
    .window = NULL,
    .renderer = NULL
    };
    SDLWrapper_Init("Pacman", &graphicsState);
    
    LevelManager manager = {
        .currentLevel= NULL,
        .data=NULL,
        .renderer=graphicsState.renderer,
        .inputEvent=0,
        .isInputActive =0
    };

    InitLevelManager(&manager);
    
    Level mainMenu = CONSTRUCT_LEVEL(MainMenuLevel);
    LevelManager_SetNewLevel(&manager, mainMenu);

    Uint32 lastTick = SDL_GetTicks();
    float deltaTime = 0.0f;
    while (IsGameRunning(&manager))
    {
        Uint32 currentTick = SDL_GetTicks();
        deltaTime = (currentTick - lastTick) / 1000.0f;

        manager.isInputActive = SDL_PollEvent(&(manager.inputEvent));
        if (manager.isInputActive && manager.inputEvent.type == SDL_QUIT)manager.state = End;

        LevelManager_Update(&manager, deltaTime);
        LevelManager_Render(&manager, deltaTime);
        
        lastTick = currentTick;
    }
    PAC_LOG("Requested quit, destroying game...")
    LevelManager_Destroy(&manager);
    LevelManager_Cleanup(&manager);
    SDLWrapper_Destroy(&graphicsState);
    return 0;
}