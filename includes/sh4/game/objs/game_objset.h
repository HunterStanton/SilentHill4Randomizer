#pragma once

enum EntryTypes : short
{
	SceneNum = 0,
	ObjType = 1,
	SetExecutor = 2,
	SetConstructor = 3,
	SetDestructor = 4,
	SetRender = 5,
	SetAllFuncs = 6,
	SetEnemy = 7,
	SetXYZW = 8,
	SetRotation = 9,
	SetID1234 = 10,
	Unknown = 11,
	Unknown2 = 12,
	Unknown3 = 13,
	Unknown4 = 14,
	Unknown5 = 15,
	Unknown6 = 16,
	Unknown7 = 17,
	Unknown8 = 18,
	Unknown9 = 19,
	Unknown10 = 20,
	Unknown11 = 21,
	Unknown12 = 22,
	Unknown13 = 23,
	SetEventDriver = 24,
	Unknown14 = 25,
	Unknown15 = 26,
	Unknown16 = 27
};

void LoadSceneSets();