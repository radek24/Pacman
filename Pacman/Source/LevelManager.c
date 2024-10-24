#include "LevelManager.h"

void LevelManager_SetNewLevel(LevelManager* manager, Level NewLevel)
{
	if (manager->currentLevel.destroy != NULL)
	{
		manager->currentLevel.destroy(manager);
	}
	
	manager->currentLevel = NewLevel;
	manager->currentLevel.Initialize(manager);
}


void LevelManager_Update(LevelManager* manager,float deltaTime)
{
	manager->currentLevel.Update(deltaTime, manager);
}

void LevelManager_Render(LevelManager* manager, float deltaTime)
{
	manager->currentLevel.Render(deltaTime, manager);
}

void LevelManager_Destroy(LevelManager* manager)
{
	manager->currentLevel.destroy(manager);
}
