#include "SettingsLevel.h"
#include "GameObjects/Text.h"
#include "GameObjects/Settings.h"

typedef struct {
	Text title;
	SettingsManager settingManager;
}SettingsData;

void GenericCallback(LevelManager* manager, int current) {
	PAC_LOG("Canged setting to %d", current);
}

void SettingsLevel_Init(LevelManager* manager)
{
	manager->data = malloc(sizeof(SettingsData));
	PAC_ASSERT(manager && manager->data);
	SettingsData* leveldata = ((SettingsData*)manager->data);
	InitText(&(leveldata->title), (SDL_Color) { 255, 255, 255, 255 }, "Settings (esc to close)", MENU_HEADER_LOCATION, manager);
	InitSettingsManager(&(leveldata->settingManager));
	int volumeOptions[11] = { 0,1,2,3,4,5,6,7,8,9 };
	AppendSetting(&(leveldata->settingManager), "> Music volume", "MusicVolume", volumeOptions, 11, GenericCallback,manager);
	AppendSetting(&(leveldata->settingManager), "  Effects volume", "EffectVolume", volumeOptions, 11, GenericCallback, manager);
	int livesOptions[11] = { 1,2,3,4,5,6 };
	AppendSetting(&(leveldata->settingManager), "  Starting lives", "StartingLives", livesOptions, 6, GenericCallback, manager);
}

void SettingsLevel_Update(float deltaTime, LevelManager* manager)
{
	PAC_ASSERT(manager && manager->data);
	SettingsData* leveldata = ((SettingsData*)manager->data);
	CheckReturnInput(manager);
	UpdateSettings(&(leveldata->settingManager), manager);
}

void SettingsLevel_Render(float deltaTime, LevelManager* manager)
{
	PAC_ASSERT(manager && manager->data);
	SettingsData* leveldata = ((SettingsData*)manager->data);
	RenderText(&(leveldata->title), manager->renderer);
	DrawSettings(&(leveldata->settingManager), manager->renderer);
}

void SettingsLevel_Destroy(LevelManager* manager)
{
	PAC_ASSERT(manager && manager->data);
	SettingsData* leveldata = ((SettingsData*)manager->data);
	DestroySettings(&(leveldata->settingManager));
	DestroyText(&(leveldata->title));
	free(manager->data);
	manager->data = NULL;
}
