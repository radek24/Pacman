#include "LevelManager.h"
#include "Levels/MainMenuLevel.h"

void PrintCurrentConfiguration()
{
#ifdef PAC_DEBUG
	PAC_LOG("Starting in debug configuration")
#elif PAC_DEVELOPMENT
	PAC_LOG("Starting in development configuration")
#elif PAC_SHIPPING
	PAC_LOG("Starting in shipping configuration")
#endif

#ifdef PLATFORM_WINDOWS
		PAC_LOG("Current platform is Windows")
#elif PLATFORM_LINUX
		PAC_LOG("Current platform is Linux")
#elif PLATFORM_MAC
		PAC_LOG("Current platform is Mac")
#endif

#ifdef LOG_USE_COLOR
		PAC_LOG("Logger configured to print with color. Disable by removing LOG_USE_COLOR from premake file");
#else
		PAC_LOG("Logger configured to print without color. Enable by defining LOG_USE_COLOR macro in premake file ")
#endif

#if defined(PAC_SHIPING) && defined(LOG_IN_SHIPPING)
		PAC_LOG("Logger configured to print in shipping. Disable by removing LOG_IN_SHIPPING from premake file");
#endif //Otherwise we can't log

}

int IsGameRunning(LevelManager* manager)
{
	return manager->state == Playing;
}

static void LoadFont(LevelManager* manager, const char* fontPath, int size)
{
	manager->font = TTF_OpenFont(fontPath, size);
	manager->fontSize = size;
	if (!manager->font) {
		PAC_FATAL("Font Load Error: %s\n", TTF_GetError());
		PAC_ASSERT(0);
	}
}

void InitLevelManager(LevelManager* manager)
{
	LoadFont(manager, "Resources/Fonts/PacFont.ttf", 16);
	manager->state = Playing;
	manager->watermarkLoc = (Vec2i){5,WINDOW_SIZE_Y-20 };
	manager->watermark = IMG_LoadTexture(manager->renderer, "Resources/Sprites/Watermark.png");
	manager->gameTime = 0.0f;
	manager->renderViewport = (SDL_Rect){ 0,0,WINDOW_SIZE_X,WINDOW_SIZE_Y };
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

void LevelManager_Update(LevelManager* manager, float deltaTime)
{
	manager->gameTime += deltaTime;
	manager->currentLevel.Update(deltaTime, manager);
}

void LevelManager_Render(LevelManager* manager, float deltaTime)
{
	SDL_RenderClear(manager->renderer);
	//SDL_RenderSetViewport(manager->renderer, &(manager->renderViewport));

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
