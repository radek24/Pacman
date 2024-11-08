#include "ControlsLevel.h"
#include "GameObjects/Text.h"

typedef struct {
	Text controlsTitle;
	SDL_Texture* levelScreen;
	Vec2i screenSize;
}ControlsData;

void ControlsLevel_Init(LevelManager* manager)
{
	manager->data = malloc(sizeof(ControlsData));
	PAC_ASSERT(manager && manager->data);
	ControlsData* leveldata = ((ControlsData*)manager->data);
	InitText(&(leveldata->controlsTitle), (SDL_Color) { 255, 255, 255, 255 }, "Controls (esc to close)", MENU_HEADER_LOCATION, manager);
	leveldata->levelScreen = IMG_LoadTexture(manager->renderer, "Resources/Sprites/Controls.png");
	PAC_ASSERT(leveldata->levelScreen);
	SDL_QueryTexture(leveldata->levelScreen, NULL, NULL, &(leveldata->screenSize.x), &(leveldata->screenSize.y));
}

void ControlsLevel_Update(float deltaTime, LevelManager* manager)
{
	PAC_ASSERT(manager && manager->data);
	ControlsData* leveldata = ((ControlsData*)manager->data);
	
	CheckReturnInput(manager);
}

void ControlsLevel_Render(float deltaTime, LevelManager* manager)
{
	PAC_ASSERT(manager && manager->data);
	ControlsData* leveldata = ((ControlsData*)manager->data);
	RenderText(&(leveldata->controlsTitle), manager->renderer);
	SDL_Rect pos = { TILE_SIZE *5,TILE_SIZE*5,leveldata->screenSize.x*2,leveldata->screenSize.y*2};
	SDL_RenderCopy(manager->renderer, leveldata->levelScreen, NULL, &pos);
}

void ControlsLevel_Destroy(LevelManager* manager)
{
	PAC_ASSERT(manager && manager->data);
	ControlsData* leveldata = ((ControlsData*)manager->data);
	DestroyText(&(leveldata->controlsTitle));
	SDL_DestroyTexture(&(leveldata->levelScreen));
	free(manager->data);
	manager->data = NULL;
}
