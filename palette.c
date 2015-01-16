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
}
