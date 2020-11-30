#pragma once

/// Contains critical build and engine macro

#include "Platform/Platform.h"

// Windows platform
#ifdef NIBBLE_PLATFORM_WINDOWS

#else

#error Supproted only a Windows platform.

#endif // NIBBLE_PLATFORM_WINDOWS

// Assert debug
#ifdef NIBBLE_DEBUG

#define M_NIBBLE_ENG_ASSERT(x, ...) { if(!(x)) { M_LOGGER_ENG_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#define NIBBLE_CLIENT_ASSERT(x, ...) { if(!(x)) { LOGGER_CLIENT_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }

#else

#define M_NIBBLE_ENG_ASSERT(x, ...)
#define NIBBLE_CLIENT_ASSERT(x, ...)

#endif // End of NIBBLE_DEBUG
// End of assert debug
