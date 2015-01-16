volatile InputState g_inputState;
void input_init() {
  memset((void*)&g_inputState, 0, sizeof(g_inputState));
  g_inputState.dir = DIR_UNKNOWN;
  g_inputState.prevdir = DIR_UNKNOWN;
}
static void keyboard_event_filter(const SDL_Event *event) {
  switch(event->type) {
    case SDL_KEYDOWN:
      switch(event.key.keysym.sym) {
        case SDLK_UP:
          if (g_globalVars->inBattle || g_inputState.dir != DIR_NORTH) {
            g_inputState.prevdir = (g_globalVars->inBattle?DIR_UNKNOWN:g_inputState.dir);
            g_inputState.dir = DIR_NORTH;
            g_inputState.keyPress |= KEY_UP;
          }
          break;
        case SDLK_DOWN:
          if (g_globalVars->inBattle || g_inputState.dir != DIR_SOUTH) {
            g_inputState.prevdir = (g_globalVars->inBattle ? DIR_UNKNOWN : g_inputState.dir);
            g_inputState.dir = DIR_SOUTH;
            g_inputState.keyPress |= KEY_DOWN;
          }
          break;
        case SDLK_LEFT:
          if (g_globalVars->inBattle || g_inputState.dir != DIR_WEST) {
            g_inputState.prevdir = (g_globalVars->inBattle ? DIR_UNKNOWN : g_inputState.dir);
            g_inputState.dir = DIR_WEST;
            g_inputState.keyPress |= KEY_LEFT;
          }
          break;
        case SDLK_RIGHT:
          if (g_globalVars->inBattle || g_inputState.dir != DIR_EAST) {
            g_inputState.prevdir = (g_globalVars->inBattle ? DIR_UNKNOWN : g_inputState.dir);
            g_inputState.dir = DIR_EAST;
            g_inputState.keyPress |= KEY_RIGHT;
          }
          break;
        case SDLK_ESCAPE:
          g_inputState.keyPress |= KEY_MENU;
          break;
        case SDLK_RETURN:
        case SDLK_SPACE:
          g_inputState.keyPress |= KEY_SEARCH;
          break;
        case SDLK_r:
          g_inputState.keyPress |= KEY_REPEAT;
          break;
        case SDLK_d:
          g_inputState.keyPress |= KEY_DEFEND;
          break;
        default:
          break;
      }
      break;
    case SDL_KEYUP:
      switch(event->key.keysym.sym) {
        case SDLK_UP:
          if (g_inputState.dir == DIR_NORTH) {
            g_inputState.dir = g_inputState.prevdir;
          }
          g_inputState.prevdir = DIR_UNKNOWN;
          break;
        case SDLK_DOWN:
          if (g_inputState.dir == DIR_SOUTH) {
            g_inputState.dir = g_inputState.prevdir;
          }
          g_inputState.prevdir = DIR_UNKNOWN;
          break;
        case SDLK_LEFT:
          if (g_inputState.dir == DIR_WEST) {
            g_inputState.dir = g_inputState.prevdir;
          }
          g_inputState.prevdir = DIR_UNKNOWN;
          break;
        case SDLK_RIGHT:
          if (g_inputState.dir == DIR_EAST) {
            g_inputState.dir = g_inputState.prevdir;
          }
          g_inputState.prevdir = DIR_UNKNOWN;
          break;
        default: break;
      }
      break;
  }
}
static int event_filter(const SDL_Event *event) {
  switch(event->type) {
    // case SDL_VIDEORESIZE:
    //   video_resize(event->resize.w, event->resize.h);
    //   break;
    case SDL_QUIT:
      shut_down();
      exit(0);
  }
  keyboard_event_filter(event);
}
int poll_event(SDL_Event *event) {
  SDL_Event evt;
  int ret = SDL_PollEvent(&evt);
  if (!ret) {
    event_filter(&event);
  }
  if (event != NULL) {
    *event = evt;
  }
  return ret;
}
void process_event() {
  while(poll_event(NULL)) ;
}
