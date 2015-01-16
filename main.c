#include "main.h"
static void init(unsigned short width, unsigned short height) {
  int e;
  SDL_Init(SDL_INIT_EVERYTHING);
  video_init(width, height);
  global_init();
  ui_init();
  text_init();
  input_init();
  resource_init();
  // SOUND_OpenAudio();
}
int main() {
  unsigned short width=640, height=400;
  init(width, height);
  game_main();
  return 255;
}
