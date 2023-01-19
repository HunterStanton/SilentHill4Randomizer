#include "stdafx.h"
#include "sh4/sys/storage/sf_fileread.h"
#include <plog/Log.h>

injector::hook_back<int(__cdecl*)(unsigned int)> sfFileLoad;
void InitializeSfFileLoadFunctions()
{
	// increase buffer size for wp_model.bin
	injector::WriteMemory<int>(0x0069fab0, 0x400000, true);

	sfFileLoad.fun = injector::auto_pointer(0x00573470);
}