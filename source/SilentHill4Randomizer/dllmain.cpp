#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <plog/Log.h>
#include "plog/Initializers/RollingFileInitializer.h"
#include "Randomizer.h"
#include "FileHooks.h"
#include "sh4/game/enemy/en_kind.h"
#include "sh4/game/gamemain/game.h"
#include "sh4/game/gamemain/game_demo.h"
#include "sh4/game/gamemain/game_fileread.h"
#include "sh4/game/gamemain/game_item.h"
#include "sh4/game/gamemain/game_gi_para.h"
#include "sh4/game/effect/particle/spray.h"
#include "sh4/game/misc/misc_option.h"
#include "sh4/game/misc/misc_itemicon.h"
#include "sh4/game/misc/misc_iexplanation.h"
#include "sh4/game/message/message_load.h"
#include "sh4/game/gamemain/stage_info.h"
#include "sh4/game/message/message_handle.h"
#include "sh4/sglib/math/sg_quat.h"
#include "sh4/game/objs/game_objset.h"
#include "sh4/game/player/player.h"
#include "sh4/game/player/player_anime_proc.h"
#include "sh4/game/player/player_another_ui.h"
#include "sh4/game/player/battle/player_weapon.h"
#include "sh4/game/player/battle/player_battle.h"
#include "sh4/game/player/battle/player_battle_general.h"
#include "sh4/sys/apps/sf_memorystack.h"
#include "sh4/sys/storage/sf_fileread.h"
#include "sh4/sys/geometry/sf_scene.h"
#include "sh4/sys/env/sf_env.h"

// global vars
RandomizerSettings settings = { 0 };
_GAME_WORK* gameW;
PlayerUI* playerUI;

void Init()
{

	// 00430ac8
	// 00430093

	// seed random
	std::srand(std::time(0));

	plog::init(plog::info, "randomizer.log", 1000000, 1);
	PLOG(plog::info) << "Silent Hill 4 Randomizer initializing...";

	CIniReader iniReader("randomizer.ini");

	settings.bInGameOptions = iniReader.ReadInteger("GAME", "EnableInGameOptions", 0) != 0;

	settings.bEnableHauntings = iniReader.ReadInteger("GAME", "RestoreHauntings", 1) != 0;

	settings.bFastSplash = iniReader.ReadInteger("VIDEO", "FastSplash", 1) != 0;

	settings.iGlobalSeed = iniReader.ReadInteger("RANDOMIZER", "GlobalSeed", -1);

	settings.bFogApproaches = iniReader.ReadInteger("GAME", "FogApproaches", 0) != 0;

	InitializeRandomness();

	gameW = injector::auto_pointer(0x00fd5a60);
	playerUI = injector::auto_pointer(0x010a1a00);

	InitializeSgBoneFunctions();
	InitializeSfCharacterFunctions();
	InitializeSgAnimeFunctions();
	InitializeSprayFunctions();
	InitializePlayerWeaponFunctions();
	InitializeSfEnvFunctions();
	InitializeSgQuatFunctions();
	InitializeStageInfoFunctions();
	InitializePlayerBattleFunctions();
	InitializeGameDemoFunctions();
	InitializeMessageHandleFunctions();
	InitializeGameFileReadFunctions();
	InitializeEnemyKindFunctions();
	InitializePlayerFunctions();
	InitializeSfSceneFunctions();
	InitializeSfFileLoadFunctions();
	InitializeGameGIParaFunctions();
	InitializeSfMemoryFunctions();
	InitializePlayerBattleGeneralFunctions();

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
		settings.bRandomDamage = iniReader.ReadInteger("RANDOMIZER", "RandomDamage", 1) != 0;
	}

	InstallItemHooks();


	auto pattern = hook::pattern("E8 0D FE FF FF");
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


	if (settings.bEnableHauntings)
	{
		// removes bit shifting and weird math operations that make certain "rolls" impossible in the haunting RNG
		// probably should replace this with a pattern search instead of fixed addresses
		injector::MakeNOP(0x547e4a, 12);
	}

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