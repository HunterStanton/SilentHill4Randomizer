#pragma once
#include "CommonTypes.h"

extern injector::hook_back<void(__cdecl*)(Position*, unsigned int)> CameraEngine_SetCameraPosition;
void __cdecl CameraEngine_SetCameraPositionHook(Position* pos, unsigned int ContinueMvMode);
void InitializeGameCameraFunctions();