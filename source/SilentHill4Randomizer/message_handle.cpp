#include "stdafx.h"
#include "Randomizer.h"
#include "sh4/game/message/message_handle.h"
#include <plog/Log.h>

injector::hook_back<void(__cdecl*)(int, int, int, int)> MessagePut;

injector::hook_back<void(__cdecl*)(int, int)> MessageSubtitlesPut;

injector::hook_back<void(__cdecl*)(int, int)> MessageDemoSubtitlesPut;

injector::hook_back<void(__cdecl*)(int, int)> MessageMemoPut;

injector::hook_back<void(__cdecl*)(int, int)> MessageExplanationPut;

injector::hook_back<void(__cdecl*)(unsigned short*, int, int)> sfMessagePrint;

void InitializeMessageHandleFunctions()
{
	MessagePut.fun = injector::auto_pointer(0x0050b580);
	MessageSubtitlesPut.fun = injector::auto_pointer(0x0050c2a0);
	MessageDemoSubtitlesPut.fun = injector::auto_pointer(0x0050b1c0);
	MessageMemoPut.fun = injector::auto_pointer(0x0050c340);
	MessageExplanationPut.fun = injector::auto_pointer(0x0050c300);
	sfMessagePrint.fun = injector::auto_pointer(0x00559e70);
}