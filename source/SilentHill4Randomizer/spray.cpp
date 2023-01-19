#include "stdafx.h"
#include "sh4/game/effect/particle/spray.h"
#include "sh4/sys/apps/sf_obj.h"
#include <plog/Log.h>

injector::hook_back<void(__cdecl*)(int)> PlayerSpray_Start;
injector::hook_back<void(__cdecl*)(int)> PlayerSpray_Stop;
injector::hook_back<void(__cdecl*)(Position*, Position*, int)> PlayerSpray_PosAndSpeedSet;
injector::hook_back<SplayCmnData* (__cdecl*)(sfObj*)> SupportParticle_CmnData;
injector::hook_back<void(__cdecl*)(sfObj*, Position*, Position*)> SplayParticle_GeneratePosSpdSet;

Color origSprayColor = { 0x78, 0x78, 0x78, 0x18 };
Color greenSprayColor = { 0x00, 0xFF, 0x00, 0x1e };

int is_spraying_hyperspray = 0;

void SplayParticle_GeneratePosSpdSetHook(sfObj* obj, Position* pos, Position* speed)
{
	// recolor the spray particles if Hyper Spray is being used
	auto data = SupportParticle_CmnData.fun(obj);
	if (is_spraying_hyperspray)
	{
		data->Rgba = greenSprayColor;
	}
	else
	{
		data->Rgba = origSprayColor;
	}
	return SplayParticle_GeneratePosSpdSet.fun(obj, pos, speed);
}

void InitializeSprayFunctions()
{
	PlayerSpray_Start.fun = injector::auto_pointer(0x0043b260);
	PlayerSpray_Stop.fun = injector::auto_pointer(0x0043b290);
	PlayerSpray_PosAndSpeedSet.fun = injector::auto_pointer(0x0043b230);
	SupportParticle_CmnData.fun = injector::auto_pointer(0x0043b920);
	SplayParticle_GeneratePosSpdSet.fun = injector::MakeCALL(0x0043b24d, SplayParticle_GeneratePosSpdSetHook, true).get();
}
