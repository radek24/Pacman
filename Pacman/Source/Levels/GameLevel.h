#pragma once

#include "BaseLevel.h"

void GameLevel_Init(LevelManager* data);
void GameLevel_Update(float deltaTime, LevelManager* data);
void GameLevel_Render(float deltaTime, LevelManager* data);
void GameLevel_Destroy(LevelManager* data);