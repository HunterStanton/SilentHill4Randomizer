#pragma once
#include <stdio.h>
#include "FileHooks.h"
#include <random>

struct RandomizerSettings {
	bool bInGameOptions;
	bool bRandomEnemies;
	bool bRandomPlayerModels;
	bool bRandomItems;
	bool bRandomDamage;
	bool bExtraContent;
	bool bEnableHauntings;
	bool bFastSplash;
	bool bFogApproaches;
	int iGlobalSeed;
};

extern RandomizerSettings settings;

extern std::mt19937 mainRng;

// generates a 1 or 0
extern std::uniform_int_distribution<int> boolGenerator;

// generators for vanilla enemies, items, and consumables
extern std::uniform_int_distribution<int> enemyGenerator;
extern std::uniform_int_distribution<int> consumableGenerator;
extern std::uniform_int_distribution<int> weaponGenerator;

// generators for custom items/enemies/etc.
extern std::uniform_int_distribution<int> customWeaponGenerator;

extern PlayerModel currentPlayerModel;

void InitializeRandomness();
void ReseedRNG(unsigned int seed);