#pragma once

extern injector::hook_back<unsigned short* (__cdecl*)(int, int)> MessageAddress;
unsigned short* MessageAddressHook(int packid, int num);

char* convertMessage(const char* text);