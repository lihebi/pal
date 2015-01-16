#ifndef __MAP_H__
#define __MAP_H__

#include "common.h"

typedef struct tagMap {
  uint tiles[128][64][2];
  LpSprite tileSprite;
  int mapId;
} Map, *LpMap;

#endif /* end of include guard: __MAP_H__ */
