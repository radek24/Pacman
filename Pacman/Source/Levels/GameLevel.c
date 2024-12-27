#include "GameLevel.h"
#include "WinLevel.h"
#include "GameOverLevel.h"
#include "GameObjects/Maze.h"
#include "GameObjects/Player.h"
#include "GameObjects/Pickupable.h"
#include "GameObjects/Text.h"
#include "GameObjects/LivesDisplay.h"
#include "GameObjects/Ghost.h"
#include "SDL_Wrapper.h"

#define VUNURABLE_TIME 10

typedef struct
{
	Maze maze;
	Player player;
	Pickups pickups;
	int score;
	Text scoreText;
	LivesDisplay display;
	Ghost ghosts[4];
	float vunurableTime;
	int areCurrentlyVunurable;

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
		
		case Big:{
			addScore(leveldata, manager, 50);
			leveldata->vunurableTime = manager->gameTime;
			leveldata->areCurrentlyVunurable = 1;
			for (int i = 0; i < 4; i++)
			{
				if (leveldata->ghosts[i].state == Alive) leveldata->ghosts[i].state = Vunurable;
			}
		} break;
		default:PAC_CHECKNOENTRY();break;
		}
		leveldata->pickups.pickups[i] = leveldata->pickups.pickups[leveldata->pickups.size-1];
		leveldata->pickups.size--;
	}
	if (leveldata->pickups.size == 0)
	{
		manager->currentScore = leveldata->score;
		manager->currentLives = leveldata->player.lives;
		Level WinLevel = CONSTRUCT_LEVEL(WinLevel);
		LevelManager_SetNewLevel(manager, WinLevel);
	}
}
void OnPlayerLivesChanged(LevelManager* manager, int lives) {

}

void GameLevel_Init(LevelManager* manager)
{
	manager->data = malloc(sizeof(GameLevelData));
	PAC_ASSERT(manager && manager->data);
	GameLevelData* leveldata = ((GameLevelData*)manager->data);
	leveldata->areCurrentlyVunurable = 0;
	InitPickups(&(leveldata->pickups), manager->renderer);
	InitMaze("Resources/Levels/level1.txt", &(leveldata->maze), &(leveldata->pickups), manager->renderer);
	Vec2i playerStart = { 14,23 };
	PlayerCallbacks callbacks = { OnPlayerTileUpdate ,OnPlayerLivesChanged };

	int lives;
	if (manager->currentLives == 0) {
		Ini_File* file = ini_file_parse(SETTINGS_FILE_NAME, LogErrorCallback);
		ini_file_find_integer(file, SETTINGS_SECTION_NAME, "StartingLives", &(lives));
		ini_file_free(file);
	}
	else {
		lives = manager->currentLives;
	}


	InitPlayer(&(leveldata->player),lives, manager->renderer, &playerStart, callbacks);

	char scoreString[50];
	sprintf(scoreString, "Score: %d", manager->currentScore);

	InitText(&(leveldata->scoreText), (SDL_Color) { 255, 255, 255, 255 }, scoreString, (Vec2i) { TILE_SIZE, TILE_SIZE* (MAZE_DIMENSIONS_Y + 1)}, manager);
	InitLivesDisplay(&(leveldata->display), (Vec2i) { 27, 32 }, manager->renderer);
	
	InitGhost(&(leveldata->ghosts[0]), (Vec2i) {1 , 2 }, Blinky,manager);
	InitGhost(&(leveldata->ghosts[1]), (Vec2i) { 7, 2 }, Pinky, manager);
	InitGhost(&(leveldata->ghosts[2]), (Vec2i) { 15, 2 }, Inky, manager);
	InitGhost(&(leveldata->ghosts[3]), (Vec2i) { 26, 2 }, Clyde, manager);

	leveldata->score = manager->currentScore;
}

void CheckVunurabilityState(GameLevelData* leveldata, LevelManager* manager);

void GameLevel_Update(float deltaTime, LevelManager* manager)
{
	PAC_ASSERT(manager && manager->data);
	GameLevelData* leveldata = ((GameLevelData*)manager->data);
		
	for (int i = 0; i < 4; i++)
	{
		UpdateGhost(&(leveldata->ghosts[i]), manager, deltaTime, &(leveldata->maze));
	}
	
	CheckVunurabilityState(leveldata, manager);


	for (int i = 0; i < 4; i++)
	{
		if (Vec2iEqual(&(leveldata->ghosts[i].currentTile), &(leveldata->player.currentTile)))
		{
			if (leveldata->ghosts[i].state == Vunurable)
			{
				addScore(leveldata, manager, 100);
				leveldata->ghosts[i].state = Dead;
				leveldata->ghosts[i].currentTile = (Vec2i){ 15,14 };
				leveldata->ghosts[i].timeWhenDied = manager->gameTime;
			}
			if (leveldata->ghosts[i].state == Alive)
			{
				leveldata->player.lives--;
				leveldata->player.currentTile = (Vec2i){ 14,23 };
				leveldata->ghosts[0].currentTile = (Vec2i){ 1 , 2 };
				leveldata->ghosts[1].currentTile = (Vec2i){ 7, 2 };
				leveldata->ghosts[2].currentTile = (Vec2i){ 15, 2 };
				leveldata->ghosts[3].currentTile = (Vec2i){ 26, 2 };

				if (leveldata->player.lives == 0)
				{
					manager->currentScore = leveldata->score;
					Level LostLevel = CONSTRUCT_LEVEL(GameOverLevel);
					LevelManager_SetNewLevel(manager, LostLevel);
					return;
				}
			}
		}
	}




	//Needs to be last entity to update, because this guy will call destroy level, so nothing can be after this. I know, very good design.
	UpdatePlayer(&(leveldata->player), manager, deltaTime, &(leveldata->maze));
	CheckReturnInput(manager);
}

void CheckVunurabilityState(GameLevelData* leveldata, LevelManager* manager)
{
	if (!leveldata->areCurrentlyVunurable)return;
	if (!(manager->gameTime > leveldata->vunurableTime + VUNURABLE_TIME)) return;
	leveldata->areCurrentlyVunurable = 0;
	for (int i = 0; i < 4; i++)
	{
		if (leveldata->ghosts[i].state == Vunurable) {
			leveldata->ghosts[i].state = Alive;
		}
	}
}

void GameLevel_Render(float deltaTime, LevelManager* manager)
{	
	PAC_ASSERT(manager && manager->data);
	GameLevelData* leveldata = ((GameLevelData*)manager->data);

	RenderMaze(manager->renderer, &(leveldata->maze));
	RenderPickups(&(leveldata->pickups), manager->gameTime, manager->renderer);
	RenderPlayer(&(leveldata->player), manager->gameTime, manager->renderer);
	RenderText(&(leveldata->scoreText), manager->renderer);
	RenderLivesDisplay(&(leveldata->display), manager->renderer, &(leveldata->player));
	for (int i = 0; i < 4; i++)
	{
		RenderGhost(&(leveldata->ghosts[i]), manager);
	}
	
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