#include "LevelManager.h"

void InitLevelManager(LevelManager* manager, const char* fontPath, int size)
{
	manager->font = TTF_OpenFont(fontPath, size);
	manager->fontSize = size;
	if (!manager->font) {
		PAC_FATAL("Font Load Error: %s\n", TTF_GetError());
		PAC_ASSERT(0);
	}
	manager->state = Playing;
	manager->watermarkLoc = (Vec2i){5,WINDOW_SIZE_Y-20 };
	manager->watermark = IMG_LoadTexture(manager->renderer, "Resources/Sprites/Watermark.png");
}

void LevelManager_SetNewLevel(LevelManager* manager, Level NewLevel)
{
	if (manager->currentLevel.destroy != NULL)
	{
		PAC_LOG("Destroying current level...");
		manager->currentLevel.destroy(manager);
		PAC_LOG("Current level destroyed");
	}
	PAC_LOG("Initializing new level...");
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
	SDL_RenderClear(manager->renderer);
	manager->currentLevel.Render(deltaTime, manager);

	SDL_Rect dstrect = { manager->watermarkLoc.x, manager->watermarkLoc.y,181 ,17  };
	SDL_RenderCopy(manager->renderer, manager->watermark, NULL, &dstrect);
	SDL_RenderPresent(manager->renderer);
}

void LevelManager_Destroy(LevelManager* manager)
{
	PAC_LOG("Destroying current level...");
	manager->currentLevel.destroy(manager);
	PAC_LOG("Current level destroyed sucesfully");
}
void LevelManager_Cleanup(LevelManager* manager) {
	
	if(manager->font)
	TTF_CloseFont(manager->font);
	manager->font = NULL;
	PAC_LOG("Destroyed loaded font");
	SDL_DestroyTexture(manager->watermark);

	PAC_LOG("Level manager closed");
}
