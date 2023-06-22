#include "stdafx.h"
#include "Randomizer.h"
#include "sh4/game/enemy/en_kind.h"
#include "sh4/game/gamemain/game_item.h"
#include "sh4/game/gamemain/game_scenelink.h"
#include "sh4/game/gamemain/save_data.h"
#include <plog/Log.h>
#include "plog/Initializers/RollingFileInitializer.h"

std::mt19937 mainRng = std::mt19937(std::time(0));
std::uniform_int_distribution<int> enemyGenerator(0, possibleEnemies.size() - 1);
std::uniform_int_distribution<int> consumableGenerator(ITEM_SMALL_BULLET, ITEM_FIRST_AID_KIT);
std::uniform_int_distribution<int> playerModelGenerator(0, playerModels.size() - 1);


void InitializeRandomness()
{
	// if global seed is not set, it will be -1
	// global seed -1 == "random" global seed
	if (settings.iGlobalSeed == -1)
	{
		settings.iGlobalSeed = std::time(0);
	}

	// shuffle both weapon pools
	std::shuffle(possibleWeapons.begin(), possibleWeapons.end(), mainRng);
	std::shuffle(possibleWeaponsWithExtra.begin(), possibleWeaponsWithExtra.end(), mainRng);

	// replace weapon spawns with unique weapons, avoiding duplicates
	for (auto& item : weaponSwaps) {
		item.second = possibleWeapons.front();
		possibleWeapons.erase(possibleWeapons.begin());
	}
	for (auto& item : weaponSwapsWithExtra) {
		item.second = possibleWeaponsWithExtra.front();
		possibleWeaponsWithExtra.erase(possibleWeaponsWithExtra.begin());
	}
	/*
	// shuffle apartment rooms
	std::shuffle(rl_possible_destinations.begin(), rl_possible_destinations.end(), mainRng);
	for (int i = 0; i < rl_possible_destinations.size(); i++)
	{
		// set up all the link destinations
		rl_connection_data->doorlinks_data_offset[i].end_scene = rl_possible_destinations[i];

		// find the scene data for the scene that that the door is normally in
		// and update the door number so the inside door functions properly
		for (int j = 0; j < rl_connection_data->n_scenes; j++)
		{
			if (rl_connection_data->scene_data_offsets[j]->n_doors == 1)
			{
				if (rl_connection_data->scene_data_offsets[j]->doors[0].scene_no == rl_possible_destinations[i])
				{
					rl_connection_data->scene_data_offsets[j]->doors[0].door_no = i + 1;
				}
			}
		}
	}
	*/

	// roll random player model

	currentPlayerModel = playerModels[playerModelGenerator(mainRng)];

	PLOG(plog::info) << "Setting a random playermodel " << currentPlayerModel.filename;

	HANDLE hFile = CreateFile(L"..\\save\\sh4_randomizer_per_save_settings.sav", GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile != INVALID_HANDLE_VALUE)
	{
		DWORD dwBytesRead;
		ReadFile(hFile, &perSaveSettings, sizeof(perSaveSettings), &dwBytesRead, NULL);
		CloseHandle(hFile);
	}
	else
	{
		PLOG(plog::warning) << "Failed to open sh4_randomizer_per_save_settings.sav for reading. Global randomizer settings and seed will always be used.";
	}

}
void ReseedRNG(unsigned int seed)
{
	mainRng.seed(seed + settings.iGlobalSeed);
}