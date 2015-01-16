void game_main() {
  uint _time;
  g_globalVars->curSaveSlot = (Byte)opening_menu();
  init_game_data(g_globalVars->curSaveSlot);
}
