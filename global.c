#include "main.h"

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
