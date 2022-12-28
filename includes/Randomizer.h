#pragma once

struct RandomizerSettings {
	bool bInGameOptions;
	bool bRandomEnemies;
	bool bRandomPlayerModels;
	bool bRandomItems;
	bool bRandomDamage;
	bool bExtraContent;
	bool bEnableHauntings;
	bool bFastSplash;
};

extern RandomizerSettings settings;