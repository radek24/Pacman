#pragma once
#include <SDL2/SDL_assert.h>

#define PAC_ASSERT(...) SDL_assert( __VA_ARGS__);

#define PAC_CHECKNOENTRY SDL_assert(0 && "Check no entry");
