#ifndef __COMMON_H__
#define __COMMON_H__

typedef unsigned char Byte, *LpByte

typedef unsigned char uint8_t;
typedef char int8_t;
typedef unsigned short uint16_t;
typedef short int16_t;
typedef unsigned int uint32_t;
typedef int int32_t;
typedef unsigned long long uint64_t;
typedef long long int64_t;

#endif /* end of include guard: __COMMON_H__ */

#if SDL_BYTEORDER == SDL_LIL_ENDIAN
#define SWAP16(X)    (X)
#define SWAP32(X)    (X)
#else
#define SWAP16(X)    SDL_Swap16(X)
#define SWAP32(X)    SDL_Swap32(X)
#endif

#define HEBI_XY(x,y) (uint)((((ushort)(y)<<16) & 0xffff0000) | ((ushort)(x) & 0xffff))
#define HEBI_X(xy) (short)(xy & 0xffff)
#define HEBI_Y(xy) (short)((xy>>16) & 0xffff)
