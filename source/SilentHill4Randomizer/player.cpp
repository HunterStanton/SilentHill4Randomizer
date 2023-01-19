#include "stdafx.h"
#include "sh4/game/misc/misc_option.h"
#include "sh4/game/player/player.h"
#include "Randomizer.h"
#include <plog/Log.h>

injector::hook_back<int(__cdecl*)(int, float)> PlayerDamage;
int __cdecl PlayerDamageHook(int num, float damage)
{
	if (settings.bInGameOptions)
	{
		if (miscOptionGetPtr.fun()->random_damage == 1)
		{
			return PlayerDamage.fun(num, static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 100)));
		}
		else
		{
			return PlayerDamage.fun(num, damage);
		}
	}
	else if (settings.bRandomDamage)
	{
		return PlayerDamage.fun(num, static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 100)));
	}
	return PlayerDamage.fun(num, damage);
}

void InitializePlayerFunctions()
{
	PlayerDamage.fun = injector::MakeCALL(0x00450a77, PlayerDamageHook, true).get();
	PlayerDamage.fun = injector::MakeCALL(0x005391c4, PlayerDamageHook, true).get();
	PlayerDamage.fun = injector::MakeCALL(0x005391eb, PlayerDamageHook, true).get();
	PlayerDamage.fun = injector::MakeCALL(0x005392ab, PlayerDamageHook, true).get();
	PlayerDamage.fun = injector::MakeCALL(0x0053e6e8, PlayerDamageHook, true).get();
	PlayerDamage.fun = injector::MakeCALL(0x0053eacd, PlayerDamageHook, true).get();
	PlayerDamage.fun = injector::MakeCALL(0x0053ee0e, PlayerDamageHook, true).get();
}