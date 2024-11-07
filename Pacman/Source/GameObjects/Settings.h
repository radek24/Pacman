#pragma once
#include "GameObjects/Text.h"
#include "Core/Core.h"
#include "ini/ini_file.h"

/*
Settings system
Limitations - Settins can be only edited from setting level
            - Settins manager "object" can be only acessesed in settign level
            - If anyone wants to acess settings from elsewhere there are some functions provided in core.h

*/


#define SETTINGS_FILE_NAME "Resources/Config/Settings.ini"
#define SETTINGS_SECTION_NAME "Settings"


typedef void (*SettingPressedCallback)(LevelManager*, int);

typedef struct  {
    Text text;
    Text currValue;
    /* TODORADEK: Make this dynamic!*/
    char iniName[64];
    int options[50];
    int optionsNum;
    int currentOption;
    /* Do not handle config, this is only for applying those settings*/
    SettingPressedCallback callback;
}Setting;

typedef struct  {
    Setting* settings;
    size_t size;
    size_t capacity;
    size_t currentActive;
    Ini_File* settingFile;
}SettingsManager;

void InitSettingsManager(SettingsManager* settingsManager);
void InitSetting(SettingsManager* settingManager,Setting* setting, char* settingName, char* iniName, int* options, int optionsNum, SettingPressedCallback handler, LevelManager* manager, int index);
void AppendSetting(SettingsManager* settingsManager, char* settingName,char* iniName,int options[], int optionsNum, SettingPressedCallback handler, LevelManager* manager);
void UpdateSettings(SettingsManager* settingsManager, LevelManager* manager);
void UpdateSettingChoise(SettingsManager* settingsManager, Setting* currentSetting, LevelManager* manager);
void DrawSettings(SettingsManager* manager, SDL_Renderer* renderer);
void DestroySettings(SettingsManager* manager);
