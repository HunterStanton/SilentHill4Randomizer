#include "stdafx.h"
#include "sh4/game/gamemain/game_fileread.h"
#include <plog/Log.h>

static std::vector<std::string> stageNames =
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
injector::hook_back<void(__cdecl*)(int, int)> GameFileLoadScene;
void __cdecl GameFileLoadSceneHook(int stage, int scene)
{
	PLOG(plog::info) << "Loaded scene " << scene << " on stage " << stageNames[stage];

	GameFileLoadScene.fun(stage, scene);
	return;
}