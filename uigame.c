void draw_opening_menu_background() {
  char *buf;
  buf = (char*)malloc(320*200);
  MKF_decompress_chunk(buf, 320*200, MAINMENU_BACKGROUND_FBPNUM, g_globalVars->f.fpFBP);
  FBP_blit_to_surface(buf, g_screen);
  video_update_screen(NULL);
  free(buf);
}
int save_slot_menu(ushort defaultSlot) {
  // TODO
  return MENUITEM_VALUE_CANCELLED;
}
int opening_menu() {
  ushort selectedItem;
  ushort defaultItem = 0;
  MenuItem mainMenuItem[2] = {
    {0, MAINMENU_LABEL_NEWGAME, true, HEBI_XY(125,95)},
    {1, MAINMENU_LABEL_LOADGAME, true, HEBI_XY(125,112)}
  };
  // Play Music TODO
  draw_opening_menu_background();
  fade_in(0, false, 1);
  while(true) {
    selectedItem = read_menu(NULL, mainMenuItem, 2, defaultItem, MENUITEM_COLOR);
    if (selectedItem == 0 || selectedItem == MENUITEM_VALUE_CANCELLED) {
      // start a new game
      selectedItem = 0;
      break;
    } else {
      // load game
      selectedItem = save_slot_menu(1);
      if (selectedItem != MENUITEM_VALUE_CANCELLED) {
        break;
      }
      defaultItem = 1;
    }
  }
  // TODO PlayMusic
  fade_out(1);
  return (int)selectedItem;
}
