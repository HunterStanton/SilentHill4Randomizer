#pragma once

extern injector::hook_back<int(__cdecl*)(unsigned int)> sfFileLoad;
void InitializeSfFileLoadFunctions();