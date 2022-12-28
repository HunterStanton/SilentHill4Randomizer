#include "stdafx.h"
#include "Randomizer.h"
#include "sh4/game/enemy/en_kind.h"
#include "sh4/sys/storage/sf_fileread.h"
#include "sh4/game/misc/misc_option.h"
#include <plog/Log.h>

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
	if (enemyType == ENEMY_KIND_HYENA || enemyType == ENEMY_KIND_MUSH || enemyType == ENEMY_KIND_WHEEL || enemyType == ENEMY_KIND_JINMEN || enemyType == ENEMY_KIND_TWINS || enemyType == ENEMY_KIND_HIL || enemyType == ENEMY_KIND_NURSE)
	{
		// just rewriting the function entirely fixes the crash issues
		// bit of an ugly hack though
		EnemyFileMapping enemy = possibleEnemies[std::rand() / ((RAND_MAX + 1u) / possibleEnemies.size())];
		for (unsigned int i = 0; i < enemy.fileIds.size(); i++)
		{
			sfFileLoad.fun(enemy.fileIds[i]);
		}
		PLOG(plog::info) << "Spawning enemy type: " << enemy.kind;
		return enemy.tableAddr;
	}

	PLOG(plog::info) << "Spawning enemy type: " << enemyType;
	return EnemyKindTableGetAddress.fun(enemyType);
}