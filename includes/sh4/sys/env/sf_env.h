#pragma once

#include "CommonTypes.h"

extern void InitializeSfEnvFunctions();

// gets the current frames per second as a floating point value
extern injector::hook_back<float(__cdecl*)()> sfSysEnvFps;