#include "main.h"

LpSprite g_spriteUI = NULL;

int ui_init() {
  int size;
  size = MKF_get_chunk_size(CHUNKNUM_SPRITEUI, g_globalVars->f.fpData);
  g_spriteUI = (LpSprite)calloc(1,size);
  MKF_read_chunk(g_spriteUI, size, CHUNKNUM_SPRITEUI, g_globalVars->f.fpData);
  return 0;
}

ushort read_menu(VoidCallbackUshort fnMenuItemChanged,
LpMenuItem menuItem, int nMenuItem, ushort defaultItem, Byte labelColor) {
  int i;
  ushort currentItem = (defaultItem < nMenuItem) ? defaultItem : 0;
  for (i=0;i<nMenuItem;i++) {
    Byte color = labelColor;
    if (!menuItem[i].enabled) {
      if (i==currentItem) {
        color = MENUITEM_COLOR_SELECTED_INACTIVE;
      } else {
        color = MENUITEM_COLOR_INACTIVE;
      }
    }
    draw_text(get_word(menuItem[i].wordId), menuItem[i].pos, color, true, true);
  }
  if (fnMenuItemChanged != NULL) {
    (*fnMenuItemChanged)(menuItem[defaultItem].value);
  }
  while(true) {
    g_inputState.keyPress = 0;
    if (menuItem[currentItem].enabled) {
      draw_text(get_word(menuItem[currentItem].wordId),
      menuItem[currentItem].pos,MENUITEM_COLOR_SELECTED, false, true);
    }
    process_event();
    if (g_inputState.keyPress & (KEY_DOWN | KEY_RIGHT)) {
      if (menuItem[currentItem].enabled) {
        draw_text(get_word(menuItem[currentItem].wordId),
        menuItem[currentItem].pos, labelColor, false, true);
      } else {
        draw_text(get_word(menuItem[currentItem].wordId),
        menuItem[currentItem].pos, MENUITEM_COLOR_INACTIVE, false, true);
      }
      currentItem++;
      if (currentItem >= nMenuItem) {
        currentItem = 0;
      }
      // highlight selected item
      if (menuItem[currentItem].enabled) {
        draw_text(get_word(menuItem[currentItem].wordId),
        menuItem[currentItem].pos, MENUITEM_COLOR_SELECTED, false, true);
      } else {
        draw_text(get_word(menuItem[currentItem].wordId),
        menuItem[currentItem].pos, MENUITEM_COLOR_SELECTED_INACTIVE, false, true);
      }
      if (fnMenuItemChanged != NULL) {
        (*fnMenuItemChanged)(menuItem[currentItem].value);
      }
    } else if (g_inputState.keyPress & (KEY_UP | KEY_LEFT)) {
      if (menuItem[currentItem].enabled) {
        draw_text(get_word(menuItem[currentItem].wordId),
        menuItem[currentItem].pos, labelColor, false, true);
      } else {
        draw_text(get_word(menuItem[currentItem].wordId),
        menuItem[currentItem].pos, MENUITEM_COLOR_INACTIVE, false, true);
      }
      if (currentItem > 0) {
        currentItem--;
      } else {
        currentItem = nMenuItem -1;
      }
      // highlight selected item
      if (menuItem[currentItem].enabled) {
        draw_text(get_word(menuItem[currentItem].wordId),
        menuItem[currentItem].pos, MENUITEM_COLOR_SELECTED, false, true);
      } else {
        draw_text(get_word(menuItem[currentItem].wordId),
        menuItem[currentItem].pos, MENUITEM_COLOR_SELECTED_INACTIVE, false, true);
      }
      if (fnMenuItemChanged != NULL) {
        (*fnMenuItemChanged)(menuItem[currentItem].value);
      }
    } else if (g_inputState.keyPress & KEY_MENU) {
      if (menuItem[currentItem].enabled) {
        draw_text(get_word(menuItem[currentItem].wordId),
        menuItem[currentItem].pos, labelColor, false, true);
      } else {
        draw_text(get_word(menuItem[currentItem].wordId),
        menuItem[currentItem].pos, MENUITEM_COLOR_INACATIVE, false, true);
      }
      break;
    } else if (g_inputState & KEY_SEARCH) {
      if (menuItem[currentItem].enabled) {
        draw_text(get_word(menuItem[currentItem].wordId),
        menuItem[currentItem].pos, MENUITEM_COLOR_CONFIRMED, false, true);
        return menuItem[currentItem].value;
      }
    }
    SDL_Delay(50);
  }
  return MENUITEM_VALUE_CANCELLED;
}
