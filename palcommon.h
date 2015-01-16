#ifndef __PAL_COMMON_H__
#define __PAL_COMMON_H__

#include "common.h"

typedef enum tagDirection {
  DIR_SOUTH = 0,
  DIR_WEST,
  DIR_NORTH,
  DIR_EAST,
  DIR_UNKNOWN
} Direction, *LpDirection;

typedef LpByte LpSprite;

#endif /* end of include guard: __PAL_COMMON_H__ */
