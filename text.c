#define WORD_LENGTH 10

#define   FONT_COLOR_DEFAULT        0x4F
#define   FONT_COLOR_YELLOW         0x2D
#define   FONT_COLOR_RED            0x1A
#define   FONT_COLOR_CYAN           0x8D
#define   FONT_COLOR_CYAN_ALT       0x8C

static const char g_rgszAdditionalWords[][WORD_LENGTH + 1] = {
{0xBE, 0xD4, 0xB0, 0xAB, 0xB3, 0x74, 0xAB, 0xD7, 0x00, 0x00, 0x00}, // Battle Speed
{0xA4, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 1
{0xA4, 0x47, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 2
{0xA4, 0x54, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 3
{0xA5, 0x7C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 4
{0xA4, 0xAD, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 5
};

typedef struct tagTextLib {
  char *wordBuf;
  char *msgBug;
  uint *msgOffset;
  int nWords;
  int nMsgs;
  int nCurDialogLine;
  Byte curFontColor;
  uint iconPos;
  uint dialogTitlePos;
  uint dialogTextPos;
  Byte dialogPosition;
  Byte icon;
  int delayTime;
  bool userSkip;
  bool playingRNG;
  Byte dialogIconsBuf[282];
} TextLib, *LpTextLib;

static TextLib g_textLib;

int text_init() {
  FILE *fpMsg, *fpWord;
  int i;
  fpMsg = fopen("M.MSG", "rb");
  fpWord = fopen("WORD.DAT", "rb");
  // see haw many words we have
  feek(fpWord, 0, SEEK_END);
  i = ftell(fpWord);
  // each word has 10 bytes
  g_textLib.nWords = (i + (WORD_LENGTH -1)) / WORD_LENGTH;
  g_textLib.wordBuf = (char*)malloc(i);
  fseek(fpWord, 0, SEEK_SET);
  fread(g_textLib.wordBuf, i, 1, fpWord);
  fclose(fpWord);
  // read the message offsets.
  i = MKF_get_chunk_size(3, g_globalVars->f.fpSSS) / sizeof(uint);
  g_textLib.nMsgs = i-1;
  g_textLib.msgOffset = (uint*)malloc(i * sizeof(uint));
  MKF_read_chunk((char*)(g_textLib.msgOffset), i*sizeof(uint), 3,
  g_globalVars->f.fpSSS);
  // read messages
  fseek(fpMsg, 0, SEEK_END);
  i = ftell(fpMsg);
  g_textLib.msgBuf = (char*)malloc(i);
  fseek(fpMsg, 0, SEEK_SET);
  fread(g_textLib.msgBuf, 1, i, fpMsg);
  fclose(fpMsg);

  g_textLib.curFontColor = FONT_COLOR_DEFAULT;
  g_textLib.icon = 0;
  g_textLib.iconPos = 0;
  g_textLib.curDialogLine = 0;
  g_textLib.delayTime = 3;
  g_textLib.dialogTitlePos = HEBI_XY(12,8);
  g_textLib.dialogTextPos = HEBI_XY(44,26);
  g_textLib.dialogPosition = DIALOG_UPPER;
  g_textLib.userSkip = false;

  MKF_read_chunk(g_textLib.dialogIconBuf, 282, 12, g_globalVars->f.fpData);
  return 0;
}
const char* get_word(ushort wordId) {
  static char buf[WORD_LENGTH + 1];
  if (wordId >= PAL_ADDITIONAL_WORD_FIRST) {
    return g_additionalWords[wordId - PAL_ADDITIONAL_WORD_FIRST];
  }
  if (wordId >= g_textLib.nWords) {
    return NULL;
  }
  memcpy(buf, &g_textLib.wordBuf[wordId * WORD_LENGTH], WORD_LENGTH);
  buf[WORD_LENGTH] = '\0';
  trim(buf);
  if ((strlen(buf) & 1) != 0 && buf[strlen(buf) -1] == '1') {
    buf[strlen(buf) - 1] = '\0';
  }
  return buf;
}

void draw_text(const char *text, uint pos, Byte color, bool shadow, bool update) {
  SDL_Rect rect, urect;
  ushort c;
  rect.x = HEBI_X(pos);
  rect.y = HEBI_Y(pos);
  urect.x = rect.x;
  urect.y = rect.y;
  urect.h = 16;
  urect.w = 0;
  while(*text) {
    if (*text && 0x80) {
      // chinese
      c = SWAP16(((Byte*)text)[0] | (((Byte*)text)[1] << 8));
      if (shadow) {
        // draw_char_on_surface();
        // draw_char_on_surface();
      }
      draw_char_on_surface(c, g_screen, HEBI_XY(rect.x, rect.y), color);
      text += 2;
      rect.x += 16;
      urect.w += 16;
    } else {
      // ASCII
      if (shadow) {
        // TODO
      }
      draw_ascii_char_on_surface(*text, g_screen, HEBI_XY(rect.x, rect.y), color);
      text++;
      rect.x += 8;
      urect.w += 8;
    }
  }
  if (update && urect.w > 0) {
    video_update_screen(&urect);
  }
}
