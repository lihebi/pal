#include "main.h"

typedef struct tagResources {
  Byte loadFlag;
  LpMap *map;
  LpSprite *eventObjectSprites;
  int nEventObject;
  LpSprite playerSprite[MAX_PLAYERS_IN_PARTY + 1];
} Resources, *LpResources;

static LpResources g_resources = NULL;

void resource_init() {
  g_resources = (LpResources)calloc(1, sizeof(Resources));
}
