#include "stdafx.h"
#include "FileHooks.h"
#include "Randomizer.h"
#include <plog/Log.h>

std::vector<PlayerModel> playerModels = {
	// vanilla
	{".\\data\\henry01.bin", ".\\data\\henhk.bin"},

	// early/prototype Henry + Eileen
	{".\\data\\randomizer_early_henry.bin", ".\\data\\randomizer_early_henry_cutscene.bin"},
	//{".\\data\\randomizer_early_eileen.bin", ".\\data\\randomizer_early_eileen_cutscene.bin"}, // disable for now until I can figure out how to reposition the bone the weapon attaches to

	// Eileen + Eileen nurse
	{".\\data\\randomizer_eileen.bin", ".\\data\\eihk.bin"},
	{".\\data\\randomizer_eileen_sexy.bin", ".\\data\\eohk.bin"},

	// {".\\data\\randomizer_jasper.bin", ".\\data\\geik.bin"} // same deal as with early Eileen
};

// replacement files that don't need special handling logic
std::unordered_map<std::string, LPCSTR> replacementFiles = {
	{".\\data\\snap_title.bin", ".\\data\\randomizer_snap_title.bin"},
	{".\\data\\item_l.bin", ".\\data\\randomizer_item_l.bin"},
	{".\\data\\wp_model.bin", ".\\data\\randomizer_wp_model.bin"},
	{".\\data\\system_load.bin", ".\\data\\randomizer_system_load.bin"},
};

PlayerModel currentPlayerModel = playerModels[0];

// didn't want to dig super deep in the game code so this is the basic file reading function
injector::hook_back<void(__cdecl*)(LPCSTR, HANDLE*)> LoadFile;
void __cdecl LoadFileHook(LPCSTR file, HANDLE* handle)
{
	// player model + cutscene model replacements
	if (strcmp(file, ".\\data\\henry01.bin") == 0)
	{
		if (settings.bInGameOptions)
		{
			if (miscOptionGetPtr.fun()->random_models == 0)
			{
				PLOG(plog::info) << "Loading file " << file;
				return LoadFile.fun(file, handle);
			}
		}
		else if (settings.bRandomPlayerModels == false)
		{
			PLOG(plog::info) << "Loading file " << file;
			return LoadFile.fun(file, handle);
		}


		PLOG(plog::info) << "Loading file " << currentPlayerModel.filename;
		return LoadFile.fun(currentPlayerModel.filename, handle);
	}

	if (strcmp(file, ".\\data\\henhk.bin") == 0)
	{
		if (settings.bInGameOptions)
		{
			if (miscOptionGetPtr.fun()->random_models == 0)
			{
				PLOG(plog::info) << "Loading file " << file;
				return LoadFile.fun(file, handle);
			}
		}
		else if (settings.bRandomPlayerModels == false)
		{
			PLOG(plog::info) << "Loading file " << file;
			return LoadFile.fun(file, handle);
		}


		PLOG(plog::info) << "Loading file " << currentPlayerModel.cutsceneFileName;
		return LoadFile.fun(currentPlayerModel.cutsceneFileName, handle);
	}

	// file replacements for randomizer (weapon models, item icons, etc.)
	if (replacementFiles.contains(file))
	{
		PLOG(plog::info) << "Loading replacement file " << replacementFiles[file] << " over original file " << file;
		return LoadFile.fun(replacementFiles[file], handle);
	}

	PLOG(plog::info) << "Loading file " << file;
	return LoadFile.fun(file, handle);
}