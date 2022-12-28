#pragma once
#include "sh4/game/gamemain/game_item.h"

struct ItemIcon
{
	GameItem kind;
	char no;
	char image_no;
	char clut_no;
	char offset_no;
};

extern std::vector<ItemIcon> small_icon_tbl;
extern std::vector<ItemIcon> large_icon_tbl;
