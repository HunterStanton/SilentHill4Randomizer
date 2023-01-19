#pragma once

#include "sh4/sglib/animation/sg_anime.h"
#include "sh4/sglib/renderer/TErender/sg_temodel.h"
#include "sh4/sglib/renderer/TErender/sg_svmodel.h"

struct sfCharacter {
    sgBone root;
    sgAnime anime_work;
    sgTEModel model_work;
    sgSVModel sv_model;
    sgAnime* anime;
    unsigned short flag;
};

extern void InitializeSfCharacterFunctions();
extern injector::hook_back<sgBone*(__cdecl*)(sfCharacter*, unsigned int)> sfCharacterBone;
