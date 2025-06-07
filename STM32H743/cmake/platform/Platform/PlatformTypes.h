#ifndef PLATFORM_TYPES_H_
#define PLATFORM_TYPES_H_

// Section 0: C Standard Types
//    fprime depends on the existence of intN_t and uintN_t C standard ints and
//    the mix/max values for those types. Platform developers must either:
//    1. define these types and definitions
//    2. include headers that define these types
//
// In addition, support for various type widths can be turned on/off with the
// switches in this section to control which of the C standard types are
// available in the system. fprime consumes this information and produces the
// UN, IN, and FN types we see in fprime code.

#ifdef  __cplusplus
extern "C" {
#endif
#include <stdint.h>

typedef long int PlatformIntType;
#define PRI_PlatformIntType "d"

typedef long unsigned int PlatformUIntType;
#define PRI_PlatformUIntType "u"

// Linux/Darwin definitions for pointer have various sizes across platforms
// and since these definitions need to be consistent we must ask the size.
// Check for __SIZEOF_POINTER__ or cause error
#ifndef __SIZEOF_POINTER__
#error "Compiler does not support __SIZEOF_POINTER__, cannot use Linux/Darwin types"
#endif

// Pointer sizes are determined by compiler
#if __SIZEOF_POINTER__ == 8
typedef uint64_t PlatformPointerCastType;
#define PRI_PlatformPointerCastType PRIx64
#elif __SIZEOF_POINTER__ == 4
typedef uint32_t PlatformPointerCastType;
#define PRI_PlatformPointerCastType PRIx32
#elif __SIZEOF_POINTER__ == 2
typedef uint16_t PlatformPointerCastType;
#define PRI_PlatformPointerCastType PRIx16
#elif __SIZEOF_POINTER__ == 1
typedef uint8_t PlatformPointerCastType;
#define PRI_PlatformPointerCastType PRIx8
#else
#error "Expected __SIZEOF_POINTER__ to be one of 8, 4, 2, or 1"
#endif

#ifdef  __cplusplus
}
#endif

#endif  // PLATFORM_TYPES_H_
