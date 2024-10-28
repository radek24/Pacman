#pragma once
#include "Core/Core.h"
#include <stdlib.h>
#include "LevelManager.h"

#define CREATE_LEVEL_FUNCTIONS(level_name)\
    void level_name##_Init(LevelManager* manager);\
    void level_name##_Update(float deltaTime, LevelManager* manager);\
    void level_name##_Render(float deltaTime, LevelManager* manager);\
    void level_name##_Destroy(LevelManager* manager);\
    void level_name##_Destroy(LevelManager* manager);


void CheckReturnInput(LevelManager* manager);
