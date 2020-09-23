#pragma once

// Start of platform check
#ifdef _WIN32

#ifdef _WIN64
#undef NIBBLE_PLATFORM_WINDOWS
#define NIBBLE_PLATFORM_WINDOWS
#else
#error "x86 not supported!"
#endif // _WIN64

#else

#error "Unknown platform!"

#endif //_WIN32
// End of platform check