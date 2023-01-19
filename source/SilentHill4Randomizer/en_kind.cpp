#include "stdafx.h"
#include "Randomizer.h"
#include "sh4/game/enemy/en_kind.h"
#include "sh4/sys/storage/sf_fileread.h"
#include "sh4/game/misc/misc_option.h"
#include <plog/Log.h>

const std::vector<EnemyFileMapping> possibleEnemies = {
	{ENEMY_KIND_MUSH, {0xf000f066, 0xf000f067}, 0x00615368},
	{ENEMY_KIND_BUZZ, {0xf000f0b9}, 0x00615378},
	{ENEMY_KIND_JINMEN, {0xf000f071}, 0x006153b8},
	{ENEMY_KIND_TWINS, {0xf000f0bd}, 0x006153c8 },
	{ENEMY_KIND_HIL, {0xf000f06e}, 0x006153d8},
	{ENEMY_KIND_HYENA, {0xf000f068}, 0x006153e8},
	{ENEMY_KIND_KILLER, {0xf000f072, 0xf000f193}, 0x00615448} };

injector::hook_back<unsigned int(__cdecl*)(EnemyKind)> EnemyKindTableGetAddress;
unsigned int __cdecl EnemyKindTableGetAddressHook(EnemyKind enemyType)
{
	if (settings.bInGameOptions)
	{
		if (miscOptionGetPtr.fun()->random_enemies == 0)
		{
			return EnemyKindTableGetAddress.fun(enemyType);
		}
	}
	else if (settings.bRandomEnemies == false)
	{
		return EnemyKindTableGetAddress.fun(enemyType);
	}

	// shuffle all basic enemy types, no ghosts, no wall monster replacements, no boss replacements, no ghost replacements
	if (enemyType == ENEMY_KIND_HYENA || enemyType == ENEMY_KIND_MUSH || enemyType == ENEMY_KIND_JINMEN || enemyType == ENEMY_KIND_TWINS || enemyType == ENEMY_KIND_NURSE)
	{
		EnemyFileMapping enemy = possibleEnemies[enemyGenerator(mainRng)];
		PLOG(plog::info) << "Spawning enemy type: " << enemy.kind;
		return enemy.tableAddr;
	}

	PLOG(plog::info) << "Spawning enemy type: " << enemyType;
	return EnemyKindTableGetAddress.fun(enemyType);
}

void InitializeEnemyKindFunctions()
{
	EnemyKindTableGetAddress.fun = injector::MakeCALL(0x004852c7, EnemyKindTableGetAddressHook, true).get();
	EnemyKindTableGetAddress.fun = injector::MakeCALL(0x004623b1, EnemyKindTableGetAddressHook, true).get();
	EnemyKindTableGetAddress.fun = injector::MakeCALL(0x004853aa, EnemyKindTableGetAddressHook, true).get();
	EnemyKindTableGetAddress.fun = injector::MakeCALL(0x0052c634, EnemyKindTableGetAddressHook, true).get();
}