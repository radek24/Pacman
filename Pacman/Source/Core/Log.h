#pragma once
#include <SDL2/SDL_log.h>


#ifndef PAC_SHIPING

#define PAC_FATAL(...)  SDL_LogCritical(SDL_LOG_PRIORITY_ERROR, __VA_ARGS__);
#define PAC_WARN(...)	SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, __VA_ARGS__);
#define PAC_LOG(...)   SDL_Log(__VA_ARGS__);

#else

#define PAC_FATAL(...)  
#define PAC_WARN(...)	
#define PAC_LOG(...)   

#endif