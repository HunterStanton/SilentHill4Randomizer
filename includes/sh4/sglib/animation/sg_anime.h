#pragma once

#include "CommonTypes.h"
#include "sh4/sglib/animation/sg_bone.h"
#include "sh4/sglib/animation/sg_ikhandle.h"

struct sgAnmData {
	unsigned int type_id;
	short total_time;
	short loop;
	int reserved_a;
	int reserved_b;
	unsigned int data[1];
};

struct sgAnime {
	sgAnmData* play_data[4];
	sgBone* transforms;
	int n_transforms;
	sgIKHandle* ik_handles;
	sgBone* object_space;
	void (*post_func)(void*);
	Position* reals;
	int n_reals;
	Position* vectors;
	int n_vectors;
	int current_time;
	int time_add;
	unsigned char play_status[4];
	unsigned short flag;
	unsigned short construct_check;
};

extern void InitializeSgAnimeFunctions();
extern injector::hook_back<float(__cdecl*)(sgAnime*)> sgAnimeCurrentFloatFrame;