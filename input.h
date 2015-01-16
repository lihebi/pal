#ifndef __INPUT_H__
#define __INPUT_H__

typedef struct tagInputState {
  Direction dir, prevdir;
  uint keyPress;
} InputState;

extern volatile InputState g_inputState;

enum KEY {
  KEY_MENU = (1<<0),
  KEY_SEARCH = (1<<1),
  KEY_DOWN = (1<<2),
  KEY_LEFT = (1<<3),
  KEY_UP = (1<<4),
  KEY_RIGHT = (1<<5),
  KEY_PAGE_UP = (1<<6),
  KEY_PAGE_DOWN = (1<<7),
  KEY_REPEAT = (1<<8),
  KEY_AUTO = (1<<9),
  KEY_DEFEND = (1<<10),
  KEY_USE_ITEM = (1<<11),
  KEY_THROW_ITEM = (1<<12),
  KEY_FLEE = (1<<13),
  KEY_STATUS = (1<<14),
  KEY_FORCE = (1<<15)
};

#endif /* end of include guard: __INPUT_H__ */
