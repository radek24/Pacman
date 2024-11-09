#pragma once
#include <SDL2/SDL_log.h>
#include "log/rxi_log.h"


#if !defined(PAC_SHIPING) || defined(LOG_IN_SHIPPING)

#define PAC_FATAL(...)		log_fatal( __VA_ARGS__);
#define PAC_ERROR(...)		log_error( __VA_ARGS__)
#define PAC_WARN(...)		log_warn( __VA_ARGS__);
#define PAC_LOG(...)		log_info(__VA_ARGS__);
#define PAC_DEBUGLOG(...)	log_debug(__VA_ARGS__);

#else

#define PAC_FATAL(...)
#define PAC_ERROR(...)
#define PAC_WARN(...)	
#define PAC_LOG(...)   
#define PAC_DEBUGLOG(...)

#endif