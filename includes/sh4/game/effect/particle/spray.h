#pragma once

#include "CommonTypes.h"
#include "sh4/sys/apps/sf_obj.h"

struct SplayCmnData
{
	float PolyLen;
	float PolyAreaAddSpd;
	float PtclLifeTime;
	Color Rgba;
	float UseDragRate;
};

extern void InitializeSprayFunctions();

extern sfObj* sprayObj;

extern int is_spraying_hyperspray;

extern Color origSprayColor;
extern Color greenSprayColor;

extern injector::hook_back<void(__cdecl*)(int)> PlayerSpray_Start;
extern injector::hook_back<void(__cdecl*)(int)> PlayerSpray_Stop;
extern injector::hook_back<void(__cdecl*)(Position*, Position*, int)> PlayerSpray_PosAndSpeedSet;
extern injector::hook_back<SplayCmnData* (__cdecl*)(sfObj*)> SupportParticle_CmnData;
extern injector::hook_back<void(__cdecl*)(sfObj*, Position*, Position*)> SplayParticle_GeneratePosSpdSet;
