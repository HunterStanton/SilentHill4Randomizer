#include "stdafx.h"
#include "sh4/game/gamemain/game_gi_para.h"
#include <plog/Log.h>

injector::hook_back<unsigned int(__cdecl*)(GameItem)> GameGetItemParamTexId;
unsigned int GameGetItemParamTexIdHook(GameItem item)
{
	return GameGetItemParamTexId.fun(ITEM_SILVER_BULLET);
}

injector::hook_back<unsigned int(__cdecl*)(GameItem)> GameGetItemParamModelId;
unsigned int GameGetItemParamModelIdHook(GameItem item)
{
	return GameGetItemParamModelId.fun(ITEM_SILVER_BULLET);
}

injector::hook_back<_ItemMsgCtrlDt* (__cdecl*)(GameItem)> GameGetItemMsgCtrlDt;
_ItemMsgCtrlDt* GameGetItemMsgCtrlDtHook(GameItem item)
{
	return GameGetItemMsgCtrlDt.fun(ITEM_SILVER_BULLET);
}