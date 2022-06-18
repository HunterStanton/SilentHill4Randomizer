#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <plog/Log.h>
#include "plog/Initializers/RollingFileInitializer.h"
#include "sh4/en_kind.h"
#include "sh4/game.h"
#include "sh4/game_item.h"
#include "sh4/game_gi_para.h"

injector::hook_back<int(__cdecl*)(int, float)> PlayerDamage;
int __cdecl PlayerDamageHook(int unknown, float damage)
{
	// randomly adds or subtracts values from damage
	PLOG(plog::info) << "Player took damage: " << damage;
	return PlayerDamage.fun(unknown, damage);
}

injector::hook_back<void(__cdecl*)(unsigned int)> sfFileLoad;
void __cdecl sfFileLoadHook(unsigned int fileId)
{
	sfFileLoad.fun(fileId);
	return;

}

injector::hook_back<unsigned int(__cdecl*)(EnemyKind)> EnemyKindTableGetAddress;
unsigned int __cdecl EnemyKindTableGetAddressHook(EnemyKind enemyType)
{

	// shuffle all basic enemy types, no ghosts, no wall monster replacements, no boss replacements, no ghost replacements
	if (enemyType == ENEMY_KIND_HYENA || enemyType == ENEMY_KIND_MUSH || enemyType == ENEMY_KIND_WHEEL || enemyType == ENEMY_KIND_JINMEN || enemyType == ENEMY_KIND_TWINS || enemyType == ENEMY_KIND_HIL || enemyType == ENEMY_KIND_NURSE)
	{
		// just rewriting the function entirely fixes the crash issues
		// bit of an ugly hack though
		EnemyFileMapping enemy = possibleEnemies[std::rand() / ((RAND_MAX + 1u) / possibleEnemies.size())];
		for (int i = 0; i < enemy.fileIds.size(); i++)
		{
			sfFileLoad.fun(enemy.fileIds[i]);
		}
		PLOG(plog::info) << "Spawning enemy type: " << enemy.kind;
		return enemy.tableAddr;
	}

	PLOG(plog::info) << "Spawning enemy type: " << enemyType;
	return EnemyKindTableGetAddress.fun(enemyType);
}

injector::hook_back<bool(__cdecl*)(GameItem)> GameGetItem;
bool __cdecl GameGetItemHook(GameItem item)
{
	// don't change the torch pickup since bad RNG could make it impossible to progress otherwise
	if (item == ITEM_CLUB)
	{
		return GameGetItem.fun(item);
	}

	int newWeapon = 0;

	// original item is a weapon
	if (ITEM_FIRST_AID_KIT < item && item < ITEM_KEY_OF_LIBERATION)
	{
		newWeapon = ITEM_HANDGUN + (std::rand() % (ITEM_CHAIN_SAW - ITEM_HANDGUN + 1));
		PLOG(plog::info) << "Adding weapon " << newWeapon << " to inventory, original weapon was " << item;
		return GameGetItem.fun(static_cast <GameItem>(newWeapon));
	}

	// original item is a consumable of some kind
	if (ITEM_EMPTY < item && item < ITEM_HANDGUN)
	{
		newWeapon = ITEM_SMALL_BULLET + (std::rand() % (ITEM_FIRST_AID_KIT - ITEM_SMALL_BULLET + 1));

		// prevent giving the player unused/cut items
		if (newWeapon == ITEM_RED_CHRISM) newWeapon = ITEM_FINISHER;
		if (newWeapon == ITEM_LOADS_PRAYER) newWeapon = ITEM_SAINT_MEDALLION;

		PLOG(plog::info) << "Adding consumable item " << newWeapon << " to inventory, original consumable item was " << item;
		return GameGetItem.fun(static_cast <GameItem>(newWeapon));
	}


	return GameGetItem.fun(item);
}

injector::hook_back<void(__cdecl*)(int, int)> GameFileLoadScene;
void __cdecl GameFileLoadSceneHook(int scene, int stage)
{
	PLOG(plog::info) << "Loaded scene " << scene << " on stage " << stage;

	GameFileLoadScene.fun(scene, stage);
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

		// this needs to be done or it will always give you the last item in the player model vector, every time
		for (int i = 0; i < 10; i++)
		{
			model = playerModels[std::rand() / ((RAND_MAX + 1u) / playerModels.size())];
		}

		PLOG(plog::info) << "Setting a random playermodel " << model;

		return LoadFile.fun(model, handle);
	}


	if (strcmp(file, ".\\data\\snap_title.bin") == 0)
	{
		return LoadFile.fun(".\\data\\snap_title_randomizer.bin", handle);
	}

	return LoadFile.fun(file, handle);
}


void Init()
{

	// 00430ac8
	// 00430093

	// seed random
	std::srand(std::time(nullptr));

	plog::init(plog::info, "randomizer.log");
	PLOG(plog::info) << "Silent Hill 4 Randomizer Loaded";


	CIniReader iniReader("randomizer.ini");

	bool bRandomEnemies = iniReader.ReadInteger("RANDOMIZER", "RandomEnemies", 1) != 0;
	bool bRandomPlayerModels = iniReader.ReadInteger("RANDOMIZER", "RandomPlayerModel", 1) != 0;
	bool bRandomItems = iniReader.ReadInteger("RANDOMIZER", "RandomItems", 1) != 0;

	bool bEnableHauntings = iniReader.ReadInteger("GAME", "RestoreHauntings", 1) != 0;

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

	if (bEnableHauntings)
	{
		// removes bit shifting and weird math operations that make certain "rolls" impossible in the haunting RNG
		// probably should replace this with a pattern search instead of fixed addresses
		injector::WriteMemory<char>(0x547e4a, 0x90, true);
		injector::WriteMemory<char>(0x547e4b, 0x90, true);
		injector::WriteMemory<char>(0x547e4c, 0x90, true);
		injector::WriteMemory<char>(0x547e4d, 0x90, true);
		injector::WriteMemory<char>(0x547e4e, 0x90, true);
		injector::WriteMemory<char>(0x547e4f, 0x90, true);
		injector::WriteMemory<char>(0x547e50, 0x90, true);
		injector::WriteMemory<char>(0x547e51, 0x90, true);
		injector::WriteMemory<char>(0x547e52, 0x90, true);
		injector::WriteMemory<char>(0x547e53, 0x90, true);
		injector::WriteMemory<char>(0x547e54, 0x90, true);
		injector::WriteMemory<char>(0x547e55, 0x90, true);
	}
	if (bRandomItems)
	{
		pattern = hook::pattern("E8 CC EB FD FF 83 C4 08 85 C0");
		GameGetItem.fun = injector::MakeCALL(pattern.count(1).get(0).get<uint32_t>(0), GameGetItemHook, true).get();
	}

	if (bLogDamage)
	{
		pattern = hook::pattern("E8 DE E5 FE FF 83 C4 0C 83");
		PlayerDamage.fun = injector::MakeCALL(pattern.count(1).get(0).get<uint32_t>(0), PlayerDamageHook, true).get();
	}

	// raises texture size limit to 2048 x 2048 in sgTextureConstruct
	// injector::WriteMemory<char>(0x0042b358, 0x08, true);
	// injector::WriteMemory<char>(0x0042b3e4, 0x08, true);
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