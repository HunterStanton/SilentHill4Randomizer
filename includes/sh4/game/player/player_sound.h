#pragma once
#include "sh4/game/gamemain/game.h"

struct PlayerSEFlags
{
	unsigned char r_foot;
	unsigned char l_foot;
	unsigned char tire;
	unsigned char die;
	unsigned char b_general;
	unsigned char b_g_val;
	unsigned char weapon;
	unsigned char weapon_val;
	unsigned char wall;
	int weapon_slot;
	float player_pan;
	float player_vol;
	float gaoh_time;
};

extern PlayerSEFlags* flags;
extern injector::hook_back<void(__cdecl*)(int)> se_call_swing;
extern injector::hook_back<void(__cdecl*)(int, _PLAYER_WORK*)> set_attack_se;
extern injector::hook_back<void(__cdecl*)(int)> set_battle_loop_se;
void set_attack_seHook(int unk, _PLAYER_WORK* pWork);
void InitializePlayerSoundFunctions();
