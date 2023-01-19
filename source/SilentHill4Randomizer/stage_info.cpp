#include "stdafx.h"
#include "sh4/game/gamemain/stage_info.h"
#include <plog/Log.h>

injector::hook_back<int(__cdecl*)()> StageInfoIsLatterHalf;

void InitializeStageInfoFunctions()
{
	StageInfoIsLatterHalf.fun = injector::auto_pointer(0x004fc830);
}