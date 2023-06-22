#include "stdafx.h"
#include "sh4/game/player/player_anime_proc.h"
#include <plog/Log.h>

// list of pointers to anim tables for various weapons
static int motion_handgun = 0x006953c8;
static int motion_pipe = 0x00695508;
static int motion_cutter = 0x006955a8;
static int motion_bottle_broken = 0x00695968;
static int motion_scoop = 0x00695828;
static int motion_axe = 0x00695468;
static int motion_pick = 0x006958c8;
static int motion_stun = 0x00695648;
static int motion_spray = 0x006956e8;
static int motion_chain = 0x00695788;

std::vector<int> motion_battle = {
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	motion_handgun, motion_handgun, motion_pipe,
	motion_cutter, motion_pipe, motion_pipe, motion_pipe, motion_pipe, motion_pipe, motion_pipe,
	motion_pipe, motion_pipe, motion_pipe, motion_pipe, motion_pipe, motion_pipe, motion_pipe,
	motion_pipe, motion_pipe, motion_pipe, motion_pipe, motion_pipe, motion_pipe, motion_pipe,
	motion_pipe, motion_pipe, motion_pipe, motion_pipe, motion_pipe, motion_cutter,
	motion_bottle_broken, motion_scoop, motion_axe, motion_pick, motion_stun, motion_spray,
	motion_pipe, motion_chain, motion_pipe, motion_pipe, motion_pipe, motion_pipe, motion_pipe,
	motion_pipe, motion_pipe, motion_pipe, motion_pipe, motion_pipe, motion_pipe, motion_pipe,
	motion_pipe, motion_pipe, motion_pipe, motion_pipe, motion_pipe, motion_pipe, motion_pipe,
	motion_pipe, motion_pipe, motion_pipe, motion_pipe, motion_pipe, motion_pipe, motion_pipe,
	motion_pipe, motion_pipe, motion_pipe, motion_pipe, motion_pipe, motion_pipe, motion_pipe,
	motion_pipe, motion_pipe, motion_pipe, motion_pipe, motion_pipe, motion_pipe, motion_pipe,
	motion_pipe, motion_pipe, motion_pipe, motion_pipe, motion_pipe, motion_pipe, motion_pipe,
	motion_pipe, motion_pipe, motion_pipe, motion_pipe, motion_pipe, motion_pipe, motion_pipe,
	motion_pipe, motion_pipe, motion_pipe, motion_pipe, motion_pipe, motion_pipe, motion_pipe,
	motion_pipe, motion_pipe, motion_pipe, motion_pipe, motion_pipe, motion_pipe, motion_pipe,
	motion_pipe, motion_pipe, motion_pipe, motion_pipe, motion_pipe, motion_pipe, motion_pipe,
	motion_pipe, motion_pipe, motion_pipe, motion_pipe, motion_pipe, motion_pipe, motion_pipe,
	motion_pipe, motion_pipe, motion_pipe, motion_pipe, motion_pipe, motion_pipe, motion_pipe,
	motion_pipe, motion_pipe, motion_pipe, motion_pipe, motion_pipe, motion_pipe, motion_pipe,
	motion_pipe, motion_pipe, motion_pipe, motion_pipe, motion_pipe, motion_pipe, motion_pipe,
	motion_pipe, motion_pipe, motion_pipe, motion_pipe, motion_pipe, motion_pipe, motion_pipe,
	motion_pipe, motion_pipe, motion_pipe, motion_pipe, motion_pipe, motion_pipe, motion_pipe,
	motion_pipe, motion_pipe, motion_pipe, motion_pipe, motion_pipe, motion_pipe, motion_pipe,
	motion_pipe, motion_pipe, motion_pipe, motion_pipe, motion_pipe, motion_pipe, motion_pipe,
	motion_pipe, motion_pipe, motion_pipe, motion_pipe, motion_pipe, motion_pipe, motion_pipe,
	motion_pipe, motion_pipe, motion_pipe, motion_pipe, motion_pipe, motion_pipe, motion_pipe,
	motion_pipe, motion_pipe, motion_pipe, motion_pipe, motion_pipe, motion_pipe, motion_pipe,
	motion_pipe, motion_pipe, motion_pipe, motion_pipe, motion_pipe, motion_pipe, motion_pipe,
	motion_pipe, motion_pipe, motion_pipe, motion_pipe, motion_pipe, motion_pipe, motion_pipe,
	motion_pipe, motion_pipe, motion_pipe, motion_pipe, motion_pipe, motion_pipe, motion_pipe,
	motion_pipe, motion_pipe, motion_pipe, motion_pipe, motion_pipe, motion_pipe,
	// hyper spray
	motion_spray,
	// gold pipe
	motion_pipe,
	// silver pipe
	motion_pipe
};