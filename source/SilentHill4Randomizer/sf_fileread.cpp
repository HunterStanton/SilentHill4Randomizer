#include "stdafx.h"
#include "sh4/sys/storage/sf_fileread.h"
#include <plog/Log.h>

injector::hook_back<void(__cdecl*)(unsigned int)> sfFileLoad;
void __cdecl sfFileLoadHook(unsigned int fileId)
{
	sfFileLoad.fun(fileId);
	return;
}