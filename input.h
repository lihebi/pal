#ifndef __INPUT_H__
#define __INPUT_H__

typedef struct tagInputState {
  Direction dir, prevdir;
  uint keyPress;
} InputState;

extern volatile InputState g_inputState;

#endif /* end of include guard: __INPUT_H__ */
