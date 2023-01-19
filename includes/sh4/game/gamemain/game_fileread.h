#pragma once

enum GameStage : int {
	GAME_STAGE_DUMMY,
	GAME_STAGE_3LDK,
	GAME_STAGE_SUBWAY,
	GAME_STAGE_FOREST,
	GAME_STAGE_WATER,
	GAME_STAGE_BUILDING,
	GAME_STAGE_HOME,
	GAME_STAGE_HOSPITAL,
	GAME_STAGE_PAST_HOME,
	GAME_STAGE_LAST,
	GAME_STAGE_TUNNEL,
	GAME_STAGE_SPIRAL,
	GAME_STAGE_TEST,
	GAME_STAGE_MAX
};

extern std::vector<std::string> stageNames;
extern injector::hook_back<void(__cdecl*)(GameStage, int)> GameFileLoadScene;
extern injector::hook_back<void(__cdecl*)(GameStage)> GameFileLoadStage;
void __cdecl GameFileLoadSceneHook(GameStage stage, int scene);
void __cdecl GameFileLoadStageHook(GameStage stage);

void InitializeGameFileReadFunctions();