#pragma once

#include "Core/MacroPlatform.h"

// Export lib for platform
#ifdef NIBBLE_PLATFORM_WINDOWS

#ifdef NIBBLE_BUILD_DLL

#define NIBBLE_EXPORT_API __declspec(dllexport)
#else
#define NIBBLE_EXPORT_API __declspec(dllimport)
#endif // NIBBLE_BUILD_DLL

#else

#error Windows only supported!

#endif // NIBBLE_PLATFORM_WINDOWS

// Assert debug
#ifdef NIBBLE_DEBUG

#define M_NIBBLE_ENG_ASSERT(x, ...) { if(!(x)) { LOGGER_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#define NIBBLE_CLIENT_ASSERT(x, ...) { if(!(x)) { LOGGER_APP_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }

#else

#define M_NIBBLE_ENG_ASSERT(x, ...)
#define NIBBLE_CLIENT_ASSERT(x, ...)

#endif // End of NIBBLE_DEBUG
// End of assert debug
