#include "LevelManager.h"

void LevelManager_SetNewLevel(LevelManager* manager, Level NewLevel)
{
	PAC_LOG("Initializing new level...");
	if (manager->currentLevel.destroy != NULL)
	{
		PAC_LOG("Previous level destroyed");
		manager->currentLevel.destroy(manager);
	}
	manager->currentLevel = NewLevel;
	manager->currentLevel.Initialize(manager);
	PAC_LOG("New level initialized sucesfully");
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
	PAC_LOG("Destroying current level...");
	manager->currentLevel.destroy(manager);
	PAC_LOG("New level destroyed sucesfully");
}
