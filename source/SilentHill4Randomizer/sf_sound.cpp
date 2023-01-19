#include "stdafx.h"
#include "sh4/sys/sound/sf_sound.h"
#include "Randomizer.h"
#include <plog/Log.h>

injector::hook_back<int(__cdecl*)(int, float, float, int, int)> sfSeCallEx;
void InitializeSfSoundFunctions()
{
	sfSeCallEx.fun = injector::auto_pointer(0x0056c9b0);
}