#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <plog/Log.h>
#include "plog/Initializers/RollingFileInitializer.h"
#include "sh4/Enemy.h"

using namespace std;

injector::hook_back<int(__cdecl*)(int, float)> PlayerDamage;
int __cdecl PlayerDamageHook(int unknown, float damage)
{
	// randomly adds or subtracts values from damage
	PLOG(plog::info) << "Player took damage: " << damage;
	return PlayerDamage.fun(unknown, damage);
}

// the IDs of most of the common enemies besides the wheelchair as its crashy on non-hospital rooms
std::vector<EnemyKind> possibleEnemies = { ENEMY_KIND_MUSH, ENEMY_KIND_BUZZ, ENEMY_KIND_WALLMAN, ENEMY_KIND_JINMEN, ENEMY_KIND_TWINS, ENEMY_KIND_HIL, ENEMY_KIND_HYENA, ENEMY_KIND_KILLER, ENEMY_KIND_NURSE };


injector::hook_back<int* (__cdecl*)(EnemyKind)> EnemyKindTableGetAddress;
int* __cdecl EnemyKindTableGetAddressHook(EnemyKind enemyId)
{
	PLOG(plog::info) << "Spawning enemy type: " << enemyId;

	// shuffle all basic enemy types, no ghosts, no wall monster replacements, no boss replacements
	if (enemyId == ENEMY_KIND_HYENA || enemyId == ENEMY_KIND_MUSH || enemyId == ENEMY_KIND_BUZZ || enemyId == ENEMY_KIND_MM || enemyId == ENEMY_KIND_WHEEL || enemyId == ENEMY_KIND_JINMEN || enemyId == ENEMY_KIND_TWINS || enemyId == ENEMY_KIND_HIL)
	{

		enemyId = possibleEnemies[std::rand() / ((RAND_MAX + 1u) / possibleEnemies.size())];
	}

	return EnemyKindTableGetAddress.fun(enemyId);
}

injector::hook_back<void(__cdecl*)(int)> sfFileLoad;
void __cdecl sfFileLoadHook(int fileId)
{
	return sfFileLoad.fun(fileId);
}

// the game references a lookup table to know what files it should load, which contains only the files for enemies normally in that room
// but the game wont spawn enemies unless their files are loaded
// so we just load the original files, and then also load the .bin files for every enemy
// this is not really a memory or performance concern the game is almost 20 years old and the amount of memory needed to load it all at once is less than 40mb
injector::hook_back<void(__cdecl*)(int, int)> GameFileLoadScene;
void __cdecl GameFileLoadSceneHook(int scene, int stage)
{
	PLOG(plog::info) << "Loaded scene " << scene << " on stage " << stage;

	GameFileLoadScene.fun(scene, stage);
	sfFileLoad.fun(0xf000f020);
	sfFileLoad.fun(0xf000f064);
	sfFileLoad.fun(0xf000f065);
	sfFileLoad.fun(0xf000f066);
	sfFileLoad.fun(0xf000f067);
	sfFileLoad.fun(0xf000f068);
	sfFileLoad.fun(0xf000f069);
	sfFileLoad.fun(0xf000f06a);
	sfFileLoad.fun(0xf000f06b);
	sfFileLoad.fun(0xf000f06c);
	sfFileLoad.fun(0xf000f06d);
	sfFileLoad.fun(0xf000f06e);
	sfFileLoad.fun(0xf000f06f);
	sfFileLoad.fun(0xf000f070);
	sfFileLoad.fun(0xf000f071);
	sfFileLoad.fun(0xf000f072);
	sfFileLoad.fun(0xf000f0b7);
	sfFileLoad.fun(0xf000f0b8);
	sfFileLoad.fun(0xf000f0b9);
	sfFileLoad.fun(0xf000f0ba);
	sfFileLoad.fun(0xf000f0bb);
	sfFileLoad.fun(0xf000f0bc);
	sfFileLoad.fun(0xf000f0bd);
	sfFileLoad.fun(0xf000f0be);
	sfFileLoad.fun(0xf000f20b);
	sfFileLoad.fun(0xf000f0e7);
	sfFileLoad.fun(0xf000f0e8);
	sfFileLoad.fun(0xf000f0e9);
	sfFileLoad.fun(0xf000f0ea);
	sfFileLoad.fun(0xf000f0eb);
	sfFileLoad.fun(0xf000f0ec);
	sfFileLoad.fun(0xf000f0ed);
	sfFileLoad.fun(0xf000f0ee);
	sfFileLoad.fun(0xf000f11f);
	sfFileLoad.fun(0xf000f120);
	sfFileLoad.fun(0xf000f121);
	sfFileLoad.fun(0xf000f122);
	sfFileLoad.fun(0xf000f123);
	sfFileLoad.fun(0xf000f193);
	sfFileLoad.fun(0xf000f19d);
	sfFileLoad.fun(0xf000f19e);
	sfFileLoad.fun(0xf000f19f);
	sfFileLoad.fun(0xf000f1a0);
	sfFileLoad.fun(0xf000f1dc);
	return;
}

std::vector<LPCSTR> playerModels = { ".\\data\\henry01.bin", ".\\data\\randomizer_eileen.bin", ".\\data\\randomizer_eileen_sexy.bin" };

// didn't want to dig super deep in the game code so this is the basic file reading function
injector::hook_back<void(__cdecl*)(LPCSTR, HANDLE*)> LoadFile;
void __cdecl LoadFileHook(LPCSTR file, HANDLE* handle)
{
	PLOG(plog::info) << "Loading file " << file;

	if (strcmp(file, ".\\data\\henry01.bin") == 0)
	{

		LPCSTR model = playerModels[std::rand() / ((RAND_MAX + 1u) / playerModels.size())];

		// this needs to be done or it will always give you the last item in the player model vector, every time apparently
		for (int i = 0; i < 10; i++)
		{
			model = playerModels[std::rand() / ((RAND_MAX + 1u) / playerModels.size())];
		}

		PLOG(plog::info) << "Setting a random playermodel " << model;

		return LoadFile.fun(model, handle);
	}

	return LoadFile.fun(file, handle);
}


void Init()
{
	// seed random
	std::srand(std::time(nullptr));

	plog::init(plog::info, "randomizer.log");
	PLOG(plog::info) << "Silent Hill 4 Randomizer Loaded";

	CIniReader iniReader("randomizer.ini");
	bool bRandomPlayerModels = iniReader.ReadInteger("RANDOMIZER", "RandomEnemies", 1) != 0;
	bool bRandomEnemies = iniReader.ReadInteger("RANDOMIZER", "RandomPlayerModel", 1) != 0;

	bool bLogDamage = iniReader.ReadInteger("LOGGING", "LogDamage", 1) != 0;

	auto pattern = hook::pattern("E8 A3 34 00 00");

	if (bRandomEnemies)
	{
		GameFileLoadScene.fun = injector::MakeCALL(pattern.count(1).get(0).get<uint32_t>(0), GameFileLoadSceneHook, true).get();

		pattern = hook::pattern("E8 E5 FE 07 00");
		sfFileLoad.fun = injector::MakeCALL(pattern.count(1).get(0).get<uint32_t>(0), sfFileLoadHook, true).get();

		pattern = hook::pattern("E8 17 3A F4 FF");
		EnemyKindTableGetAddress.fun = injector::MakeCALL(pattern.count(1).get(0).get<uint32_t>(0), EnemyKindTableGetAddressHook, true).get();
	}

	if (bRandomPlayerModels)
	{
		pattern = hook::pattern("E8 0D FE FF FF");
		LoadFile.fun = injector::MakeCALL(pattern.count(2).get(1).get<uint32_t>(0), LoadFileHook, true).get();
		pattern = hook::pattern("E8 42 FE FF FF");
		LoadFile.fun = injector::MakeCALL(pattern.count(3).get(1).get<uint32_t>(0), LoadFileHook, true).get();
	}

	if (bLogDamage)
	{
		pattern = hook::pattern("E8 DE E5 FE FF 83 C4 0C 83");
		PlayerDamage.fun = injector::MakeCALL(pattern.count(1).get(0).get<uint32_t>(0), PlayerDamageHook, true).get();
	}
}

CEXP void InitializeASI()
{
	std::call_once(CallbackHandler::flag, []()
		{
			CallbackHandler::RegisterCallback(Init, hook::pattern("8B 0D ? ? ? ? 6A 00 50 51"));
		});
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD reason, LPVOID lpReserved)
{
	if (reason == DLL_PROCESS_ATTACH)
	{
		if (!IsUALPresent()) { InitializeASI(); }
	}
	return TRUE;
}