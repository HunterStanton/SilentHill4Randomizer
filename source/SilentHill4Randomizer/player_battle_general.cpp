#include "stdafx.h"
#include "sh4/game/player/battle/player_battle_general.h"
#include "sh4/game/gamemain/game.h"
#include "Randomizer.h"
#include <plog/Log.h>

injector::hook_back<int(__cdecl*)()> motion_is_pipe;
int motion_is_pipeHook()
{
	switch (gameW->player->weapon_kind)
	{
	case ITEM_GREEN_HYPER_SPRAY:
		return 0;
	case ITEM_SILVER_PIPE:
	case ITEM_GOLD_PIPE:
		return 1;
	default:
		return motion_is_pipe.fun();
	}
}

void InitializePlayerBattleGeneralFunctions()
{
	motion_is_pipe.fun = injector::MakeCALL(0x0053d5b9, motion_is_pipeHook, true).get();
}