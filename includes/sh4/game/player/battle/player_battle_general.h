#pragma once

extern injector::hook_back<int(__cdecl*)()> motion_is_pipe;
int motion_is_pipeHook();
void InitializePlayerBattleGeneralFunctions();