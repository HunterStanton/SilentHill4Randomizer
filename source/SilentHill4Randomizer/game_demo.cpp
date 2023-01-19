#include "stdafx.h"
#include "Randomizer.h"
#include "sh4/game/gamemain/game_demo.h"
#include "sh4/sys/storage/sf_fileread.h"

injector::hook_back<DemoCharaListEntry* (__cdecl*)(DemoCharaListEntry*, int)> DemoGetCharacterFileInfo;

DemoCharaListEntry* demo_chara_list;

DemoCharaListEntry* __cdecl DemoGetCharacterFileInfoHook(DemoCharaListEntry* entry, int chara_id)
{
	DemoCharaListEntry* retEntry = DemoGetCharacterFileInfo.fun(entry, chara_id);
	return retEntry;
}
void InitializeGameDemoFunctions()
{
	demo_chara_list = injector::auto_pointer(0x0062ced8);
	DemoGetCharacterFileInfo.fun = injector::MakeCALL(0x004f1f63, DemoGetCharacterFileInfoHook, true).get();
}
