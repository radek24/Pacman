#include "WinLevel.h"
#include "GameLevel.h"
#include "GameObjects/Text.h"

typedef struct
{
	Text youWonTitle;
	Text currentScoreText;
	Text pressEnterText;
} WinData;

void WinLevel_Init(LevelManager* manager)
{
	manager->data = malloc(sizeof(WinData));
	PAC_ASSERT(manager && manager->data);
	WinData* leveldata = ((WinData*)manager->data);
	InitText(&(leveldata->youWonTitle), (SDL_Color) { 255, 255, 255, 255 }, "Level cleared sucesfully!", ((Vec2i) {16 * 2, 16 * 2}), manager);
	
	char scoreString[50];
	sprintf(scoreString, "Score = %d", manager->currentScore);
	InitText(&(leveldata->currentScoreText), (SDL_Color) { 255, 255, 255, 255 }, scoreString, ((Vec2i) {16 * 2, 16 * 4}), manager);
	InitText(&(leveldata->pressEnterText), (SDL_Color) { 255, 255, 255, 255 }, "Press Enter to continue", ((Vec2i) {16 * 2, 16 * 6}), manager);
}

void CheckContinueInput(LevelManager* manager)
{
	if (!manager->isInputActive) return;
	SDL_Event event = manager->inputEvent;
	if (event.type != SDL_KEYDOWN) return;

	switch (event.key.keysym.sym)
	{
	case SDLK_RETURN: {
		Level gameLevel = CONSTRUCT_LEVEL(GameLevel);
		LevelManager_SetNewLevel(manager, gameLevel);
	}break;
	}
}


void WinLevel_Update(float deltaTime, LevelManager* manager)
{
	PAC_ASSERT(manager && manager->data);
	WinData* leveldata = ((WinData*)manager->data);
	CheckContinueInput(manager);
}

void WinLevel_Render(float deltaTime, LevelManager* manager)
{
	PAC_ASSERT(manager && manager->data);
	WinData* leveldata = ((WinData*)manager->data);
	RenderText(&(leveldata->youWonTitle), manager->renderer);
	RenderText(&(leveldata->currentScoreText), manager->renderer);
	RenderText(&(leveldata->pressEnterText), manager->renderer);
}

void WinLevel_Destroy(LevelManager* manager)
{
	PAC_ASSERT(manager && manager->data);
	WinData* leveldata = ((WinData*)manager->data);
	DestroyText(&(leveldata->youWonTitle));
	DestroyText(&(leveldata->currentScoreText));
	DestroyText(&(leveldata->pressEnterText));
	free(manager->data);
	manager->data = NULL;
}