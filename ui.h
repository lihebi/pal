#ifndef __UI_H__
#define __UI_H__

#include "common.h"

#define CHUNKNUM_SPRITEUI 9

#define MAINMENU_LABEL_NEWGAME 7
#define MAINMENU_LABEL_LOADGAME 8

#define MENUITEM_COLOR 0x4f
#define MENUITEM_COLOR_INACTIVE 0x1c
#define MENUITEM_COLOR_CONFIRMED 0x2c
#define MENUITEM_COLOR_SELECTED_INACTIVE 0x1f
#define MENUITEM_COLOR_SELECTED_FIRST 0xf9
#define MENUITEM_COLOR_SELECTED_TOTALNUM 6
#define MENUITEM_COLOR_SELECTED \
  (MENUITEM_COLOR_SELECTED_FIRST + \
  SDL_GetTicks() / (600 / MENUITEM_COLOR_SELECTED_TOTALNUM) \
  % MENUITEM_COLOR_SELECTED_TOTALNUM)
#define MENUITEM_COLOR_EQUIPPEDITEM 0xc8
#define DESCTEXT_COLOR 0x2e

#define MENUITEM_VALUE_CANCELLED 0xffff

typedef struct tagMenuItem {
  ushort value;
  ushort numWord;
  bool enabled;
  uint pos;
} MenuItem, *LpMenuItem;

typedef void (*VoidCallbackUshort)(ushort);

#endif /* end of include guard: __UI_H__ */
