#include "stdafx.h"
#include "Randomizer.h"
#include "CommonTypes.h"
#include "sh4/game/gamemain/game.h"
#include "sh4/game/gamemain/game_fileread.h"
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
			if (gameW->stage != GAME_STAGE_LAST && gameW->stage != GAME_STAGE_3LDK && gameW->stage != GAME_STAGE_TUNNEL && gameW->stage != GAME_STAGE_SPIRAL)
			{
				color->r = 255;
				color->g = 255;
				color->b = 255;
			}
		}
	}
	else
	{
		if (settings.bFogApproaches == true)
		{
			if (gameW->stage != GAME_STAGE_LAST && gameW->stage != GAME_STAGE_3LDK && gameW->stage != GAME_STAGE_TUNNEL && gameW->stage != GAME_STAGE_SPIRAL)
			{
				color->r = 255;
				color->g = 255;
				color->b = 255;
			}
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
			// do not override fog on the tunnel cutscenes, Henry's apartment, or in the final boss arena
			// it just looks weird and in the case of the final boss arena, is unplayable
			// TODO: figure out where else the fog shouldn't be applied
			if (gameW->stage != GAME_STAGE_LAST && gameW->stage != GAME_STAGE_3LDK && gameW->stage != GAME_STAGE_TUNNEL && gameW->stage != GAME_STAGE_SPIRAL)
			{
				PLOG(plog::info) << "Overriding fog for scene " << gameW->scene << " in stage " << stageNames[gameW->stage];
				return sfSceneSetFogPower.fun(750, 1, 5000, 0xA0);
			}
		}
	}
	else
	{
		if (settings.bFogApproaches == true)
		{
			if (gameW->stage != GAME_STAGE_LAST && gameW->stage != GAME_STAGE_3LDK && gameW->stage != GAME_STAGE_TUNNEL && gameW->stage != GAME_STAGE_SPIRAL)
			{
				PLOG(plog::info) << "Overriding fog for scene " << gameW->scene << " in stage " << stageNames[gameW->stage];
				return sfSceneSetFogPower.fun(750, 1, 5000, 0xA0);
			}
		}
	}
	return sfSceneSetFogPower.fun(nearPow, nearPow2, farPow, farPow2);
}

void InitializeSfSceneFunctions()
{
	sfSceneSetFogColor.fun = injector::MakeCALL(0x004d748c, sfSceneSetFogColorHook, true).get();
	sfSceneSetFogColor.fun = injector::MakeCALL(0x004d83fc, sfSceneSetFogColorHook, true).get();
	sfSceneSetFogColor.fun = injector::MakeCALL(0x004f13de, sfSceneSetFogColorHook, true).get();
	sfSceneSetFogColor.fun = injector::MakeCALL(0x004f1493, sfSceneSetFogColorHook, true).get();
	sfSceneSetFogColor.fun = injector::MakeCALL(0x004f15cf, sfSceneSetFogColorHook, true).get();
	sfSceneSetFogColor.fun = injector::MakeCALL(0x004f1e7a, sfSceneSetFogColorHook, true).get();
	sfSceneSetFogColor.fun = injector::MakeCALL(0x0054c343, sfSceneSetFogColorHook, true).get();
	sfSceneSetFogColor.fun = injector::MakeCALL(0x0054c625, sfSceneSetFogColorHook, true).get();

	sfSceneSetFogPower.fun = injector::MakeCALL(0x004d74be, sfSceneSetFogPowerHook, true).get();
	sfSceneSetFogPower.fun = injector::MakeCALL(0x004d842e, sfSceneSetFogPowerHook, true).get();
	sfSceneSetFogPower.fun = injector::MakeCALL(0x004f13f4, sfSceneSetFogPowerHook, true).get();
	sfSceneSetFogPower.fun = injector::MakeCALL(0x004f14ab, sfSceneSetFogPowerHook, true).get();
	sfSceneSetFogPower.fun = injector::MakeCALL(0x0054c33a, sfSceneSetFogPowerHook, true).get();
	sfSceneSetFogPower.fun = injector::MakeCALL(0x0055e4b7, sfSceneSetFogPowerHook, true).get();
	sfSceneSetFogPower.fun = injector::MakeCALL(0x0055e577, sfSceneSetFogPowerHook, true).get();
	sfSceneSetFogPower.fun = injector::MakeCALL(0x0055e5ac, sfSceneSetFogPowerHook, true).get();
	sfSceneSetFogPower.fun = injector::MakeCALL(0x0055e5e8, sfSceneSetFogPowerHook, true).get();
}