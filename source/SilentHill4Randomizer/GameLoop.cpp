#include "GameLoop.h"
#include "sh4/game/gamemain/game.h"
#include "sh4/game/message/message_handle.h"
#include "sh4/game/message/message_load.h"


injector::hook_back<void(__cdecl*)()> GameLoop;
// std::string formattedStr;
// int frame = 0;

void GameLoopHook()
{
	/*
	if (gameW->game_init_executed == 1)
	{
		formattedStr = std::format("Frame: {0}", frame);
		sfMessagePrint.fun((unsigned short*)convertMessage(formattedStr.c_str()), 0x12a, 0x152);
		frame++;
	}
	*/
	return;
}

void InitializeGameLoopFunction()
{
	GameLoop.fun = injector::MakeCALL(0x004150f4, GameLoopHook, true).get();
}