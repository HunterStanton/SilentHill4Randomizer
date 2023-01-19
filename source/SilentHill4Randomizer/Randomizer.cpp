#include "stdafx.h"
#include "Randomizer.h"
#include "sh4/game/enemy/en_kind.h"
#include "sh4/game/gamemain/game_item.h"
#include <plog/Log.h>
#include "plog/Initializers/RollingFileInitializer.h"

std::mt19937 mainRng = std::mt19937(std::time(0));
std::uniform_int_distribution<int> enemyGenerator(0, possibleEnemies.size() - 1);
std::uniform_int_distribution<int> consumableGenerator(ITEM_SMALL_BULLET, ITEM_FIRST_AID_KIT);
std::uniform_int_distribution<int> playerModelGenerator(0, playerModels.size() - 1);


void InitializeRandomness()
{
	// if global seed is not set, it will be -1
	// global seed -1 == "random" global seed
	if (settings.iGlobalSeed == -1)
	{
		settings.iGlobalSeed = std::time(0);
	}

	// shuffle both weapon pools
	std::shuffle(possibleWeapons.begin(), possibleWeapons.end(), mainRng);
	std::shuffle(possibleWeaponsWithExtra.begin(), possibleWeaponsWithExtra.end(), mainRng);

	// replace weapon spawns with unique weapons, avoiding duplicates
	for (auto& item : weaponSwaps) {
		item.second = possibleWeapons.front();
		possibleWeapons.erase(possibleWeapons.begin());
	}
	for (auto& item : weaponSwapsWithExtra) {
		item.second = possibleWeaponsWithExtra.front();
		possibleWeaponsWithExtra.erase(possibleWeaponsWithExtra.begin());
	}

	currentPlayerModel = playerModels[playerModelGenerator(mainRng)];

	PLOG(plog::info) << "Setting a random playermodel " << currentPlayerModel.filename;

}
void ReseedRNG(unsigned int seed)
{
	mainRng.seed(seed + settings.iGlobalSeed);
}