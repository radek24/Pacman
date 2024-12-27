#include "GameOverLevel.h"
#include "GameLevel.h"
#include "GameObjects/Text.h"

typedef struct
{
	Text youWonTitle;
	Text currentScoreText;
	Text pressEnterText;
} WinData;

void GameOverLevel_Init(LevelManager* manager)
{
	manager->data = malloc(sizeof(WinData));
	PAC_ASSERT(manager && manager->data);
	WinData* leveldata = ((WinData*)manager->data);
	InitText(&(leveldata->youWonTitle), (SDL_Color) { 255, 255, 255, 255 }, "You are dead. :(", ((Vec2i) {16 * 2, 16 * 2}), manager);
	char scoreString[50];
	sprintf(scoreString, "Score = %d", manager->currentScore);
	InitText(&(leveldata->currentScoreText), (SDL_Color) { 255, 255, 255, 255 }, scoreString, ((Vec2i) {16 * 2, 16 * 4}), manager);
	InitText(&(leveldata->pressEnterText), (SDL_Color) { 255, 255, 255, 255 }, "Press Esc to return", ((Vec2i) {16 * 2, 16 * 6}), manager);

	manager->currentScore = 0;
	manager->currentLives = 0;
}

void GameOverLevel_Update(float deltaTime, LevelManager* manager)
{
	PAC_ASSERT(manager && manager->data);
	WinData* leveldata = ((WinData*)manager->data);
	CheckReturnInput(manager);
}

void GameOverLevel_Render(float deltaTime, LevelManager* manager)
{
	PAC_ASSERT(manager && manager->data);
	WinData* leveldata = ((WinData*)manager->data);
	RenderText(&(leveldata->youWonTitle), manager->renderer);
	RenderText(&(leveldata->currentScoreText), manager->renderer);
	RenderText(&(leveldata->pressEnterText), manager->renderer);
}

void GameOverLevel_Destroy(LevelManager* manager)
{
	PAC_ASSERT(manager && manager->data);
	WinData* leveldata = ((WinData*)manager->data);
	DestroyText(&(leveldata->youWonTitle));
	DestroyText(&(leveldata->currentScoreText));
	DestroyText(&(leveldata->pressEnterText));
	free(manager->data);
	manager->data = NULL;
}