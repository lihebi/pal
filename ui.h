#ifndef __UI_H__
#define __UI_H__

#include "common.h"

#define CHUNKNUM_SPRITEUI 9

#define MAINMENU_LABEL_NEWGAME 7
#define MAINMENU_LABEL_LOADGAME 8

typedef struct tagMenuItem {
  ushort value;
  ushort numWord;
  bool enabled;
  uint pos;
} MenuItem, *LpMenuItem;

#endif /* end of include guard: __UI_H__ */
