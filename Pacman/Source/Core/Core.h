#pragma once

#include "Log.h"
#include "Assert.h"
#include "Math.h"


#define TILE_SIZE 16
#define MAZE_DIMENSIONS_X 28
#define MAZE_DIMENSIONS_Y 31
#define WINDOW_SIZE_X ((MAZE_DIMENSIONS_X)+2) * (TILE_SIZE)
#define WINDOW_SIZE_Y ((MAZE_DIMENSIONS_Y)+4) * (TILE_SIZE)	

#ifndef NULL
#define NULL ((void *)0)
#endif

int getSpriteIndexFromTime(float time, int sprites);