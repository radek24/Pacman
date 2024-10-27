#include "GameLevel.h"
#include "GameObjects/Maze.h"
#include "GameObjects/Player.h"
#include "GameObjects/Pickupable.h"
#include "GameObjects/Text.h"
#include "SDL_Wrapper.h"

typedef struct
{
	Maze maze;
	Player player;
	float gameTime;
	Pickups pickups;
	int score;
	Text scoreText;
	

}GameLevelData;

/*Setter, because every time score is changed we need to update UI*/
static void addScore(GameLevelData* data, LevelManager* manager,int amount) 
{
	data->score += amount;

	char buffer[256];  
	sprintf(buffer, "score: %d", data->score);

	UpdateText(&(data->scoreText), buffer, manager);
}

void PlayerTileUpdateCallback(LevelManager* manager, Vec2i *pos) {
	PAC_ASSERT(manager && manager->data);
	GameLevelData* leveldata = ((GameLevelData*)manager->data);
	for (int i = 0; i < leveldata->pickups.size; i++)
	{
		if (leveldata->pickups.pickups[i].positionInGrid.x != pos->x || leveldata->pickups.pickups[i].positionInGrid.y != pos->y)continue;
		//Insead of changing pickup state we just remove it from array and decrese size.
		switch (leveldata->pickups.pickups[i].type) {
		case Score: addScore(leveldata,manager, 10); break;
		case Big: addScore(leveldata,manager, 50); break;
		default:PAC_CHECKNOENTRY();break;
		}
		leveldata->pickups.pickups[i] = leveldata->pickups.pickups[leveldata->pickups.size-1];
		leveldata->pickups.size--;
	}
}



void GameLevel_Init(LevelManager* manager)
{
	manager->data = malloc(sizeof(GameLevelData));
	PAC_ASSERT(manager && manager->data);
	GameLevelData* leveldata = ((GameLevelData*)manager->data);
	InitPickups(&(leveldata->pickups), manager->renderer);
	
	InitMaze("Resources/Levels/level1.txt", &(leveldata->maze), &(leveldata->pickups), manager->renderer);
	
	Vec2i playerStart = { 14,23 };
	InitPlayer(&(leveldata->player), manager->renderer, &playerStart, PlayerTileUpdateCallback);
	
	InitText(&(leveldata->scoreText), (SDL_Color) { 255, 255, 255, 255 }, "Score: 0", (Vec2i) { TILE_SIZE, TILE_SIZE* (MAZE_DIMENSIONS_Y + 1)}, manager);

	leveldata->gameTime = 0;
	leveldata->score = 0;
}

void GameLevel_Update(float deltaTime, LevelManager* manager)
{
	PAC_ASSERT(manager && manager->data);
	GameLevelData* leveldata = ((GameLevelData*)manager->data);
	leveldata->gameTime += deltaTime;
	
	UpdatePlayer(&(leveldata->player), manager, deltaTime,&(leveldata->maze));	
}

void GameLevel_Render(float deltaTime, LevelManager* manager)
{	
	PAC_ASSERT(manager && manager->data);
	GameLevelData* leveldata = ((GameLevelData*)manager->data);

	RenderMaze(manager->renderer, &(leveldata->maze));
	RenderPickups(&(leveldata->pickups), leveldata->gameTime, manager->renderer);
	RenderPlayer(&(leveldata->player), leveldata->gameTime, manager->renderer);
	RenderText(&(leveldata->scoreText), manager->renderer);

}

void GameLevel_Destroy(LevelManager* manager)
{
	PAC_ASSERT(manager && manager->data);
	GameLevelData* leveldata = ((GameLevelData*)manager->data);
	
	DestroyMaze(&(leveldata->maze));
	DestroyPlayer(&(leveldata->player));
	DestroyPickups(&(leveldata->pickups));
	DestroyText(&(leveldata->scoreText));
	free(manager->data);
}