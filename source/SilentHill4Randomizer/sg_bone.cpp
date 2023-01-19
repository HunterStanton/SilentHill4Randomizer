#include "stdafx.h"
#include "sh4/sglib/animation/sg_bone.h"
#include <plog/Log.h>

injector::hook_back<void(__cdecl*)(sgBone*, Position*)> sgBoneGetAbsRot;
injector::hook_back<void(__cdecl*)(Position*, FourByFourMatrix*, Position*)> sgBoneGetAbsMatrix;
injector::hook_back<Position *(__cdecl*)(sgBone*, FourByFourMatrix *)> sgBoneGetEuclideanDistance;

void InitializeSgBoneFunctions()
{
	sgBoneGetAbsRot.fun = injector::auto_pointer(0x00419ff0).get();
	sgBoneGetAbsMatrix.fun = injector::auto_pointer(0x004217b0).get();
	sgBoneGetEuclideanDistance.fun = injector::auto_pointer(0x0041a060).get();
}