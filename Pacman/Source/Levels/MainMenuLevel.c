#include "MainMenuLevel.h"
#include "GameObjects/Button.h"
#include "Levels/GameLevel.h"

#define NUM_BUTTONS 6

typedef struct {
	float gameTime;
	Button mainMenuButtons[NUM_BUTTONS];
	//Just so I dont have to write sizeof everywhere, array is stack alocated anyway, so the size wont change
	int numberOfButtons;

}MainMenuData;

void StartPressed(LevelManager* manager) {
	Level gameLevel = { GameLevel_Init,GameLevel_Update,GameLevel_Render,GameLevel_Destroy };
	LevelManager_SetNewLevel(manager, gameLevel);
}
void LeaderboardsPressed(LevelManager* manager) {

}
void SettingsPressed(LevelManager* manager) {

}
void ControlsPressed(LevelManager* manager) {

}
void CreditsPressed(LevelManager* manager) {

}
void QuitPressed(LevelManager* manager) {
	manager->state = End;
}

void MainMenuLevel_Init(LevelManager* manager)
{
	manager->data = malloc(sizeof(MainMenuData));
	PAC_ASSERT(manager && manager->data);
	MainMenuData* leveldata = ((MainMenuData*)manager->data);

	InitButton(&(leveldata->mainMenuButtons[0]), "> Start game", (SDL_Color) { 255, 255, 255, 255 }, (Vec2i) { TILE_SIZE * 3, TILE_SIZE * 5 }, manager, StartPressed);
	AppendButton(&(leveldata->mainMenuButtons[1]), &(leveldata->mainMenuButtons[0]), "  Leaderboards", manager,LeaderboardsPressed);
	AppendButton(&(leveldata->mainMenuButtons[2]), &(leveldata->mainMenuButtons[1]), "  Settings", manager,SettingsPressed);
	AppendButton(&(leveldata->mainMenuButtons[3]), &(leveldata->mainMenuButtons[2]), "  Controls", manager,ControlsPressed);
	AppendButton(&(leveldata->mainMenuButtons[4]), &(leveldata->mainMenuButtons[3]), "  Credits", manager,CreditsPressed);
	AppendButton(&(leveldata->mainMenuButtons[5]), &(leveldata->mainMenuButtons[4]), "  Quit", manager, QuitPressed);

	// Link up unlinked buttons
	leveldata->mainMenuButtons[0].nextButton = &(leveldata->mainMenuButtons[1]);
	leveldata->mainMenuButtons[0].previousButton = &(leveldata->mainMenuButtons[5]);
	leveldata->mainMenuButtons[5].nextButton = &(leveldata->mainMenuButtons[0]);

	leveldata->numberOfButtons = NUM_BUTTONS;
	leveldata->mainMenuButtons[0].state = selected;
}

void MainMenuLevel_Update(float deltaTime, LevelManager* manager)
{
	PAC_ASSERT(manager && manager->data);
	MainMenuData* leveldata = ((MainMenuData*)manager->data);
	
	leveldata->gameTime += deltaTime;
	int tmp;
	for (short i = 0; i < NUM_BUTTONS; i++)
	{
		tmp = leveldata->mainMenuButtons[i].state;
		UpdateButton(&(leveldata->mainMenuButtons[i]), manager);
		if (tmp != leveldata->mainMenuButtons[i].state)break;
	}
}

void MainMenuLevel_Render(float deltaTime, LevelManager* manager)
{
	PAC_ASSERT(manager && manager->data);
	MainMenuData* leveldata = ((MainMenuData*)manager->data);
	for (short i = 0; i < NUM_BUTTONS; i++)
	{
		RenderButton(&(leveldata->mainMenuButtons[i]), manager->renderer);
	}
}

void MainMenuLevel_Destroy(LevelManager* manager)
{
	PAC_ASSERT(manager && manager->data);
	MainMenuData* leveldata = ((MainMenuData*)manager->data);
	
	for (short i = 0; i < NUM_BUTTONS; i++)
	{
		DestroyButton(&(leveldata->mainMenuButtons[i]), manager->renderer);
	}
	free(manager->data);
	manager->data = NULL;
}
