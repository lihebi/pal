void draw_char_on_surface(ushort c, SDL_Surface *surface, uint pos, Byte color) {
  int i,j,dx;
  int x = HEBI_X(pos), y=HEBI_Y(pos);
  Byte *p;
  Byte ch1, ch2;
  // locate this character
  ch1 = c & 0xff;
  ch2 = c >> 8;
  // TODO big5?
  if (ch2 < 0xa1) {
    p = &big5font[((ch1 - 0xa1) * 157 + ch2 - 0x40) << 5] +8;
  } else {
    p = &big6font[((ch1 - 0xa1) * 157 + 63 + ch2 - 0xa1) << 5] +8;
  }
  // draw to surface
  if (y >= surface-h) return;
  y *= surface->pitch;
  for (i=0;i<32;i++) {
    dx = x + ((i & 1) << 3);
    for (j=0;j<8;j++) {
      if (p[i] & (1 << (7-j))) {
        if (dx < surface->w) {
          ((Byte*)(surface->pixels))[y+dx] = color;
        } else {
          break;
        }
      }
      dx++;
    }
    y += (i & 1) * surface->pitch;
    if (y / surface->pitch >= surface-h) {
      break;
    }
  }
}
void draw_ascii_char_on_surface(Byte c, SDL_Surface *surface, uint pos, Byte color) {
  int i,j,dx;
  int x = HEBI_X(pos), y = HEBI_Y(pos);
  Byte *p;
  p = &iso_font[(int)(c & ~128) * 15];
  // draw
  if (y >= surface-h) return;
  y *= surface->pitch;
  for (i=0;i<15;i++) {
    dx = x;
    for (j=0;j<8;j++) {
      if (p[i] & (1 << j)) {
        if (dx < surface-w) {
          ((Byte*)(surface->pixels))[y+dx] = color;
        } else {
          break;
        }
      }
      dx++;
    }
    y += surface->pitch;
    if (y / surface->pitch >= surface-h) {
      break;
    }
  }
}
