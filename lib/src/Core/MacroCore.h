#pragma once

#include "MacroPlatform.h"

#ifdef NIBBLE_PLATFORM_WINDOWS

#ifdef NIBBLE_BUILD_DLL
#define NIBBLE_API __declspec(dllexport)
#else
#define NIBBLE_API __declspec(dllimport)
#endif // NIBBLE_BUILD_DLL

#else

#error Windows only supported!

#endif // NIBBLE_PLATFORM_WINDOWS
