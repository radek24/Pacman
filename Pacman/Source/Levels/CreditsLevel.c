#include "CreditsLevel.h"
#include "GameObjects/Text.h"

typedef struct
{
	Text creditsTitle;
} CreditsData;

void CreditsLevel_Init(LevelManager *manager)
{
	manager->data = malloc(sizeof(CreditsData));
	PAC_ASSERT(manager && manager->data);
	CreditsData *leveldata = ((CreditsData *)manager->data);
	InitText(&(leveldata->creditsTitle), (SDL_Color){255, 255, 255, 255}, "Credits (esc to close)", MENU_HEADER_LOCATION, manager);
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
}

void CreditsLevel_Destroy(LevelManager *manager)
{
	PAC_ASSERT(manager && manager->data);
	CreditsData *leveldata = ((CreditsData *)manager->data);
	DestroyText(&(leveldata->creditsTitle));

	free(manager->data);
	manager->data = NULL;
}
