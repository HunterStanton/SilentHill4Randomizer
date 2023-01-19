#include "stdafx.h"
#include "sh4/sglib/animation/sg_anime.h"
#include <plog/Log.h>

injector::hook_back<float(__cdecl*)(sgAnime*)> sgAnimeCurrentFloatFrame;
injector::hook_back<int(__cdecl*)(sgAnmData*)> sgAnmDataIsLoop;

int __cdecl sgAnmDataIsLoopHook(sgAnmData* data)
{
	if (data != NULL)
		return data->loop;
	else
		return 1;
}

void InitializeSgAnimeFunctions()
{
	sgAnimeCurrentFloatFrame.fun = injector::auto_pointer(0x00417fd0);
	sgAnmDataIsLoop.fun = injector::MakeCALL(0x0048c26b, sgAnmDataIsLoopHook, true).get();
}