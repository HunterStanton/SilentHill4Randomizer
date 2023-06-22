#include "stdafx.h"
#include "sh4/sglib/animation/sg_anime.h"
#include <plog/Log.h>

injector::hook_back<float(__cdecl*)(sgAnime*)> sgAnimeCurrentFloatFrame;

void InitializeSgAnimeFunctions()
{
	sgAnimeCurrentFloatFrame.fun = injector::auto_pointer(0x00417fd0);
}