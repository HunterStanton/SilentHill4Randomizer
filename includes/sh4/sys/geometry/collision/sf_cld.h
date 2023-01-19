#pragma once

#include "sh4/sglib/intersect/sg_quadtree.h"
#include "sh4/sglib/animation/sg_bone.h"


struct sfCldLine
{
	float start[4];
	float end[4];
};

struct sfCldSphere
{
	float center[4];
	float radius;
};

struct sfCldAABB
{
	float bmin[4];
	float bmax[4];
};

struct sfCldOBB
{
	float mat[4][4];
	float half_w[4];
};

struct sfOffsetAABB
{
	sfCldAABB aabb;
	float offset[4];
};

union sfCldBody
{
	sfCldOBB obb;
	sfCldAABB aabb;
	sfOffsetAABB offset_aabb;
	sfCldLine line;
	sfCldSphere sphere;
};

struct sfCldPart
{
	sfCldBody world_hit;
	sfCldBody local_hit;
	unsigned char hit_type;
	unsigned char pad[3];
	int hit_kind;
	sgBone* parent;
	void* data;
	void* parent_cld;
};

struct sfCldObject {
    sgQTObject tree_object;
    sgQTNode* stay_node;
    sfCldPart* parts;
    unsigned char n_parts;
    unsigned char pad[3];
    void* data;
    char unk[34];
};