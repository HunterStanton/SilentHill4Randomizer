#pragma once
#include "sh4/game/gamemain/game_item.h"

struct DemoCharaListEntry
{
	unsigned int chara_id;
	unsigned int model_id;
	unsigned int tex_id;
	unsigned int svm_id;
};

extern injector::hook_back<DemoCharaListEntry* (__cdecl*)(DemoCharaListEntry*, int)> DemoGetCharacterFileInfo;
DemoCharaListEntry* __cdecl DemoGetCharacterFileInfoHook(DemoCharaListEntry* entry, int chara_id);

void InitializeGameDemoFunctions();