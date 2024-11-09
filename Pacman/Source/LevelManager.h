#pragma once
#include "Core/Core.h"
#include "SDL_Wrapper.h"

typedef struct LevelManager LevelManager; 

typedef void (*functionPointer)(LevelManager*);
typedef void (*functionPointerFloat)(float, LevelManager*);

typedef enum {
    Playing, Stopped, End
}GameState;

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
    TTF_Font* font;
    int fontSize;
    GameState state;
    Vec2i watermarkLoc;
    SDL_Texture* watermark;
    float gameTime;
    SDL_Rect renderViewport;
};

void PrintCurrentConfiguration();
int IsGameRunning(LevelManager* manager);
void InitLevelManager(LevelManager* manager);
void LevelManager_SetNewLevel(LevelManager* manager, Level NewLevel);
void LevelManager_Update(LevelManager* manager, float deltaTime);
void LevelManager_Render(LevelManager* manager, float deltaTime);
void LevelManager_Destroy(LevelManager* manager);
void LevelManager_Cleanup(LevelManager* manager);