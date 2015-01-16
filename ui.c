#include "main.h"

LpSprite g_spriteUI = NULL;

int ui_init() {
  int size;
  size = MKF_get_chunk_size(CHUNKNUM_SPRITEUI, g_globalVars->f.fpData);
  g_spriteUI = (LpSprite)calloc(1,size);
  MKF_read_chunk(g_spriteUI, size, CHUNKNUM_SPRITEUI, g_globalVars->f.fpData);
  return 0;
}
