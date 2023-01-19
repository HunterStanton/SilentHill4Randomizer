#include "stdafx.h"
#include "Randomizer.h"
#include "sh4/game/gamemain/game_fileread.h"
#include "sh4/game/enemy/en_kind.h"
#include "sh4/sys/storage/sf_fileread.h"
#include <plog/Log.h>
#include <stdio.h>


std::vector<std::string> stageNames =
{
	"GAME_STAGE_DUMMY",
	"GAME_STAGE_3LDK",
	"GAME_STAGE_SUBWAY",
	"GAME_STAGE_FOREST",
	"GAME_STAGE_WATER",
	"GAME_STAGE_BUILDING",
	"GAME_STAGE_HOME",
	"GAME_STAGE_HOSPITAL",
	"GAME_STAGE_PAST_HOME",
	"GAME_STAGE_LAST",
	"GAME_STAGE_TUNNEL",
	"GAME_STAGE_SPIRAL",
	"GAME_STAGE_TEST",
	"GAME_STAGE_MAX"

};

// hook for logging room loading for debugging purposes
injector::hook_back<void(__cdecl*)(GameStage, int)> GameFileLoadScene;
void __cdecl GameFileLoadSceneHook(GameStage stage, int scene)
{

	// reseed RNG based on scene + stage number
	ReseedRNG(stage + scene);

	PLOG(plog::info) << "Loading scene " << scene << " on stage " << stageNames[stage];

	// load enemy .bin files so they will spawn
	// do not load anything extra on 3LDK, TUNNEL, or LAST
	if (stage != GAME_STAGE_3LDK && stage != GAME_STAGE_TUNNEL && stage != GAME_STAGE_LAST)
	{
		for (int i = 0; i < possibleEnemies.size(); i++)
		{
			for (int j = 0; j < possibleEnemies[i].fileIds.size(); j++)
			{
				sfFileLoad.fun(possibleEnemies[i].fileIds[j]);
			}
		}
	}

	GameFileLoadScene.fun(stage, scene);
	return;
}

// hook for logging room loading for debugging purposes
injector::hook_back<void(__cdecl*)(GameStage)> GameFileLoadStage;
void __cdecl GameFileLoadStageHook(GameStage stage)
{

	PLOG(plog::info) << "Loading global files for stage " << stageNames[stage];

	// ensure that large item icons are globally loaded
	sfFileLoad.fun(0xf000f008);

	GameFileLoadStage.fun(stage);
	return;
}

void InitializeGameFileReadFunctions()
{
	GameFileLoadScene.fun = injector::MakeCALL(0x004f0068, GameFileLoadSceneHook, true).get();
	GameFileLoadScene.fun = injector::MakeCALL(0x004efe18, GameFileLoadSceneHook, true).get();
	GameFileLoadStage.fun = injector::MakeCALL(0x004fa5d0, GameFileLoadStageHook, true).get();
}