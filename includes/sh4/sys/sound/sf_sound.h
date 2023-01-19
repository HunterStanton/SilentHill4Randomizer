#pragma once

extern injector::hook_back<int(__cdecl*)(int, float, float, int, int)> sfSeCallEx;
void InitializeSfSoundFunctions();