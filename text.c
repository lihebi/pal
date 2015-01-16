#define WORD_LENGTH 10

#define   FONT_COLOR_DEFAULT        0x4F
#define   FONT_COLOR_YELLOW         0x2D
#define   FONT_COLOR_RED            0x1A
#define   FONT_COLOR_CYAN           0x8D
#define   FONT_COLOR_CYAN_ALT       0x8C

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
