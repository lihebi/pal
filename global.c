#include "main.h"

#define DO_BYTESWAP(buf, size)                                   \
for (i = 0; i < (size) / 2; i++)                              \
{                                                             \
  ((LPWORD)(buf))[i] = SWAP16(((LPWORD)(buf))[i]);           \
}

#define LOAD_DATA(buf, size, chunknum, fp)                       \
{                                                             \
  MKF_read_chunk((LPBYTE)(buf), (size), (chunknum), (fp)); \
  DO_BYTESWAP(buf, size);                                    \
}

LpGlobalVars g_globalVars = NULL;
int global_init() {
  if (g_globalVars == NULL) {
    g_globalVars = (LpGlobalVars)calloc(1, sizeof(GlobalVars));
  }
  g_globalVars->f.fpFBP = fopen("FBP.MKF", "rb");
  g_globalVars->f.fpMGO = fopen("MGO.MKF", "rb");
  g_globalVars->f.fpBALL = fopen("BALL.MKF", "rb");
  g_globalVars->f.fpDATA = fopen("DATA.MKF", "rb");
  g_globalVars->f.fpF = fopen("F.MKF", "rb");
  g_globalVars->f.fpFIRE = fopen("FIRE.MKF", "rb");
  g_globalVars->f.fpRGM = fopen("RGM.MKF", "rb");
  g_globalVars->f.fpSSS = fopen("SSS.MKF", "rb");
  g_globalVars->curSaveSlot = 1;
  return 0;
}
static void read_global_game_data() {
  const GameData *p = &g_globalVars->g;
  uint i;
  LOAD_DATA(p->scriptEntry, p->nScriptEntry * sizeof(ScriptEntry),
  4, g_globalVars->f.fpSSS);
  LOAD_DATA(p->store, p->nStore * sizeof(Store), 0, g_globalVars->f.fpDATA);
  LOAD_DATA(p->enemy, p->nEnemy * sizeof(Enemy), 1, g_globalVars->f.fpDATA);
  LOAD_DATA(p->enemyTeam, p->nEnemyTeam * sizeof(EnemyTeam),
  2, g_globalVars->fpDATA);
  LOAD_DATA(p->magic, p->nMagic * sizeof(Magic), 4, g_globalVars->f.fpDATA);
  LOAD_DATA(p->battleField, p->nBattleField * sizeof(BattleField),
  5, g_globalVars->f.fpDATA);
  LOAD_DATA(p->levelUpMagic, p->nLevelUpMagic * sizeof(LevelUpMagicAll),
  6, g_globalVars->f.fpDATA);
  LOAD_DATA(p->battleEffectIndex, sizeof(p->battleEffectIndex),
  11, g_globalVars->f.fpDATA);
  MKF_read_chunk((Byte*)&(p->enemyPos), sizeof(p->enemyPos),
  13, g_globalVars->f.fpDATA);
  DO_BYTESWAP(&(p->enemyPos), sizeof(p->enemyPos));
  MKF_read_chunk((Byte*)(p->levelUpExp), sizeof(p->levelUpExp),
  14, g_globalVars->f.fpDATA);
  DO_BYTESWAP(p->levelUpExp, sizeof(p->levelUpExp));
}
static void init_global_game_data() {
  int len;

#define PAL_DOALLOCATE(fp, num, type, lptype, ptr, n) \
  { \
    len = MKF_get_chunk_size(num, fp); \
    ptr = (lptype)malloc(len); \
    n = len / sizeof(type); \
    if (ptr == NULL) \
    { \
      exit(244); \
    } \
  }

  if (g_globalVars->g.eventObject == NULL) {
    PAL_DOALLOCATE(g_globalVars->f.fpSSS, 0, EventObject, LpEventObject,
    g_globalVars->g.eventObject, g_globalVars->g.nEventObject);
    PAL_DOALLOCATE(g_globalVars->f.fpSSS, 4, ScriptEntry, LpScriptEntry,
    g_globalVars->g.scriptEntry, g_globalVars->g.nScriptEntry);
    PAL_DOALLOCATE(g_globalVars->f.fpDATA, 0, Store, LpStore,
    g_globalVars->g.store, g_globalVars->g.nStore);
    PAL_DOALLOCATE(g_globalVars->f.fpDATA, 1, Enemy, LpEnemy,
    g_globalVars->g.enemy, g_globalVars->g.nEnemy);
    PAL_DOALLOCATE(g_globalVars->f.fpDATA, 2, EnemyTeam, LpEnemyTeam,
    g_globalVars->g.enemyTeam, g_globalVars->g.nEnemyTeam);
    PAL_DOALLOCATE(g_globalVars->f.fpDATA, 4, Magic, LpMagic,
    g_globalVars->g.magic, g_globalVars->g.nMagic);
    PAL_DOALLOCATE(g_globalVars->f.fpDATA, 5, BattleField, LpBattleField,
    g_globalVars->g.battleField, g_globalVars->g.nBattleField);
    PAL_DOALLOCATE(g_globalVars->f.fpDATA, 6, LevelUpMagicAll, LpLevelUpMagicAll,
    g_globalVars->g.levelUpMagic, g_globalVars->g.nLevelUpMagic);
    // TODO NOW read global game data
    read_global_game_data();
  }
#undef PAL_DOALLOCATE
}
void init_game_data(int saveSlot) {
  init_global_game_data();
}
