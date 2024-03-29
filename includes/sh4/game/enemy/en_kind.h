#pragma once

enum EnemyKind : unsigned char
{
	ENEMY_KIND_NOTHING,
	ENEMY_KIND_CELL,
	ENEMY_KIND_MUSH,
	ENEMY_KIND_BUZZ,
	ENEMY_KIND_MM,
	ENEMY_KIND_WALLMAN,
	ENEMY_KIND_WHEEL,
	ENEMY_KIND_JINMEN,
	ENEMY_KIND_TWINS,
	ENEMY_KIND_HIL,
	ENEMY_KIND_HYENA,
	ENEMY_KIND_MULTI,
	ENEMY_KIND_PICKGIRL,
	ENEMY_KIND_FLAMES,
	ENEMY_KIND_FAT,
	ENEMY_KIND_SCRATCH,
	ENEMY_KIND_KILLER,
	ENEMY_KIND_NURSE,
	ENEMY_KIND_SAMPLE,
	ENEMY_KIND_MAX,
	ENEMY_KIND_TEST00 = 0,
	ENEMY_KIND_ALL = 0x13
};

struct EnemyFileMapping
{
	EnemyKind kind;
	std::vector<unsigned int> fileIds;
	unsigned int tableAddr;
};

struct EnemyKindTableEntry
{
	unsigned int* sfConstructor;
	unsigned int* objConstructor;
	unsigned int* objDestructor;
	unsigned int* objDraw;
};

enum EnemySeKind : unsigned char
{
	ENEMY_SE_KIND_NOTHING,
	ENEMY_SE_KIND_CELL,
	ENEMY_SE_KIND_MUSH,
	ENEMY_SE_KIND_BUZZ,
	ENEMY_SE_KIND_MM,
	ENEMY_SE_KIND_WALLMAN,
	ENEMY_SE_KIND_WHEEL,
	ENEMY_SE_KIND_JINMEN,
	ENEMY_SE_KIND_TWINS,
	ENEMY_SE_KIND_HIL,
	ENEMY_SE_KIND_HYENA,
	ENEMY_SE_KIND_MULTI,
	ENEMY_SE_KIND_PICKGIRL,
	ENEMY_SE_KIND_FLAMES,
	ENEMY_SE_KIND_FAT,
	ENEMY_SE_KIND_SCRATCH,
	ENEMY_SE_KIND_KILLER0,
	ENEMY_SE_KIND_KILLER1,
	ENEMY_SE_KIND_KILLER2,
	ENEMY_SE_KIND_KILLER3,
	ENEMY_SE_KIND_NURSE,
	ENEMY_SE_KIND_MAX
};

extern const std::vector<EnemyFileMapping> possibleEnemies;
extern injector::hook_back<unsigned int(__cdecl*)(EnemyKind)> EnemyKindTableGetAddress;
unsigned int __cdecl EnemyKindTableGetAddressHook(EnemyKind enemyType);
void InitializeEnemyKindFunctions();