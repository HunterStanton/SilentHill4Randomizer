#include "stdafx.h"
#include "FileHooks.h"
#include "Randomizer.h"
#include <plog/Log.h>

std::vector<LPCSTR> playerModels = { ".\\data\\henry01.bin", ".\\data\\randomizer_eileen.bin", ".\\data\\randomizer_eileen_sexy.bin" };

// didn't want to dig super deep in the game code so this is the basic file reading function
injector::hook_back<void(__cdecl*)(LPCSTR, HANDLE*)> LoadFile;
void __cdecl LoadFileHook(LPCSTR file, HANDLE* handle)
{
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

		LPCSTR model = playerModels[std::rand() / ((RAND_MAX + 1u) / playerModels.size())];

		// this needs to be done or it will always give you the last item in the player model vector, every time
		for (int i = 0; i < 10; i++)
		{
			model = playerModels[std::rand() / ((RAND_MAX + 1u) / playerModels.size())];
		}

		PLOG(plog::info) << "Setting a random playermodel " << model;

		PLOG(plog::info) << "Loading file " << model;
		return LoadFile.fun(model, handle);
	}

	if (strcmp(file, ".\\data\\snap_title.bin") == 0)
	{
		PLOG(plog::info) << "Loading file " << ".\\data\\snap_title_randomizer.bin";
		return LoadFile.fun(".\\data\\snap_title_randomizer.bin", handle);
	}

	if (strcmp(file, ".\\data\\wp_model.bin") == 0)
	{
		PLOG(plog::info) << "Loading file " << ".\\data\\randomizer_wp_model.bin";
		return LoadFile.fun(".\\data\\randomizer_wp_model.bin", handle);
	}

	return LoadFile.fun(file, handle);
}