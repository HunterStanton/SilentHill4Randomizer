#include "stdafx.h"
#include "sh4/game/gamemain/game_scenelink.h"
#include <plog/Log.h>

DoorLinkTableEntry* rl_connection_data;
DoorLinkTableEntry* sb_connection_data;

// bathroom, bedroom, utility room
// walter room is not included
std::vector<char> rl_possible_destinations = {
	2,3,4
};


void InitializeGameSceneLinkFunctions()
{
	rl_connection_data = injector::auto_pointer(0x0063b190);
	sb_connection_data = injector::auto_pointer(0x0063b3b0);
}