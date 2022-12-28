#pragma once
#include "sh4/game/gamemain/game_item.h"

struct ItemMessage
{
	int item;
	short name;
	short info;
};

extern std::vector<ItemMessage> item_message_table;