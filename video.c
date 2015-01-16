SDL_Surface *screen = NULL;
SDL_Surface *screenBak = NULL;
// SDL_Window *window = NULL;
// static SDL_Renderer *renderer = NULL;
// static SDL_Texture *texture = NULL;
static SDL_Surface *screenReal = NULL;
volatile bool g_renderPaused = false;
static bool scaleScreen = true;
static ushort g_width = 640;
static ushort g_height = 400;
void set_palette(SDL_Color palette[256]) {
  SDL_SetPalette(screen, SDL_LOGPAL | SDL_PHYSPAL, palette, 0, 256);
  SDL_SetPalette(screenBak, SDL_LOGPAL | SDL_PHYSPAL, palette, 0, 256);
  SDL_SetPalette(screenReal, SDL_LOGPAL | SDL_PHYSPAL, palette, 0, 256);
}
int video_init(ushort width, ushort height) {
  g_width = width;
  g_height = height;
  // window = SDL_CreateWindow("Pal", SDL_WINDOWPOS_UNDEFINED,
  // SDL_WINDOWPOS_UNDEFINED, width, height,
  // SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
  // renderer = SDL_CreateRenderer(window, -1, 0);
  // screen = SDL_CreateRGBSurface(SDL_SWSURFACE, 320, 200, 8, 0, 0, 0, 0);
  // screenBak = SDL_CreateRGBSurface(SDL_SWSURFACE, 320, 200, 8, 0, 0, 0, 0);
  // screenReal = SDL_CreateRGBSurface(SDL_SWSURFACE, 320, 200, 32,
  // 0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000);
  // texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888,
  // SDL_TEXTUREACCESS_STREAMING, 320, 200);
  // SDL_Color palette[256] = {0};
  // SDL_Surface *p;
  // palette[0].r = palette[0].g = palette[0].b = palette[0].a = 0;
  // palette[1].r = palette[1].g = palette[1].b = palette[1].a = 255;
  // SDL_FillRect(screenBak, NULL, 0);
  // set_palette(palette);
  screenReal = SDL_SetVideoMode(width, height, 8,
  SDL_HWSURFACE | SDL_RESIZABLE);
  screen = SDL_CreateRGBSurface(screenReal->flags & ~SDL_HWSURFACE,
  320, 200, 8,
  screenReal->format->Rmask, screenReal->format->Gmask,
  screenReal->format->Bmask, screenReal->format->Amask);
  return 0;
}
