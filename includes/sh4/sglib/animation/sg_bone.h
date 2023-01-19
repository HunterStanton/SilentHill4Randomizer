#pragma once

#include "CommonTypes.h"

struct sgBone {
    Position rot;
    Position trans;
    Position scale;
    Position abs_rot;
    Position abs_trans;
    sgBone* parent;
    sgBone* child_list;
    sgBone* child_sibling;
    unsigned short last;
    unsigned short flag;
    float partly_blend_rate;
    float field11_0x64;
    float field12_0x68;
    float field13_0x6c;
};

extern void InitializeSgBoneFunctions();

extern injector::hook_back<void(__cdecl*)(sgBone*, Position*)> sgBoneGetAbsRot;
extern injector::hook_back<void(__cdecl*)(Position*, FourByFourMatrix*, Position*)> sgBoneGetAbsMatrix;
extern injector::hook_back<Position *(__cdecl*)(sgBone*, FourByFourMatrix*)> sgBoneGetEuclideanDistance;
