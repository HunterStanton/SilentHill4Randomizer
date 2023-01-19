#pragma once

extern injector::hook_back<void(__cdecl*)()> battle_anotherworld;
extern injector::hook_back<int(__cdecl*)()> normal_attack_all;
extern injector::hook_back<int(__cdecl*)(GameItem)> PlayerWeaponChargable;
void __cdecl battle_anotherworldHook();
int __cdecl normal_attack_allHook();
int __cdecl PlayerWeaponChargableHook(GameItem item);
void InitializePlayerBattleFunctions();