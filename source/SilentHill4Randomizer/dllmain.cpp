#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <plog/Log.h>
#include "plog/Initializers/RollingFileInitializer.h"

using namespace std;

injector::hook_back<int(__cdecl*)(int, float)> PlayerDamage;
int __cdecl PlayerDamageHook(int unknown, float damage)
{
	PLOG(plog::info) << "Player took damage: " << damage;
	return PlayerDamage.fun(unknown, damage);
}

int possibleEnemies[9] = { 2, 3, 5, 7, 8, 9, 0xA, 0x10, 0x11 };
injector::hook_back<int* (__cdecl*)(unsigned int)> EnemyKindTableGetAddress;
int* __cdecl EnemyKindTableGetAddressHook(unsigned int enemyId)
{
	PLOG(plog::info) << "Spawning enemy type: " << enemyId;

	// shuffle all basic enemy types, no ghosts, no wall monster replacements, no boss replacements
	if (enemyId == 10 || enemyId == 2 || enemyId == 3 || enemyId == 4 || enemyId == 6 || enemyId == 7 || enemyId == 8 || enemyId == 9)
	{
		// replace dogs with anything
		enemyId = possibleEnemies[rand() % 9];
	}

	return EnemyKindTableGetAddress.fun(enemyId);
}

injector::hook_back<void(__cdecl*)(int)> sfFileLoad;
void __cdecl sfFileLoadHook(int fileId)
{
	return sfFileLoad.fun(fileId);
}

injector::hook_back<void(__cdecl*)(int, int)> GameFileLoadScene;
void __cdecl GameFileLoadSceneHook(int scene, int stage)
{
	PLOG(plog::info) << "Loaded scene " << scene << " on stage " << stage;

	// load all enemy .bin files upon the loading of every scene so they can be spawned
	// this is not really a memory or performance concern the game is almost 20 years old and the amount of memory needed to load it all at once is less than 40mb
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

LPCSTR playerModels[3] = { ".\\data\\henry01.bin", ".\\data\\randomizer_eileen.bin", ".\\data\\randomizer_eileen_sexy.bin" };

injector::hook_back<void(__cdecl*)(LPCSTR, HANDLE*)> LoadFile;
void __cdecl LoadFileHook(LPCSTR file, HANDLE* handle)
{
	PLOG(plog::info) << "Loading file " << file;

	if (strcmp(file, ".\\data\\henry01.bin") == 0)
	{
		PLOG(plog::info) << "Setting a random playermodel";
		return LoadFile.fun(playerModels[rand() % 3], handle);
	}

	return LoadFile.fun(file, handle);
}

void Init()
{
	plog::init(plog::info, "info.log");
	PLOG(plog::info) << "Silent Hill 4 Randomizer Loaded";

	CIniReader iniReader("randomizer.ini");
	bool bLogDamage = iniReader.ReadInteger("MAIN", "LogDamageValues", 1) != 0;

	auto pattern = hook::pattern("E8 A3 34 00 00");
	GameFileLoadScene.fun = injector::MakeCALL(pattern.count(1).get(0).get<uint32_t>(0), GameFileLoadSceneHook, true).get();

	pattern = hook::pattern("E8 E5 FE 07 00");
	sfFileLoad.fun = injector::MakeCALL(pattern.count(1).get(0).get<uint32_t>(0), sfFileLoadHook, true).get();

	pattern = hook::pattern("E8 17 3A F4 FF");
	EnemyKindTableGetAddress.fun = injector::MakeCALL(pattern.count(1).get(0).get<uint32_t>(0), EnemyKindTableGetAddressHook, true).get();

	pattern = hook::pattern("E8 0D FE FF FF");
	LoadFile.fun = injector::MakeCALL(pattern.count(2).get(1).get<uint32_t>(0), LoadFileHook, true).get();
	pattern = hook::pattern("E8 42 FE FF FF");
	LoadFile.fun = injector::MakeCALL(pattern.count(3).get(1).get<uint32_t>(0), LoadFileHook, true).get();

	if (bLogDamage)
	{
		// PlayerDamage Hook
		pattern = hook::pattern("E8 DE E5 FE FF 83 C4 0C 83"); //0x00450A07
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