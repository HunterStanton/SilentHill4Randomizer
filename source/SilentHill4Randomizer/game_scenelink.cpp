#include "stdafx.h"
#include "sh4/game/gamemain/game_scenelink.h"
#include <plog/Log.h>

DoorLinkTableEntry* rl_connection_data;
DoorLinkTableEntry* sb_connection_data;

std::vector<RLPossibleDestinations> rl_possible_destinations = {
	BATHROOM, BEDROOM, UTILITY_ROOM
};


void InitializeGameSceneLinkFunctions()
{
	rl_connection_data = injector::auto_pointer(0x0063b190);
	sb_connection_data = injector::auto_pointer(0x0063b3b0);
}