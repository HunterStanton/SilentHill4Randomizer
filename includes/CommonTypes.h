#pragma once


union CommonUnion {
    int si;
    unsigned int ui;
    void* pt;
    short ss[2];
    unsigned short us[2];
    char sc[4];
    unsigned char uc[4];
    float f;
    float fv[1];
    int iv[1];
};

struct Position
{
	float x;
	float y;
	float z;
	float w;
};

struct FourByFourMatrix
{
    Position matrix[4];
};

struct Color
{
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;
};