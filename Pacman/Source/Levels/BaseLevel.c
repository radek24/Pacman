#include "BaseLevel.h"
#include "Levels/MainMenuLevel.h"

void CheckReturnInput(LevelManager* manager)
{
	if (!manager->isInputActive) return;
	SDL_Event event = manager->inputEvent;
	if (event.type != SDL_KEYDOWN) return;

	switch (event.key.keysym.sym)
	{
	case SDLK_ESCAPE: {
		Level mainMenu = CONSTRUCT_LEVEL(MainMenuLevel);
		LevelManager_SetNewLevel(manager, mainMenu);
	}break;
	}
}
