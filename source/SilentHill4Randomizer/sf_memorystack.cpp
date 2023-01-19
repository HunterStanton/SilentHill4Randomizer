#include "stdafx.h"
#include "sh4/sys/apps/sf_memorystack.h"
#include <plog/Log.h>

void InitializeSfMemoryFunctions()
{
	// double sfMemoryStack size to allow more data loaded at once
	// the game normally only allows roughly 67mb, but by doubling this it prevents crashes related to exceeding this memory in large scenes when using the enemy randomizer
	injector::WriteMemory<int>(0x00551f98, 0x8000000, true);
	injector::WriteMemory<int>(0x00551fa9, 0x2000000, true);
	injector::WriteMemory<int>(0x00551fc5, 0x8000000, true);
}