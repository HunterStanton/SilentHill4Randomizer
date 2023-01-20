#include "stdafx.h"
#include "Randomizer.h"
#include <plog/Log.h>
#include "sh4/game/player/player_sound.h"
#include "sh4/game/player/player_another_ui.h"
#include "sh4/game/gamemain/game.h"
#include "sh4/sys/sound/sf_sound.h"

PlayerSEFlags* flags;

injector::hook_back<void(__cdecl*)(int)> se_call_swing;
injector::hook_back<void(__cdecl*)(int, _PLAYER_WORK*)> set_attack_se;
injector::hook_back<void(__cdecl*)(int)> set_battle_loop_se;
void __cdecl set_attack_seHook(int unk, _PLAYER_WORK* pWork)
{
	// PlayerSESetWeapon calls this function and puts the pWork pointer into EDI
	// So we move it onto the stack so we can do our own logic
	// wanted to avoid inline ASM but unless I rewrite all the functions involved from scratch, there is no way
	__asm {
		mov pWork, edi;
	}
	GameItem weaponKind = pWork->weapon_kind;
	set_attack_se.fun(unk, pWork);

	if (weaponKind == ITEM_SILVER_PIPE || weaponKind == ITEM_GOLD_PIPE)
	{
		if (*motion_stop == 0)
		{
			float vol = flags->player_vol;
			if ((gameW->stage == GAME_STAGE_LAST && gameW->scene == 2) && (1.0f < flags->player_vol))
			{
				vol = 1.0f;
			}
			sfSeCallEx.fun(0x9c62, vol, flags->player_pan, 0, 1);

			// move pWork pointer into EAX as that is what se_call_swing expects
			// works fine, need to make sure it doesn't cause any other issues
			__asm {
				mov eax, pWork;
			}

			se_call_swing.fun(0x7);
			return;
		}
	}

	if (weaponKind == ITEM_GREEN_HYPER_SPRAY)
	{
		set_battle_loop_se.fun(0xa028);
		return;
	}
}

void InitializePlayerSoundFunctions()
{
	set_attack_se.fun = injector::MakeCALL(0x00536936, set_attack_seHook, true).get();
	set_attack_se.fun = injector::MakeCALL(0x00536946, set_attack_seHook, true).get();
	set_battle_loop_se.fun = injector::auto_pointer(0x00535f80);
	se_call_swing.fun = injector::auto_pointer(0x00536250);

	flags = injector::auto_pointer(0x010a1d60);
}