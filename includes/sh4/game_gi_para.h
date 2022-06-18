#pragma once

#include "game_item.h"

extern injector::hook_back<unsigned int(__cdecl*)(GameItem)> GameGetItemParamTexId;
unsigned int GameGetItemParamTexIdHook(GameItem item);

extern injector::hook_back<unsigned int(__cdecl*)(GameItem)> GameGetItemParamModelId;
unsigned int GameGetItemParamModelIdHook(GameItem item);