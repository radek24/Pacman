#pragma once
#include "Core/Core.h"


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
};


void LevelManager_SetNewLevel(LevelManager* manager, Level NewLevel);
void LevelManager_Update(LevelManager* manager, float deltaTime);
void LevelManager_Render(LevelManager* manager, float deltaTime);
void LevelManager_Destroy(LevelManager* manager);