#pragma once

#include "CommonTypes.h"

struct sfObj {
    CommonUnion fwork[256];
    CommonUnion* work;
    void* sfObjFunc;
    CommonUnion* work_pt0;
    CommonUnion* work_pt1;
    unsigned short step;
    unsigned short step_s;
    unsigned short kind;
    unsigned short pad;
    CommonUnion* sys_work;
    CommonUnion* scene_work;
    int* event_work;
    CommonUnion* objhit_work;
    void* sfObjDestructor;
    short flag;
    short thread_no;
};