#pragma once
#include <assert.h>

#define PAC_ASSERT(...) assert( __VA_ARGS__);

#define PAC_CHECKNOENTRY() assert(0 && "Check no entry");
