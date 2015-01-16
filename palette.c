// get palette from pat.mkf
SDL_Color *get_palette(int paletteId, bool night) {
  static SDL_Color palette[256];
  char buf[1536];
  int i;
  FILE *fp;
  fp = fopen("PAT.MKF", "rb");
  i = MKF_read_chunk(buf, 1536, paletteId, fp);
  fclose(fp);
  if (i<=256*3) {
    // no night colors in the palette
    night = false;
  }
  for (i=0;i<256;i++) {
    palette[i].r = buf[(night?256*3:0) + i*3] << 2;
    palette[i].g = buf[(night?256*3:0) + i*3 +1] <<2;
    palette[i].b = buf[(night?256*3:0) + i*3 +2] <<2;
  }
  return palette;
}
void fade_in(int paletteId, bool night, int delay) {
  int i,j;
  uint time;
  SDL_Color *palette;
  SDL_Color newpalette[256];
  palette = get_palette(paletteId, night);
  time = SDL_GetTicks() + delay*10*60;
  while(true) {
    j = (int)(time-SDL_GetTicks()) / delay / 10;
    if (j<0) {
      break;
    }
    j=60-j;
    for (i=0;i<256;i++) {
      newpalette[i].r = (palette[i].r * j) >> 6;
      newpalette[i].g = (palette[i].g * j) >> 6;
      newpalette[i].b = (palette[i].b * j) >> 6;
    }
    video_set_palette(newpalette);
  }
}

void fade_out(int delay) {
  int i,j;
  uint time;
  for (i=0;i<256;i++) {
    palette[i] = video_get_palette()[i];
  }
  time = SDL_GetTicks() + delay * 10 * 60;
  while(true) {
    j = (int)(time - SDL_GetTicks()) / delay / 10;
    if (j<0) {
      break;
    }
    for (i=0;i<256;i++) {
      newpalette[i].r = (palette[i].r * j) >> 6;
      newpalette[i].g = (palette[i].g * j) >> 6;
      newpalette[i].b = (palette[i].b * j) >> 6;
    }
    video_set_palette(newpalette);
    delay(10);
  }
  memset(newpalette, 0, sizeof(newpalette));
  video_set_palette(newpalette);
}
