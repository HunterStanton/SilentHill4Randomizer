#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <plog/Log.h>
#include "plog/Initializers/RollingFileInitializer.h"
#include "Randomizer.h"
#include "FileHooks.h"
#include "sh4/game/enemy/en_kind.h"
#include "sh4/game/gamemain/game_fileread.h"
#include "sh4/game/gamemain/game_item.h"
#include "sh4/game/gamemain/game_gi_para.h"
#include "sh4/game/misc/misc_option.h"
#include "sh4/game/misc/misc_itemicon.h"
#include "sh4/game/misc/misc_iexplanation.h"
#include "sh4/game/message/message_load.h"
#include "sh4/game/message/message_handle.h"
#include "sh4/game/objs/game_objset.h"
#include "sh4/game/player/player.h"
#include "sh4/game/player/player_anime_proc.h"
#include "sh4/game/player/battle/player_weapon.h"
#include "sh4/sys/storage/sf_fileread.h"
#include "sh4/sys/geometry/sf_scene.h"

RandomizerSettings settings = { 0 };

int chosenColor = 0;
std::vector<int> colors = {
	((64 << 8 | 100) << 8 | 15) << 8 | 15, // blue
	((64 << 8 | 100) << 8 | 100) << 8 | 15, // cyan
	((64 << 8 | 100) << 8 | 15) << 8 | 100, // pink
	((64 << 8 | 15) << 8 | 120) << 8 | 120, // yellow
	((64 << 8 | 100) << 8 | 100) << 8 | 100, // white
	((64 << 8 | 0) << 8 | 0) << 8 | 0, // white
};

injector::hook_back<void(__cdecl*)(int, int, int, int, int, unsigned int)> MakeBloodDrop;
void __cdecl MakeBloodDropHook(int unk, int unk2, int unk3, int unk4, int unk5, unsigned int color)
{
	return MakeBloodDrop.fun(unk, unk2, unk3, unk4, unk5, colors[5]); //colors[std::rand() / ((RAND_MAX + 1u) / playerModels.size())]);
}

void Init()
{

	// 00430ac8
	// 00430093

	// seed random
	std::srand(std::time(0));

	plog::init(plog::info, "randomizer.log");
	PLOG(plog::info) << "Silent Hill 4 Randomizer initializing...";

	CIniReader iniReader("randomizer.ini");

	unsigned int seed = iniReader.ReadInteger("RANDOMIZER", "Seed", std::time(0));

	settings.bInGameOptions = iniReader.ReadInteger("GAME", "EnableInGameOptions", 0) != 0;

	settings.bEnableHauntings = iniReader.ReadInteger("GAME", "RestoreHauntings", 1) != 0;

	settings.bFastSplash = iniReader.ReadInteger("VIDEO", "FastSplash", 1) != 0;

	auto pattern = hook::pattern("E8 A3 34 00 00");

	LoadSceneSets();

	if (settings.bInGameOptions)
	{
		ApplyIngameOptionsPatches();
	}
	else
	{
		settings.bRandomEnemies = iniReader.ReadInteger("RANDOMIZER", "RandomEnemies", 1) != 0;
		settings.bRandomPlayerModels = iniReader.ReadInteger("RANDOMIZER", "RandomPlayerModel", 1) != 0;
		settings.bRandomItems = iniReader.ReadInteger("RANDOMIZER", "RandomItems", 1) != 0;
	}

	InstallItemHooks();

	GameFileLoadScene.fun = injector::MakeCALL(pattern.count(1).get(0).get<uint32_t>(0), GameFileLoadSceneHook, true).get();

	pattern = hook::pattern("E8 E5 FE 07 00");
	sfFileLoad.fun = injector::MakeCALL(pattern.count(1).get(0).get<uint32_t>(0), sfFileLoadHook, true).get();

	pattern = hook::pattern("E8 17 3A F4 FF");
	EnemyKindTableGetAddress.fun = injector::MakeCALL(pattern.count(1).get(0).get<uint32_t>(0), EnemyKindTableGetAddressHook, true).get();

	pattern = hook::pattern("E8 0D FE FF FF");
	LoadFile.fun = injector::MakeCALL(pattern.count(2).get(1).get<uint32_t>(0), LoadFileHook, true).get();
	pattern = hook::pattern("E8 42 FE FF FF");
	LoadFile.fun = injector::MakeCALL(pattern.count(3).get(1).get<uint32_t>(0), LoadFileHook, true).get();

	if (settings.bFastSplash)
	{
		// removes an fdivr instruction to shorten splash screens but not make them too short
		injector::WriteMemory<unsigned char>(0x00518eb4, 0x90, true);
		injector::WriteMemory<unsigned char>(0x00518eb5, 0x90, true);
		injector::WriteMemory<unsigned char>(0x00518eb6, 0x90, true);
		injector::WriteMemory<unsigned char>(0x00518eb7, 0x90, true);
		injector::WriteMemory<unsigned char>(0x00518eb8, 0x90, true);
		injector::WriteMemory<unsigned char>(0x00518eb9, 0x90, true);
	}

	/*
	injector::WriteMemory<unsigned char>(0x00525bc6, 0x31, true);
	injector::WriteMemory<unsigned char>(0x00525bc7, 0xc0, true);
	injector::WriteMemory<unsigned char>(0x00525bc8, 0x40, true);
	injector::WriteMemory<unsigned char>(0x00525bc9, 0x40, true);
	
	injector::WriteMemory<unsigned char>(0x00525c0a, 0x31, true);
	injector::WriteMemory<unsigned char>(0x00525c0b, 0xc0, true);
	injector::WriteMemory<unsigned char>(0x00525c0c, 0x40, true);
	injector::WriteMemory<unsigned char>(0x00525c0d, 0x40, true);

	injector::WriteMemory<unsigned char>(0x00525b88, 0x03, true);

	injector::WriteMemory<unsigned char>(0x00523e23, 0x10, true);
	*/


	if (settings.bEnableHauntings)
	{
		// removes bit shifting and weird math operations that make certain "rolls" impossible in the haunting RNG
		// probably should replace this with a pattern search instead of fixed addresses
		injector::MakeNOP(0x547e4a, 12);
	}

	pattern = hook::pattern("E8 DE E5 FE FF 83 C4 0C 83");
	PlayerDamage.fun = injector::MakeCALL(pattern.count(1).get(0).get<uint32_t>(0), PlayerDamageHook, true).get();

	MessagePut.fun = injector::auto_pointer(0x0050b580);
	MessageSubtitlesPut.fun = injector::auto_pointer(0x0050c2a0);
	MessageDemoSubtitlesPut.fun = injector::auto_pointer(0x0050b1c0);
	MessageMemoPut.fun = injector::auto_pointer(0x0050c340);
	MessageExplanationPut.fun = injector::auto_pointer(0x0050c300);

	MakeBloodDrop.fun = injector::MakeCALL(0x00430c48, MakeBloodDropHook, true).get();

	sfSceneSetFogColor.fun = injector::MakeCALL(0x004d748c, sfSceneSetFogColorHook, true).get();
	sfSceneSetFogColor.fun = injector::MakeCALL(0x004d83fc, sfSceneSetFogColorHook, true).get();
	sfSceneSetFogColor.fun = injector::MakeCALL(0x004f13de, sfSceneSetFogColorHook, true).get();
	sfSceneSetFogColor.fun = injector::MakeCALL(0x004f1493, sfSceneSetFogColorHook, true).get();
	sfSceneSetFogColor.fun = injector::MakeCALL(0x004f15cf, sfSceneSetFogColorHook, true).get();
	sfSceneSetFogColor.fun = injector::MakeCALL(0x004f1e7a, sfSceneSetFogColorHook, true).get();
	sfSceneSetFogColor.fun = injector::MakeCALL(0x0054c343, sfSceneSetFogColorHook, true).get();
	sfSceneSetFogColor.fun = injector::MakeCALL(0x0054c625, sfSceneSetFogColorHook, true).get();

	sfSceneSetFogPower.fun = injector::MakeCALL(0x004d74be, sfSceneSetFogPowerHook, true).get();
	sfSceneSetFogPower.fun = injector::MakeCALL(0x004d842e, sfSceneSetFogPowerHook, true).get();
	sfSceneSetFogPower.fun = injector::MakeCALL(0x004f13f4, sfSceneSetFogPowerHook, true).get();
	sfSceneSetFogPower.fun = injector::MakeCALL(0x004f14ab, sfSceneSetFogPowerHook, true).get();
	sfSceneSetFogPower.fun = injector::MakeCALL(0x0054c33a, sfSceneSetFogPowerHook, true).get();
	sfSceneSetFogPower.fun = injector::MakeCALL(0x0055e4b7, sfSceneSetFogPowerHook, true).get();
	sfSceneSetFogPower.fun = injector::MakeCALL(0x0055e577, sfSceneSetFogPowerHook, true).get();
	sfSceneSetFogPower.fun = injector::MakeCALL(0x0055e5ac, sfSceneSetFogPowerHook, true).get();
	sfSceneSetFogPower.fun = injector::MakeCALL(0x0055e5e8, sfSceneSetFogPowerHook, true).get();

	

	PLOG(plog::info) << "Silent Hill 4 Randomizer initialized";
}

CEXP void InitializeASI()
{
	std::call_once(CallbackHandler::flag, []()
		{ CallbackHandler::RegisterCallback(Init, hook::pattern("8B 0D ? ? ? ? 6A 00 50 51")); });
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD reason, LPVOID lpReserved)
{
	if (reason == DLL_PROCESS_ATTACH)
	{
		if (!IsUALPresent())
		{
			InitializeASI();
		}
	}
	return TRUE;
}