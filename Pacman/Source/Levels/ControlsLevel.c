#include "ControlsLevel.h"
#include "GameObjects/Text.h"

typedef struct {
	Text controlsTitle;
}ControlsData;

void ControlsLevel_Init(LevelManager* manager)
{
	manager->data = malloc(sizeof(ControlsData));
	PAC_ASSERT(manager && manager->data);
	ControlsData* leveldata = ((ControlsData*)manager->data);
	InitText(&(leveldata->controlsTitle), (SDL_Color) { 255, 255, 255, 255 }, "Controls (esc to close)", MENU_HEADER_LOCATION, manager);
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
}

void ControlsLevel_Destroy(LevelManager* manager)
{
	PAC_ASSERT(manager && manager->data);
	ControlsData* leveldata = ((ControlsData*)manager->data);
	DestroyText(&(leveldata->controlsTitle));

	free(manager->data);
	manager->data = NULL;

}
