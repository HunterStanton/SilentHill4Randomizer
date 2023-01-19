#pragma once

#include "sh4/game/misc/misc_option.h"


struct PlayerModel {
	LPCSTR filename;
	LPCSTR cutsceneFileName;
};

extern std::vector<PlayerModel> playerModels;

extern injector::hook_back<void(__cdecl*)(LPCSTR, HANDLE*)> LoadFile;
void __cdecl LoadFileHook(LPCSTR file, HANDLE* handle);