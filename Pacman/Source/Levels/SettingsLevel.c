#include "SettingsLevel.h"
#include "GameObjects/Text.h"

typedef struct {
	Text settingsTitle;
}SettingsData;

void SettingsLevel_Init(LevelManager* manager)
{
	manager->data = malloc(sizeof(SettingsData));
	PAC_ASSERT(manager && manager->data);
	SettingsData* leveldata = ((SettingsData*)manager->data);
	InitText(&(leveldata->settingsTitle), (SDL_Color) { 255, 255, 255, 255 }, "Settings (esc to close)", MENU_HEADER_LOCATION, manager);
}

void SettingsLevel_Update(float deltaTime, LevelManager* manager)
{
	PAC_ASSERT(manager && manager->data);
	SettingsData* leveldata = ((SettingsData*)manager->data);
	CheckReturnInput(manager);
}

void SettingsLevel_Render(float deltaTime, LevelManager* manager)
{
	PAC_ASSERT(manager && manager->data);
	SettingsData* leveldata = ((SettingsData*)manager->data);
	RenderText(&(leveldata->settingsTitle), manager->renderer);
}

void SettingsLevel_Destroy(LevelManager* manager)
{
	PAC_ASSERT(manager && manager->data);
	SettingsData* leveldata = ((SettingsData*)manager->data);
	DestroyText(&(leveldata->settingsTitle));
	free(manager->data);
	manager->data = NULL;
}
