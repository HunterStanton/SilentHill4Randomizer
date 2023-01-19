#pragma once

#include "CommonTypes.h"
#include "sh4/sglib/renderer/TErender/model3.h"

struct sgTEModel {
    Model* model;
    void* texture;
    void* texture_global;
    Position* matrices;
    float* weights;
    Position* tex_crops;
    void (*texture_load_func)(int*, int, int, float*);
    int equip_flag;
};