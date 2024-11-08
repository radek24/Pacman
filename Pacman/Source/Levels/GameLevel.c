#include "GameLevel.h"
#include "GameObjects/Maze.h"
#include "GameObjects/Player.h"
#include "GameObjects/Pickupable.h"
#include "GameObjects/Text.h"
#include "GameObjects/LivesDisplay.h"
#include "GameObjects/Ghost.h"
#include "SDL_Wrapper.h"

typedef struct
{
	Maze maze;
	Player player;
	Pickups pickups;
	int score;
	Text scoreText;
	LivesDisplay display;
	Ghost ghosts[4];

}GameLevelData;

/*Setter, because every time score is changed we need to update UI*/
static void addScore(GameLevelData* data, LevelManager* manager,int amount) 
{
	data->score += amount;

	char buffer[256];  
	sprintf(buffer, "score: %d", data->score);
	UpdateText(&(data->scoreText), buffer, manager);
}

void OnPlayerTileUpdate(LevelManager* manager, Vec2i *pos) {
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
void OnPlayerLivesChanged(LevelManager* manager, int lives) {

}

void GameLevel_Init(LevelManager* manager)
{
	manager->data = malloc(sizeof(GameLevelData));
	PAC_ASSERT(manager && manager->data);
	GameLevelData* leveldata = ((GameLevelData*)manager->data);
	
	InitPickups(&(leveldata->pickups), manager->renderer);
	InitMaze("Resources/Levels/level1.txt", &(leveldata->maze), &(leveldata->pickups), manager->renderer);
	Vec2i playerStart = { 14,23 };
	PlayerCallbacks callbacks = { OnPlayerTileUpdate ,OnPlayerLivesChanged };
	InitPlayer(&(leveldata->player), manager->renderer, &playerStart, callbacks);
	InitText(&(leveldata->scoreText), (SDL_Color) { 255, 255, 255, 255 }, "Score: 0", (Vec2i) { TILE_SIZE, TILE_SIZE* (MAZE_DIMENSIONS_Y + 1)}, manager);
	InitLivesDisplay(&(leveldata->display), leveldata->player.lives, (Vec2i) { 27, 32 }, manager->renderer);
	InitGhost(&(leveldata->ghosts[0]), (Vec2i) {1 , 2 }, Blinky,manager);

	leveldata->score = 0;
}

void GameLevel_Update(float deltaTime, LevelManager* manager)
{
	PAC_ASSERT(manager && manager->data);
	GameLevelData* leveldata = ((GameLevelData*)manager->data);
	
	UpdatePlayer(&(leveldata->player), manager, deltaTime,&(leveldata->maze));	
	UpdateGhost(&(leveldata->ghosts[0]), manager);

	CheckReturnInput(manager);
}

void GameLevel_Render(float deltaTime, LevelManager* manager)
{	
	PAC_ASSERT(manager && manager->data);
	GameLevelData* leveldata = ((GameLevelData*)manager->data);

	RenderMaze(manager->renderer, &(leveldata->maze));
	RenderPickups(&(leveldata->pickups), manager->gameTime, manager->renderer);
	RenderPlayer(&(leveldata->player), manager->gameTime, manager->renderer);
	RenderText(&(leveldata->scoreText), manager->renderer);
	RenderLivesDisplay(&(leveldata->display), manager->renderer);
	RenderGhost(&(leveldata->ghosts), manager);
}

void GameLevel_Destroy(LevelManager* manager)
{
	PAC_ASSERT(manager && manager->data);
	GameLevelData* leveldata = ((GameLevelData*)manager->data);
	
	DestroyMaze(&(leveldata->maze));
	DestroyPlayer(&(leveldata->player));
	DestroyPickups(&(leveldata->pickups));
	DestroyText(&(leveldata->scoreText));
	DestroyLivesDisplay(&(leveldata->display));
	DestroyGhost(&(leveldata->ghosts[0]));
	free(manager->data);
}