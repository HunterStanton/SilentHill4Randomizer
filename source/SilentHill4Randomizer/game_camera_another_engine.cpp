#include "stdafx.h"
#include "Randomizer.h"
#include "sh4/game/gamemain/camera/game_camera_another_engine.h"
#include "sh4/game/gamemain/game.h"

injector::hook_back<void(__cdecl*)(Position*, unsigned int)> CameraEngine_SetCameraPosition;

void __cdecl CameraEngine_SetCameraPositionHook(Position* pos, unsigned int ContinueMvMode)
{
	if (gameW != NULL && gameW->player != NULL)
	{
		pos->x = gameW->player->pos.x;
		pos->y = gameW->player->pos.y;
		pos->z = gameW->player->pos.z;
	}
	CameraEngine_SetCameraPosition.fun(pos, ContinueMvMode);
	return;
}

void InitializeGameCameraFunctions()
{
	//CameraEngine_SetCameraPosition.fun = injector::MakeCALL(0x0050355e, CameraEngine_SetCameraPositionHook, true).get();
	//CameraEngine_SetCameraPosition.fun = injector::MakeCALL(0x005036c2, CameraEngine_SetCameraPositionHook, true).get();
	//CameraEngine_SetCameraPosition.fun = injector::MakeCALL(0x005036db, CameraEngine_SetCameraPositionHook, true).get();
}
