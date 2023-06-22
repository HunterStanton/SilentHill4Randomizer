#include "stdafx.h"
#include "Randomizer.h"
#include "sh4/game/gamemain/save_data.h"
#include "sh4/game/message/message_load.h"
#include "sh4/game/message/message_handle.h"
#include "sh4/sys/apps/sf_step.h"
#include <plog/Log.h>

injector::hook_back<int(__cdecl*)(int, int, int)> sfMcLoad;
injector::hook_back<int(__cdecl*)(int, int, int)> sfMcSaveCreate;
injector::hook_back<int(__cdecl*)(int, int, int)> print_load_stat_s;

ExtraSaveSettings perSaveSettings[32];

const char* seedMsg = convertMessage("Randomizer seed: 0");

int __cdecl sfMcLoadHook(int port, int fn, int file_no)
{
	PLOG(plog::info) << "Loading save file " << file_no << " on port " << port;

	if (perSaveSettings[file_no].seed != 0)
	{
		PLOG(plog::info) << "File has randomizer seed " << perSaveSettings[file_no].seed;
		settings.iGlobalSeed = perSaveSettings[file_no].seed;
	}

	return sfMcLoad.fun(port, fn, file_no);
};

int __cdecl sfMcSaveCreateHook(int port, int fn, int file_no)
{

	perSaveSettings[file_no].seed = settings.iGlobalSeed;

	std::ofstream outfile;
	outfile.open(".\\save\\sh4_randomizer_per_save_settings.sav", std::ios::binary);
	outfile.write((char*)&perSaveSettings, sizeof(perSaveSettings));
	outfile.close();

	PLOG(plog::info) << "Saving save file " << file_no << " on port " << port;
	return sfMcSaveCreate.fun(port, fn, file_no);
}

void print_load_stat_sHook(int port, int cur, int disp)
{
	print_load_stat_s.fun(port, cur, disp);
	if (disp != 0)
	{
		if (perSaveSettings[cur].seed != 0)
		{
			if (sfStepGet.fun() < 0x65)
			{
				std::string formattedString = std::format("Seed: {0}", perSaveSettings[cur].seed);
				seedMsg = convertMessage(formattedString.c_str());
				sfMessagePrint.fun((unsigned short*)seedMsg, 0x12a, 0x152);
				PLOG(plog::info) << "Printing print " << cur << " " << disp;
			}

		}
	}
	return;
}

void InitializeSaveDataFunctions()
{
	sfMcLoad.fun = injector::MakeCALL(0x00571d7e, sfMcLoadHook, true).get();
	sfMcLoad.fun = injector::MakeCALL(0x00571dab, sfMcLoadHook, true).get();

	sfMcSaveCreate.fun = injector::MakeCALL(0x00571651, sfMcSaveCreateHook, true).get();
	sfMcSaveCreate.fun = injector::MakeCALL(0x00571690, sfMcSaveCreateHook, true).get();


	print_load_stat_s.fun = injector::MakeCALL(0x005708fc, print_load_stat_sHook, true).get();
	print_load_stat_s.fun = injector::MakeCALL(0x0057295a, print_load_stat_sHook, true).get();



};
