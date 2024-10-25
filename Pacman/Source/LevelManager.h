#pragma once
#include "Core/Core.h"
#include <SDL2/SDL.h>

typedef struct LevelManager LevelManager; 

typedef void (*functionPointer)(LevelManager*);
typedef void (*functionPointerFloat)(float, LevelManager*);

typedef struct {
    functionPointer Initialize;
    functionPointerFloat Update;
    functionPointerFloat Render;
    functionPointer destroy;
} Level;

struct LevelManager {  
    Level currentLevel;
    void* data;
    SDL_Renderer* renderer;
    SDL_Event inputEvent;
    int isInputActive;
};


void LevelManager_SetNewLevel(LevelManager* manager, Level NewLevel);
void LevelManager_Update(LevelManager* manager, float deltaTime);
void LevelManager_Render(LevelManager* manager, float deltaTime);
void LevelManager_Destroy(LevelManager* manager);