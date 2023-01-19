#include "stdafx.h"
#include "sh4/game/player/player_another_ui.h"
#include "sh4/game/gamemain/game.h"
#include "Randomizer.h"
#include <plog/Log.h>

PlayerUI* playerUI;
int* motion_stop;

void InitializePlayerAnotherUIFunctions()
{
	playerUI = injector::auto_pointer(0x010a1a00);
	motion_stop = injector::auto_pointer(0x010a1914);
}