#pragma once

#include <Oasis/Debug/Log.h>

#ifdef OASIS_DEBUG
    #ifdef OASIS_WINDOWS
        #define OASIS_DEBUG_BREAK __debugbreak()
    #elif OASIS_MACOSX
        #define OASIS_DEBUG_BREAK
    #elif OASIS_LINUX
        #define OASIS_DEBUG_BREAK
    #endif
    
	#define OASIS_ASSERT(x, msg) { if(!(x)) { OASIS_LOG_ERROR("Assertion failed: %s", msg); OASIS_DEBUG_BREAK; } }
#else
	#define OASIS_ASSERT(x, msg)
#endif

