#include "TestLevel.h"
#include "../GameObjects/Maze.h"
#include "../GameObjects/Player.h"
#include "../GameObjects/Pickupable.h"
#include "../SDL_Wrapper.h"

typedef struct
{
	Maze maze;
	Player player;
	float gameTime;
}TestLevelData;

void TestLevel_Init(LevelManager* manager)
{
	manager->data = malloc(sizeof(TestLevelData));
	PAC_ASSERT(manager && manager->data);
	
	TestLevelData* leveldata = ((TestLevelData*)manager->data);
	InitMaze("Resources/Levels/level1.txt", &(leveldata->maze), manager->renderer);
	
	Vec2i playerStart = { 14,23 };
	InitPlayer(&(leveldata->player), manager->renderer, &playerStart);
	
	leveldata->gameTime = 0;
}

void TestLevel_Update(float deltaTime, LevelManager* manager)
{
	PAC_ASSERT(manager && manager->data);
	TestLevelData* leveldata = ((TestLevelData*)manager->data);
	leveldata->gameTime += deltaTime;
	
	UpdatePlayer(&(leveldata->player), manager, deltaTime,&(leveldata->maze));	
}

void TestLevel_Render(float deltaTime, LevelManager* manager)
{	
	PAC_ASSERT(manager && manager->data);
	TestLevelData* leveldata = ((TestLevelData*)manager->data);

	SDL_RenderClear(manager->renderer);

	RenderMaze(manager->renderer, &(leveldata->maze));
	RenderPlayer(&(leveldata->player), leveldata->gameTime, manager->renderer);

	SDL_RenderPresent(manager->renderer);
}

void TestLevel_Destroy(LevelManager* manager)
{
	PAC_ASSERT(manager && manager->data);
	TestLevelData* leveldata = ((TestLevelData*)manager->data);
	
	DestroyMaze(&(leveldata->maze));
	DestroyPlayer(&(leveldata->player));
	free(manager->data);
}