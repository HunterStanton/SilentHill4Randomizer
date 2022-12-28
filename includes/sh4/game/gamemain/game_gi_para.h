#pragma once

#include "sh4/game/gamemain/game_item.h"

struct _ItemMsgCtrlDt
{
	int* cmd;
	short id;
};

extern injector::hook_back<unsigned int(__cdecl*)(GameItem)> GameGetItemParamTexId;
unsigned int GameGetItemParamTexIdHook(GameItem item);

extern injector::hook_back<unsigned int(__cdecl*)(GameItem)> GameGetItemParamModelId;
unsigned int GameGetItemParamModelIdHook(GameItem item);

extern injector::hook_back<_ItemMsgCtrlDt* (__cdecl*)(GameItem)> GameGetItemMsgCtrlDt;
_ItemMsgCtrlDt* GameGetItemMsgCtrlDtHook(GameItem item);