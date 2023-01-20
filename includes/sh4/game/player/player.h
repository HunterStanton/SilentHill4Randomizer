#pragma once

#include "CommonTypes.h"
#include "sh4/game/gamemain/game_item.h"
#include "sh4/sglib/animation/sg_anime.h"
#include "sh4/sys/apps/sf_obj.h"
#include "sh4/sys/geometry/sf_chara.h"
#include "sh4/sys/geometry/collision/sf_cld.h"

struct _PLAYER_WORK {
	int num;
	int type;
	float life;
	float str;
	float def;
	float tire;
	int dull_count;
	int dulls;
	int dull_motion;
	int invincible;
	GameItem wp_last;
	float life_max;
	float str_max;
	float def_max;
	float ampule_time;
	int draw_flag;
	Position pos;
	Position v_pos;
	Position eyerot;
	Position prev_pos;
	Position rot;
	Position prev_rot;
	Position v_rot;
	sfCharacter chara;
	float field24_0x198[6];
	sfCharacter* obj;
	sgAnime* anim;
	sgAnime* anim_frame;
	int field28_0x1bc;
	sfCldObject cld_obj;
	sfObj* ch_obj;
	int battle_stat;
	int holy_stat;
	float power_attack;
	int damage;
	int gotmode;
	int hold;
	int hold_kind;
	float hold_time;
	int gun_ikset;
	float gun_angle;
	sfObj* target;
	int target_mode;
	GameItem weapon_kind;
	sfCharacter weapon_chr;
	Position weapon_pos;
	sfCharacter* wp_chr;
	sfObj* wp_obj;
	sfCldObject weapon_cld;
	sfCldObject* wp_cld;
	int cld_entry;
	GameItem holy_kind;
	int autolock;
	int sword_stat;
	int enemy_near;
	int anime_process;
	int anime_sub;
	int anim_ctrl;
	int slot_frame;
	int link_anim;
	int slot_link;
	float anim_speed;
	float hit_reduce;
	int auto_search;
	int pos_f;
	Position pos_bak;
	Position rot_bak;
	Position last_neck;
	int advance_only;
	int who;
	char field70_0x410[16];
};

extern injector::hook_back<int(__cdecl*)(int, float)> PlayerDamage;
int __cdecl PlayerDamageHook(int num, float damage);
void InitializePlayerFunctions();