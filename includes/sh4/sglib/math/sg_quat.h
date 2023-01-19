#pragma once

#include "CommonTypes.h"

extern void InitializeSgQuatFunctions();

extern injector::hook_back<void(__cdecl*)(Position*, Position*, float)> sgQuatFromAxisAngle;
extern injector::hook_back<void(__cdecl*)(Position*, Position*, Position*)> sgQuatMul;
extern injector::hook_back<void(__cdecl*)(Position*, Position*, Position*)> sgQuatMulVector;
extern injector::hook_back<void(__cdecl*)(Position*, Position*)> sgQuatGetEuclideanDistance;
