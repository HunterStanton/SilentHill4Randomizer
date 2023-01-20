#include "stdafx.h"
#include "sh4/game/gamemain/game.h"
#include "sh4/game/misc/misc_option.h"
#include "sh4/game/player/player.h"
#include "Randomizer.h"
#include <plog/Log.h>

// random damage algorithm has 50% chance of increasing damage by a range of percentage values
// percent increase is dependent on difficulty
// 0-25% on easy
// 0-50% on medium
// 0-100% on hard
injector::hook_back<int(__cdecl*)(int, float)> PlayerDamage;
int __cdecl PlayerDamageHook(int num, float damage)
{
	if (settings.bInGameOptions)
	{
		if (miscOptionGetPtr.fun()->random_damage == 1)
		{
			float percentChange;
			switch (gameW->level)
			{
			case EASY:
				percentChange = (rand() % 26) / 100.0;
				break;
			case NORMAL:
				percentChange = (rand() % 51) / 100.0;
				break;
			case HARD:
				percentChange = (rand() % 101) / 100.0;
				break;
			default:
				percentChange = (rand() % 26) / 100.0;
				break;
			}
			if (rand() % 2 == 0) {
				damage += damage * percentChange;
			}
		}
		return PlayerDamage.fun(num, damage);
	}
	else if (settings.bRandomDamage)
	{
		float percentChange;
		switch (gameW->level)
		{
		case EASY:
			percentChange = (rand() % 26) / 100.0;
			break;
		case NORMAL:
			percentChange = (rand() % 51) / 100.0;
			break;
		case HARD:
			percentChange = (rand() % 101) / 100.0;
			break;
		default:
			percentChange = (rand() % 26) / 100.0;
			break;
		}
		if (rand() % 2 == 0) {
			damage += damage * percentChange;
		}
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