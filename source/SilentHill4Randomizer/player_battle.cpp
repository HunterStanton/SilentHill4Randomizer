#include "stdafx.h"
#include "Randomizer.h"
#include <plog/Log.h>
#include "CommonTypes.h"
#include "sh4/game/gamemain/game.h"
#include "sh4/game/effect/particle/spray.h"
#include "sh4/sys/geometry/sf_chara.h"
#include "sh4/sys/env/sf_env.h"
#include "sh4/sglib/animation/sg_bone.h"
#include "sh4/sglib/math/sg_quat.h"
#include "sh4/game/player/battle/player_battle.h"
#include "sh4/game/player/player_another_ui.h"
#include "sh4/game/player/battle/player_weapon.h"

injector::hook_back<void(__cdecl*)()> battle_anotherworld;
injector::hook_back<int(__cdecl*)()> normal_attack_all;
injector::hook_back<int(__cdecl*)(GameItem)> PlayerWeaponChargable;

sfObj* sprayObj;

int __cdecl normal_attack_allHook()
{
	int ret = normal_attack_all.fun();

	// take away 1 unit of health on every spray
	if (gameW->player->weapon_kind == ITEM_GREEN_HYPER_SPRAY)
	{
		if (gameW->player->life < 0.01f)
		{
			gameW->player->life = 0.0f;
		}
		else
		{
			gameW->player->life = gameW->player->life - 0.01f;
		}
	}

	return ret;
}

void __cdecl battle_anotherworldHook()
{

	sprayObj = injector::ReadMemory<sfObj*>(0x00fcdf80, true);

	// call original battle_anotherworld
	// this shouldn't cause any problems because the Spray checks are done at the end of the func
	battle_anotherworld.fun();

	GameItem kind = gameW->player->weapon_kind;
	int battleStat = gameW->player->battle_stat;

	int* is_spraying = injector::auto_pointer(0x010a1e9c);
	Position* quatPtr = injector::auto_pointer(0x006112e0);
	Position* quatPtr2 = injector::auto_pointer(0x006112c0);

	// copy the original spray can logic and modify it so it works for the Hyper Spray(s)
	if (battleStat != 0)
	{
		if (kind == ITEM_GREEN_HYPER_SPRAY)
		{
			if (battleStat == 3)
			{
				// if player is spraying hyper spray, do the original spray FX stuff
				float frame = sgAnimeCurrentFloatFrame.fun(gameW->player->anim_frame);
				float curFps = sfSysEnvFps.fun();
				float startTime = PlayerWeaponGetStartTime.fun(kind, 0);
				float endTime = PlayerWeaponGetEndTime.fun(kind, 0);

				if ((startTime + 0.1 < curFps * frame) && (endTime > curFps * frame) && (gameW->player->anim_ctrl == 0x23 || gameW->player->anim_ctrl == 0x24))
				{
					Position temp = { 35.0, 15.0, 12.0, 1.0 };
					FourByFourMatrix temp2 = { 0 };
					Position absRot = { 0,0,0,0 };
					Position angleQuat = { 0,0,0,0 };
					Position sprayPos = { 0,0,0,0 };
					Position vectorMultipliedQuat = { 0,0,0,0 };
					sgBone* bone = sfCharacterBone.fun(gameW->player->obj, 0x19);


					// calculate where to draw the spray cloud (Henry's right hand bone, bone 0x19, is roughly where the spray should spawn)
					sgBoneGetEuclideanDistance.fun(bone, &temp2);
					sgBoneGetAbsMatrix.fun(&sprayPos, &temp2, &temp);
					sgBoneGetAbsRot.fun(bone, &absRot);
					sgQuatFromAxisAngle.fun(&angleQuat, quatPtr, 0.7853982f);
					sgQuatMul.fun(&absRot, &absRot, &angleQuat);
					sgQuatMulVector.fun(&vectorMultipliedQuat, &absRot, quatPtr2);
					sgQuatGetEuclideanDistance.fun(&vectorMultipliedQuat, &vectorMultipliedQuat);


					vectorMultipliedQuat.x = vectorMultipliedQuat.x * 1400.0f;
					vectorMultipliedQuat.y = vectorMultipliedQuat.y * 1400.0f;
					vectorMultipliedQuat.z = vectorMultipliedQuat.z * 1400.0f;
					PlayerSpray_PosAndSpeedSet.fun(&sprayPos, &vectorMultipliedQuat, 0);

					if (*is_spraying == 0)
					{
						*is_spraying = 1;
						is_spraying_hyperspray = 1;
						auto data = SupportParticle_CmnData.fun(sprayObj);
						data->Rgba = greenSprayColor;
						PlayerSpray_Start.fun(0);
						return;
					}
				}
			}
			if (*is_spraying == 1)
			{
				*is_spraying = 0;
				is_spraying_hyperspray = 0;
				auto data = SupportParticle_CmnData.fun(sprayObj);
				data->Rgba = greenSprayColor;
				PlayerSpray_Stop.fun(0);
				return;
			}
		}
	}

	return;
}

int __cdecl PlayerWeaponChargableHook(GameItem item)
{
	if (item == ITEM_EMPTY) {
		return item;
	}
	return (0.0 < wp_param[item - 16].charge_time);
}

void InitializePlayerBattleFunctions()
{
	battle_anotherworld.fun = injector::MakeCALL(0x0053933c, battle_anotherworldHook, true).get();
	normal_attack_all.fun = injector::MakeJMP(0x0053d5c7, normal_attack_allHook, true).get();

	PlayerWeaponChargable.fun = injector::MakeCALL(0x0053b188, PlayerWeaponChargableHook, true).get();
	PlayerWeaponChargable.fun = injector::MakeCALL(0x0053cbac, PlayerWeaponChargableHook, true).get();
	PlayerWeaponChargable.fun = injector::MakeCALL(0x0053ce82, PlayerWeaponChargableHook, true).get();
	PlayerWeaponChargable.fun = injector::MakeCALL(0x0053d144, PlayerWeaponChargableHook, true).get();
	PlayerWeaponChargable.fun = injector::MakeCALL(0x0053d4f3, PlayerWeaponChargableHook, true).get();
	PlayerWeaponChargable.fun = injector::MakeCALL(0x00540a97, PlayerWeaponChargableHook, true).get();
	PlayerWeaponChargable.fun = injector::MakeCALL(0x00540ef3, PlayerWeaponChargableHook, true).get();

}