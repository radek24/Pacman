#include "LeaderboardLevel.h"
#include "ini/ini_file.h"
#include <stdio.h>
#include <stdlib.h>
#include "Levels/MainMenuLevel.h"
#include "GameObjects/Text.h"

//TODORADEK: This struct will allocate text even if not displayed, try to figure something out.
typedef struct {
	int score;
	Text text;
}LeaderboardStat;

typedef struct {
	size_t statsSize;
	size_t statsCapacity;
	LeaderboardStat* stats;
	struct Ini_File* iniFile;
	Text leaderboardTitle;
	Text leaderboardEmpty;
}LeaderboardData;

int compareStats(const void* a, const void* b) {
	LeaderboardStat* statA = (LeaderboardStat*)a;
	LeaderboardStat* statB = (LeaderboardStat*)b;
	return statB->score - statA->score;  // Descending order
}
void sortLeaderboard(LeaderboardStat* stats, size_t statsSize) {
	qsort(stats, statsSize, sizeof(LeaderboardStat), compareStats);
}

void LeaderboardLevel_Init(LevelManager* manager)
{
	manager->data = malloc(sizeof(LeaderboardData));
	PAC_ASSERT(manager && manager->data);
	LeaderboardData* leveldata = ((LeaderboardData*)manager->data);
	InitText(&(leveldata->leaderboardTitle), (SDL_Color) { 255, 255, 255, 255 }, "Leaderboards (esc to close)", MENU_HEADER_LOCATION, manager);
	InitText(&(leveldata->leaderboardEmpty), (SDL_Color) { 150, 150, 150, 255 }, "No data", (Vec2i) { TILE_SIZE * 5, TILE_SIZE * 5 }, manager);

	leveldata->statsCapacity = 8;
	leveldata->statsSize = 0;
	leveldata->stats = malloc(sizeof(LeaderboardStat)*leveldata->statsCapacity);

	FILE* file = fopen(LEADERBOARD_FILENAME, "r");
	if (file != NULL) {
		fclose(file);
	}
	else
	{
		PAC_LOG("Leaderboard file doesn't exits, creating new one");
		leveldata->iniFile = ini_file_new();
		ini_file_add_section(leveldata->iniFile, LEADERBORDS_SECTION);
		ini_file_save(leveldata->iniFile, LEADERBOARD_FILENAME);
		ini_file_free(leveldata->iniFile);
	}
	
	leveldata->iniFile = ini_file_parse(LEADERBOARD_FILENAME, LogErrorCallback);
	PAC_ASSERT(leveldata->iniFile);
	PAC_LOG("Log file opened sucesfully");
	
	//We hope this is correct section
	PAC_ASSERT(leveldata->iniFile->sections_size == 1);
	Ini_Section* section = &(leveldata->iniFile->sections[0]);
	for (size_t property_index = 0; property_index < section->properties_size; property_index++) {
		
		leveldata->statsSize++;
		if (leveldata->statsSize >= leveldata->statsCapacity) {
			leveldata->statsCapacity *= 2;
			LeaderboardStat* tmp = (LeaderboardStat*)realloc(leveldata->stats, sizeof(LeaderboardStat) * leveldata->statsCapacity);
			PAC_ASSERT(tmp);
			leveldata->stats = tmp;
			PAC_LOG("Realloc stats to %d", leveldata->statsCapacity);
		}
		Key_Value_Pair* property = &section->properties[property_index];
		
		int value = atoi(property->value);
		leveldata->stats[property_index].score = value;
		SDL_Color color = {255,255,255,255};
		char buff[256];
		sprintf(buff, "%s: %s", property->key, property->value);
		InitText(&(leveldata->stats[property_index].text), color, buff, (Vec2i) { 100, 100 }, manager);
	}
	PAC_LOG("Read %d stats from %s stat file", leveldata->statsSize, LEADERBOARD_FILENAME);

	sortLeaderboard(leveldata->stats, leveldata->statsSize);
	for (size_t i = 0; i < min(leveldata->statsSize, 3); i++)
	{
		if (i == 0) { UpdateTextColor(&(leveldata->stats[i].text), (SDL_Color) { 252, 171, 8, 255 }, manager); }
		else if (i == 1) { UpdateTextColor(&(leveldata->stats[i].text), (SDL_Color) { 192, 192, 192, 255 }, manager); }
		else if (i == 2) { UpdateTextColor(&(leveldata->stats[i].text), (SDL_Color) { 205, 127, 50, 255 }, manager); }
	}
}

void LeaderboardLevel_Update(float deltaTime, LevelManager* manager)
{
	PAC_ASSERT(manager && manager->data);
	LeaderboardData* leveldata = ((LeaderboardData*)manager->data);
	CheckReturnInput(manager);
}

void LeaderboardLevel_Render(float deltaTime, LevelManager* manager)
{
	PAC_ASSERT(manager && manager->data);
	LeaderboardData* leveldata = ((LeaderboardData*)manager->data);
	if (leveldata->statsSize == 0)RenderText(&(leveldata->leaderboardEmpty), manager->renderer);
	for (int i = 0; i < min(leveldata->statsSize,8); i++)
	{
		leveldata->stats[i].text.location = (Vec2i){ TILE_SIZE * 5, TILE_SIZE * 5 + ((TILE_SIZE * 2) * i) };
		RenderText(&(leveldata->stats[i].text), manager->renderer);
	}
	RenderText(&(leveldata->leaderboardTitle), manager->renderer);
}

void LeaderboardLevel_Destroy(LevelManager* manager)
{
	PAC_ASSERT(manager && manager->data);
	LeaderboardData* leveldata = ((LeaderboardData*)manager->data);

	for (int i = 0; i < leveldata->statsSize; i++)
	{
		DestroyText(&(leveldata->stats[i].text));
	}
	DestroyText(&(leveldata->leaderboardTitle));
	DestroyText(&(leveldata->leaderboardEmpty));
	ini_file_free(leveldata->iniFile);
	leveldata->iniFile = NULL;
	free(leveldata->stats);
	leveldata->stats = NULL;
	free(manager->data);
	manager->data = NULL;
	PAC_LOG("Leaderboard file closed sucesfully");
}
