#pragma once

struct Color
{
	unsigned char red;
	unsigned char green;
	unsigned char blue;
	unsigned char alpha;
};

extern injector::hook_back<void(__cdecl*)(Color*)> sfSceneSetFogColor;
void __cdecl sfSceneSetFogColorHook(Color* color);

extern injector::hook_back<void(__cdecl*)(float, unsigned char, float, unsigned char)> sfSceneSetFogPower;
void __cdecl sfSceneSetFogPowerHook(float nearPow, unsigned char nearPow2, float farPow, unsigned char farPow2);