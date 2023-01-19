#pragma once

enum sgIKSolveResult : unsigned char 
{
    SG_IK_RESULT_NONE = 0,
    SG_IK_RESULT_OK = 1,
    SG_IK_RESULT_BEYOND = 2
};

struct sgIKHandle 
{
    float acceleration[4][2];
    float damping_ratio;
    int* bone;
    int* start;
    int* end;
    void* solver;
    sgIKSolveResult solve_result;
    float reach_constrain;
    float close_constrain;
    int* next;
};