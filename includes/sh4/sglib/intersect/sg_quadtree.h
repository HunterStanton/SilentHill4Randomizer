#pragma once

struct sgQTNode {
    int dummy;
};

struct sgQTBounding {
    float center[4];
    float radius;
};

struct sgQTObject {
    struct sgQTBounding bounding_ball;
    struct sgQTObject* next;
    struct sgQTObject* prev;
};