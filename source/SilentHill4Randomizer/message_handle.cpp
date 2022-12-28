#include "stdafx.h"
#include "Randomizer.h"
#include "sh4/game/message/message_handle.h"
#include <plog/Log.h>

injector::hook_back<void(__cdecl*)(int, int, int, int)> MessagePut;

injector::hook_back<void(__cdecl*)(int, int)> MessageSubtitlesPut;

injector::hook_back<void(__cdecl*)(int, int)> MessageDemoSubtitlesPut;

injector::hook_back<void(__cdecl*)(int, int)> MessageMemoPut;

injector::hook_back<void(__cdecl*)(int, int)> MessageExplanationPut;