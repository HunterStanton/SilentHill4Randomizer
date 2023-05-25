#pragma once

extern injector::hook_back<int(__cdecl*)(int, int, int)> sfMcLoad;
extern injector::hook_back<int(__cdecl*)(int, int, int)> sfMcSaveCreate;
int __cdecl sfMcLoadHook(int port, int fn, int file_no);
int __cdecl sfMcSaveCreateHook(int port, int fn, int file_no);

struct ExtraSaveSettings
{
	// all the randomizer toggles + the saves seed
	unsigned int seed;
	unsigned int randomEnemies;
	unsigned int randomModels;
	unsigned int randomItems;
	unsigned int randomDamage;
	unsigned int extraContent;
	unsigned int fogApproaches;

	// any future settings or per-save stuff will go here
	unsigned int reserved[0x64];
};

extern ExtraSaveSettings perSaveSettings[32];

void InitializeSaveDataFunctions();