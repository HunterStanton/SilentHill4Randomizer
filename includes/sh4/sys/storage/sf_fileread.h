#pragma once

extern injector::hook_back<void(__cdecl*)(unsigned int)> sfFileLoad;
void __cdecl sfFileLoadHook(unsigned int fileId);