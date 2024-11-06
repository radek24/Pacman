#include "Settings.h"



static int FindIndex(int target, int arr[], int size) {
	for (int i = 0; i < size; i++) {
		if (arr[i] == target) {
			return i;
		}
	}
	return -1; 
}


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

void InitSetting(SettingsManager* settingManager,Setting* setting, char* settingName, char* iniName, int* options, int optionsNum, SettingPressedCallback handler, LevelManager* manager, int index)
{
	InitText(&(setting->text), (SDL_Color) { 255, 255, 255 }, settingName, (Vec2i) { TILE_SIZE * 3, TILE_SIZE* (5 + (index * 2)) }, manager);
	
	char str[20];
	int number;
	ini_file_find_integer(settingManager->settingFile, SETTINGS_SECTION_NAME, iniName, &number);
	
	itoa(options[FindIndex(number, options, optionsNum)], str, 10);
	InitText(&(setting->currValue), (SDL_Color) { 255, 255, 255 }, str, (Vec2i) { TILE_SIZE * 23, TILE_SIZE* (5 + (index * 2)) }, manager);
	setting->currentOption = FindIndex(number, options, optionsNum);
	strcpy(setting->iniName, iniName);

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
	InitSetting(settingsManager,&(settingsManager->settings[settingsManager->size]), settingName,iniName, options, optionsNum, handler,manager, settingsManager->size);
	settingsManager->size++;
}

void UpdateSettings(SettingsManager* settingsManager, LevelManager* manager)
{
	if (!manager->isInputActive) return;
	SDL_Event event = manager->inputEvent;
	if (event.type != SDL_KEYDOWN) return;


	Setting* currentSetting =&(settingsManager->settings[settingsManager->currentActive]);
	Setting* allSettings = (settingsManager->settings);
	
	switch (event.key.keysym.sym)
	{
		
	case SDLK_UP: {
		char c[128];
		int nextIndex = ((settingsManager->currentActive - 1) % settingsManager->size + settingsManager->size) % settingsManager->size;
		strcpy(c, (currentSetting)->text.text);
		memcpy(c, "  ", 2);
		UpdateText(&(currentSetting->text), c, manager);
		strcpy(c, (allSettings[nextIndex]).text.text);
		memcpy(c, "> ", 2);
		UpdateText(&((allSettings[nextIndex]).text), c, manager);
		settingsManager->currentActive = nextIndex;
	}break;
	case SDLK_DOWN: {
		char c[128];
		strcpy(c, (currentSetting)->text.text);
		memcpy(c, "  ", 2);
		UpdateText(&(currentSetting->text), c, manager);
		strcpy(c, (allSettings[(settingsManager->currentActive + 1) % (settingsManager->size )]).text.text);
		memcpy(c, "> ", 2);
		UpdateText(&((allSettings[(settingsManager->currentActive + 1) % (settingsManager->size )]).text), c, manager);
		settingsManager->currentActive = (settingsManager->currentActive + 1) % (settingsManager->size);
	}break;
	case SDLK_LEFT: {
		currentSetting->currentOption = ((currentSetting->currentOption - 1) % currentSetting->optionsNum + currentSetting->optionsNum) % currentSetting->optionsNum;
		UpdateSettingChoise(settingsManager, currentSetting, manager);
		
	}break;
	case SDLK_RIGHT: {
		currentSetting->currentOption = ((currentSetting->currentOption + 1) % currentSetting->optionsNum + currentSetting->optionsNum) % currentSetting->optionsNum;
		UpdateSettingChoise(settingsManager, currentSetting, manager);
	}break;			  
	}

}

void UpdateSettingChoise(SettingsManager* settingsManager, Setting* currentSetting, LevelManager* manager)
{
	char c[128];
	sprintf(c, "%d", currentSetting->options[currentSetting->currentOption]);
	UpdateText(&(currentSetting->currValue), c, manager);
	currentSetting->callback(manager,currentSetting->options[currentSetting->currentOption]);
	Ini_File_Error err=0;
	err = ini_file_add_property(settingsManager->settingFile, currentSetting->iniName, c);
}

void DrawSettings(SettingsManager* manager, SDL_Renderer* renderer)
{
	for (int i = 0; i < manager->size; i++)
	{
		RenderText(&(manager->settings[i].text), renderer);
		RenderText(&(manager->settings[i].currValue), renderer);
	}
}

void DestroySettings(SettingsManager* manager)
{
	remove(SETTINGS_FILE_NAME);


	ini_file_save(manager->settingFile, SETTINGS_FILE_NAME);
	ini_file_free(manager->settingFile);
	for (int i = 0; i < manager->size; i++)
	{	
		DestroyText(&(manager->settings[i].text));
		DestroyText(&(manager->settings[i].currValue));
	}
	free(manager->settings);
	manager->settings = NULL;
}
