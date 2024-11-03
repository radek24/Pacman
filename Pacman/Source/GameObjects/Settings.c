#include "Settings.h"




void InitSettingsManager(SettingsManager* manager)
{
	manager->size = 0;
	manager->capacity = 4;
	manager->settings = (Setting*)malloc(sizeof(Setting) * manager->capacity);
	manager->currentActive = 0;

	/*Setting file is needed as it has all the defaults. If the file cannot be found, we kill the program*/
	manager->settingFile = ini_file_parse(SETTINGS_FILE_NAME, LogErrorCallback);
	PAC_ASSERT(manager->settingFile);
	PAC_LOG("Setting file opened sucesfully");
}

void InitSetting(Setting* setting, char* settingName, char* iniName, int* options, int optionsNum, SettingPressedCallback handler, LevelManager* manager, int index)
{
	InitText(&(setting->text), (SDL_Color) { 255, 255, 255 }, settingName, (Vec2i) { TILE_SIZE * 3, TILE_SIZE* (5 + (index * 2)) }, manager);
	setting->callback = handler;
	memcpy(setting->options, options, optionsNum * sizeof(int));
	setting->optionsNum = optionsNum;
	
}

void AppendSetting(SettingsManager* settingsManager, char* settingName, char* iniName, int options[], int optionsNum, SettingPressedCallback handler, LevelManager* manager)
{
	if (settingsManager->size == settingsManager->capacity) {
		settingsManager->capacity *= 2;
		Setting* tmp = (Setting*)realloc(settingsManager->settings, sizeof(Setting) * settingsManager->capacity);
		PAC_ASSERT(tmp);
		settingsManager->settings = tmp;
		PAC_LOG("Realloc settings to %d", settingsManager->capacity);
	}
	InitSetting(&(settingsManager->settings[settingsManager->size]), settingName,iniName, options, optionsNum, handler,manager, settingsManager->size);
	settingsManager->size++;
}

void DrawSettings(SettingsManager* manager, SDL_Renderer* renderer)
{
	for (int i = 0; i < manager->size; i++)
	{
		RenderText(&(manager->settings[i].text), renderer);
	}
}

void DestroySettings(SettingsManager* manager)
{
	PAC_WARN("NO destroy event in settings");
}
