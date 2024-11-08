#include "CreditsLevel.h"
#include "GameObjects/Text.h"

typedef struct
{
	Text creditsTitle;
	SDL_Texture* levelScreen;
	Vec2i screenSize;
} CreditsData;

void CreditsLevel_Init(LevelManager *manager)
{
	manager->data = malloc(sizeof(CreditsData));
	PAC_ASSERT(manager && manager->data);
	CreditsData *leveldata = ((CreditsData *)manager->data);
	InitText(&(leveldata->creditsTitle), (SDL_Color){255, 255, 255, 255}, "Credits (esc to close)", MENU_HEADER_LOCATION, manager);
	leveldata->levelScreen = IMG_LoadTexture(manager->renderer, "Resources/Sprites/Credits.png");
	PAC_ASSERT(leveldata->levelScreen);
	SDL_QueryTexture(leveldata->levelScreen, NULL, NULL, &(leveldata->screenSize.x), &(leveldata->screenSize.y));
}

void CreditsLevel_Update(float deltaTime, LevelManager *manager)
{
	PAC_ASSERT(manager && manager->data);
	CreditsData *leveldata = ((CreditsData *)manager->data);
	CheckReturnInput(manager);
}

void CreditsLevel_Render(float deltaTime, LevelManager *manager)
{
	PAC_ASSERT(manager && manager->data);
	CreditsData *leveldata = ((CreditsData *)manager->data);
	RenderText(&(leveldata->creditsTitle), manager->renderer);
	SDL_Rect pos = { TILE_SIZE * 5,TILE_SIZE * 5,leveldata->screenSize.x * 2,leveldata->screenSize.y * 2 };
	SDL_RenderCopy(manager->renderer, leveldata->levelScreen, NULL, &pos);
}

void CreditsLevel_Destroy(LevelManager *manager)
{
	PAC_ASSERT(manager && manager->data);
	CreditsData *leveldata = ((CreditsData *)manager->data);
	DestroyText(&(leveldata->creditsTitle));
	SDL_DestroyTexture(&(leveldata->levelScreen));
	free(manager->data);
	manager->data = NULL;
}
