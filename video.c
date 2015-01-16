SDL_Surface *g_screen = NULL;
SDL_Surface *g_screenBak = NULL;
// SDL_Window *window = NULL;
// static SDL_Renderer *renderer = NULL;
// static SDL_Texture *texture = NULL;
static SDL_Surface *g_screenReal = NULL;
volatile bool g_renderPaused = false;
static bool scaleScreen = true;
static ushort g_width = 640;
static ushort g_height = 400;
static ushort g_shakeTime = 0;
static ushort g_shakeLevel = 0;
void set_palette(SDL_Color palette[256]) {
  SDL_SetPalette(g_screen, SDL_LOGPAL | SDL_PHYSPAL, palette, 0, 256);
  SDL_SetPalette(g_screenBak, SDL_LOGPAL | SDL_PHYSPAL, palette, 0, 256);
  SDL_SetPalette(g_screenReal, SDL_LOGPAL | SDL_PHYSPAL, palette, 0, 256);
}
int video_init(ushort width, ushort height) {
  g_width = width;
  g_height = height;
  g_screenReal = SDL_SetVideoMode(width, height, 8,
  SDL_HWSURFACE | SDL_RESIZABLE);
  g_screen = SDL_CreateRGBSurface(g_screenReal->flags & ~SDL_HWSURFACE,
  320, 200, 8,
  g_screenReal->format->Rmask, g_screenReal->format->Gmask,
  g_screenReal->format->Bmask, g_screenReal->format->Amask);
  return 0;
}
void video_update_screen(const SDL_Rect *rect) {
  SDL_Rect src,dest;
  short offset = 240-200;
  short screenRealHeight = g_screenReal->h;
  short screenRealY = 0;
  if (SDL_MUSTLOCK(g_screenReal)) {
    SDL_LockSurface(g_screenReal);
  }
  if (!scaleScreen) {
    screenRealHeight -= offset;
    screenRealY = offset/2;
  }
  if (rect!=NULL) {
    dest.x = (short)((int)(rect->x) * g_screenReal->w / g_screen->w);
    dest.y = (short)((int)(screenRealY + rect->y) * screenRealHeight / g_screen->h);
    dest.w = (ushort)((uint)(rect->w) * g_screenReal->w / g_screen->w);
    dest.h = (ushort)((uint)(rect->h) * screenRealHeight / g_screen->h);

    SDL_SoftStretch(g_screen, (SDL_Rect*)rect, g_screenReal, &dest);
    if (SDL_MUSTLOCK(g_screenReal)) {
      SDL_UnlockSurface(g_screenReal);
    }
    SDL_UpdateRect(g_screenReal, dest.x, dest.y, dest.w, dest.h);
  } else if (g_shakeTime !=0) {
    // shake the screen
    src.x = 0;
    src.y = 0;
    src.w = 320;
    src.h = 200-g_shakeLevel;
    dest.x = 0;
    dest.y = screenRealY;
    dest.w = 320 * g_screenReal->w / g_screen->w;
    dest.h = (200 - g_shakeLevel) * screenRealHeight / g_screen->h;
    if (g_shakeTime & 1) {
      src.y = g_shakeLevel;
    } else {
      dest.y = (screenRealY + g_shakeLevel) * screenRealHeight / g_screen->h;
    }
    SDL_SoftStretch(g_screen, &src, g_screenReal, &dest);
    if (g_shakeTime & 1) {
      dest.y = (screenRealY + screenRealHeight - g_shakeLevel) * screenRealHeight / g_screen->h;
    } else {
      dest.y = screenRealY;
    }
    dest.h = g_shakeLevel * screenRealHeight / g_screen->h;
    SDL_FillRect(g_screenReal, &dest, 0);
    if (SDL_MUSTLOCK(g_screenReal)) {
      SDL_UnlockSurface(g_screenReal);
    }
    SDL_UpdateRect(g_screenReal, 0, 0, g_screenReal->w, g_screenReal->h);
    g_shakeTime--;
  } else {
    dest.x = 0;
    dest.y = screenRealY;
    dest.w = g_screenReal->w;
    dest.h = screenRealHeight;
    SDL_SoftStretch(g_screen, NULL, g_screenReal, &dest);
    if (SDL_MUSTLOCK(g_screenReal)) {
      SDL_UnlockSurface(g_screenReal);
    }
    SDL_UpdateRect(g_screenReal, 0, 0, g_screenReal->w, g_screenReal->h);
  }
}
