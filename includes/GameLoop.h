#pragma once

#include "stdafx.h"
#include "Randomizer.h"
#include <plog/Log.h>

extern injector::hook_back<void(__cdecl*)()> GameLoop;
void InitializeGameLoopFunction();
