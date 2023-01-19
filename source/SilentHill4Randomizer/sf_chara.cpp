#include "stdafx.h"
#include "sh4/sys/geometry/sf_chara.h"
#include <plog/Log.h>

injector::hook_back<sgBone*(__cdecl*)(sfCharacter*, unsigned int)> sfCharacterBone;

void InitializeSfCharacterFunctions()
{
	sfCharacterBone.fun = injector::auto_pointer(0x0055c370);
}