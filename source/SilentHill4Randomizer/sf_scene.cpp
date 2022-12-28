#include "stdafx.h"
#include "Randomizer.h"
#include "sh4/game/misc/misc_option.h"
#include "sh4/sys/geometry/sf_scene.h"
#include <plog/Log.h>

injector::hook_back<void(__cdecl*)(Color*)> sfSceneSetFogColor;
void __cdecl sfSceneSetFogColorHook(Color* color)
{
	if (settings.bInGameOptions == true)
	{
		if (miscOptionGetPtr.fun()->fog_approaches == 1)
		{
			color->red = 255;
			color->blue = 255;
			color->green = 255;
		}
	}
	return sfSceneSetFogColor.fun(color);
}

injector::hook_back<void(__cdecl*)(float, unsigned char, float, unsigned char)> sfSceneSetFogPower;
void __cdecl sfSceneSetFogPowerHook(float nearPow, unsigned char nearPow2, float farPow, unsigned char farPow2)
{
	if (settings.bInGameOptions == true)
	{
		if (miscOptionGetPtr.fun()->fog_approaches == 1)
		{
			return sfSceneSetFogPower.fun(750, 1, 5000, 0xA0);
		}
	}
	return sfSceneSetFogPower.fun(nearPow, nearPow2, farPow, farPow2);
}