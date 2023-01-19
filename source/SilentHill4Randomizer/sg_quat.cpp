#include "stdafx.h"
#include "sh4/sglib/math/sg_quat.h"
#include <plog/Log.h>

injector::hook_back<void(__cdecl*)(Position*, Position*, float)> sgQuatFromAxisAngle;
injector::hook_back<void(__cdecl*)(Position*, Position*, Position*)> sgQuatMul;
injector::hook_back<void(__cdecl*)(Position*, Position*, Position*)> sgQuatMulVector;
injector::hook_back<void(__cdecl*)(Position*, Position*)> sgQuatGetEuclideanDistance;

void InitializeSgQuatFunctions()
{
	sgQuatFromAxisAngle.fun = injector::auto_pointer(0x00421b30);
	sgQuatMul.fun = injector::auto_pointer(0x005741d0);
	sgQuatMulVector.fun = injector::auto_pointer(0x00574300);
	sgQuatGetEuclideanDistance.fun = injector::auto_pointer(0x0041ac30);
}