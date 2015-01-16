// NO NEED
int MKF_get_chunk_count(FILE *fp) {
  int count;
  fseek(fp, 0, SEEK_SET);
  fread(&count, sizeof(int), 1, fp);
  count = (SWAP32(count)-4)/4;
  return count;
}
// get the size of a chunk in an MKF archive
int MKF_get_chunk_size(uint chunkId, FILE *fp) {
  uint offset = 0;
  uint nextOffset = 0;
  // uint chunkCount = 0;
  // chunkCount = MKF_get_chunk_count(fp);
  // if (chunkId >= chunkCount) {
  //   return -1;
  // }
  fseek(fp, 4*chunkId, SEEK_SET);
  fread(&offset, sizeof(uint), 1, fp);
  fread(&nextOffset, sizeof(uint), 1, fp);
  offset = SWAP32(offset);
  nextOffset = SWAP32(nextOffset);
  return nextOffset-offset;
}
int MKF_read_chunk(char *buffer, uint size, uint chunkId, FILE *fp) {
  uint offset = 0;
  uint nextOffset = 0;
  // uint chunkCount;
  uint chunkLen;
  // chunkCount = MKF_get_chunk_count(fp);
  // if (chunkId >= chunkCount) {
  //   return -1;
  // }
  fseek(fp, 4*chunkId, SEEK_SET);
  fread(&offset, 4, 1, fp);
  fread(&nextOffset, 4, 1, fp);
  offset = SWAP32(offset);
  nextOffset = SWAP32(nextOffset);
  chunkLen = nextOffset - offset;
  fseek(fp, offset, SEEK_SET);
  fread(buffer, chunkLen, 1, fp);
  return (int)chunkLen;
}
int MKF_decompress_chunk(char *buf, uint size, uint chunkId, FILE *fp) {
  char *_buf;
  int len;
  len = MKF_get_chunk_size(chunkId, fp);
  _buf = (char*)malloc(len);
  MKF_read_chunk(_buf, len, chunkId, fp);
  len = decompress(_buf, buf, size);
  free(_buf);
  return len;
}
int FBP_blit_to_surface(Byte *bitmapFBP, SDL_Surface *surface) {
  int x,y;
  Byte *p;
  for (y=0;y<200;y++) {
    p = (Byte*)(surface->pixels) + y*surface->pitch;
    for (x=0;x<320;x++) {
      *(p++) = *(bitmapFBP++);
    }
  }
  return 0;
}
void delay(uint ms) {
  uint t = SDL_GetTicks() + ms;
  while(PAL_PollEvent(NULL));
  while(SDL_GetTicks()<t) {
    SDL_Delay(1);
    while(PAL_PollEvent(NULL));
  }
}
void trim(char *str) {
  int pos=0;
  char *dest = str;
  while(str[pos] <= ' ' && str[pos] >0) {
    pos++;
  }
  while(str[pos]) {
    *(dest++) = str[pos];
    pos++;
  }
  *(dest--) = '\0';
  while(dest >= str && *dest <= ' ' && *dest >0) {
    *(dest--) = '\0';
  }
}
