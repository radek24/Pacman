#pragma once

#include "Log.h"
#include "Assert.h"
#include "Math.h"

#define TILE_SIZE 16
#define MAZE_DIMENSIONS_X 28
#define MAZE_DIMENSIONS_Y 31
#define WINDOW_SIZE_X ((MAZE_DIMENSIONS_X)+2) * (TILE_SIZE)
#define WINDOW_SIZE_Y ((MAZE_DIMENSIONS_Y)+5) * (TILE_SIZE)	

#ifndef NULL
#define NULL ((void *)0)
#endif

#define LEADERBOARD_FILENAME "leaderboards.ini"
#define LEADERBORDS_SECTION "Leaderboards"

#define CONSTRUCT_LEVEL(LevelName) { LevelName##_Init, LevelName##_Update, LevelName##_Render, LevelName##_Destroy }

#define MENU_HEADER_LOCATION ((Vec2i){ TILE_SIZE*2, TILE_SIZE*2})


#ifndef min
#define min(a,b) ((a) < (b) ? (a) : (b))
#endif

#ifndef max
#define max(a,b) ((a) > (b) ? (a) : (b))
#endif

int getSpriteIndexFromTime(float time, int sprites);


