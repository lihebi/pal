volatile InputState g_inputState;
void input_init() {
  memset((void*)&g_inputState, 0, sizeof(g_inputState));
  g_inputState.dir = DIR_UNKNOWN;
  g_inputState.prevdir = DIR_UNKNOWN;  
}
