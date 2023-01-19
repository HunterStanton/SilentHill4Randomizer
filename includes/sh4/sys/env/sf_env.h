#pragma once

#include "CommonTypes.h"

extern void InitializeSfEnvFunctions();
extern injector::hook_back<float(__cdecl*)()> sfSysEnvFps;