#include "stdafx.h"
#include "sh4/game/misc/misc_iexplanation.h"
#include <plog/Log.h>

std::vector<ItemMessage> item_message_table = {
{ITEM_EMPTY,0x0,0x1},
{ITEM_SMALL_BULLET,0x2,0x3},
{ITEM_LARGE_BULLET,0x6,0x7},
{ITEM_SILVER_BULLET,0xA,0xB},
{ITEM_RED_CHRISM,0xE,0xF},
{ITEM_HOLY_CANDLE,0x12,0x13},
{ITEM_LOADS_PRAYER,0x17,0x18},
{ITEM_FINISHER,0xFE,0xFF},
{ITEM_SAINT_MEDALLION,0x1B,0x1C},
{ITEM_HEALTH_DRINK,0x1F,0x20},
{ITEM_AMPLE,0x182,0x183},
{ITEM_FIRST_AID_KIT,0x23,0x24},
{ITEM_HANDGUN,0x27,0x28},
{ITEM_REVOLVER,0x29,0x2A},
{ITEM_IRON_PIPE,0x2D,0x2E},
{ITEM_CUTTER_KNIFE,0x31,0x32},
{ITEM_METAL_BAT,0x35,0x36},
{ITEM_DRIVER,0x39,0x3A},
{ITEM_DRIVER_BROKEN,0x39,0x3D},
{ITEM_SPOON,0x41,0x42},
{ITEM_SPOON_BROKEN,0x41,0x45},
{ITEM_MID_MASHY,0x48,0x49},
{ITEM_MID_MASHY_BROKEN,0x48,0x4C},
{ITEM_MASHY_IRON,0x4F,0x50},
{ITEM_MASHY_IRON_BROKEN,0x4F,0x53},
{ITEM_MASHY,0x56,0x57},
{ITEM_MASHY_BROKEN,0x56,0x5A},
{ITEM_SPADE_MASHY,0x5D,0x5E},
{ITEM_SPADE_MASHY_BROKEN,0x5D,0x61},
{ITEM_MASHY_NIBLICK,0x64,0x65},
{ITEM_MASHY_NIBLICK_BROKEN,0x64,0x68},
{ITEM_PITCHER,0x6B,0x6C},
{ITEM_PITCHER_BROKEN,0x6B,0x6F},
{ITEM_NIBLICK,0x72,0x73},
{ITEM_NIBLICK_BROKEN,0x72,0x76},
{ITEM_PITCHING_WEDGE,0x79,0x7A},
{ITEM_PITCHING_WEDGE_BROKEN,0x79,0x7D},
{ITEM_SAND_WEDGE,0x80,0x81},
{ITEM_SAND_WEDGE_BROKEN,0x80,0x84},
{ITEM_PUTTER,0x87,0x88},
{ITEM_PUTTER_BROKEN,0x87,0x8B},
{ITEM_WINE_BOTTLE,0x8E,0x8F},
{ITEM_WINE_BOTTLE_BROKEN,0x92,0x93},
{ITEM_SCOOP,0x97,0x98},
{ITEM_RUSTY_HATCHET,0x9B,0x9C},
{ITEM_PICK_OF_DESPAIR,0x9F,0xA0},
{ITEM_STUN_GUN,0xA3,0xA4},
{ITEM_SPRAY,0xA7,0xA8},
{ITEM_CLUB,0xFA,0xFB},
{ITEM_CHAIN_SAW,0xAB,0xAC},
{ITEM_KEY_OF_LIBERATION,0xAF,0xB0},
{ITEM_COIN_OF_LYNCHSTREETLINE,0xB1,0xB2},
{ITEM_CHOCOLATE_MILK,0xB3,0xB4},
{ITEM_SHOVEL_WITH_BLOOD_CHARACTER,0xB5,0xB6},
{ITEM_RUSTY_BLOODY_KEY,0xB7,0xB8},
{ITEM_RED_PAPER_1,0xB9,0xBA},
{ITEM_RED_PAPER_2,0xB9,0xBA},
{ITEM_RED_PAPER_3,0xB9,0xBA},
{ITEM_RED_PAPER_4,0xB9,0xBA},
{ITEM_RED_PAPER_5,0xB9,0xBA},
{ITEM_RED_PAPER_6,0xB9,0xBA},
{ITEM_TORN_RED_PAPER_1,0xC5,0xC6},
{ITEM_TORN_RED_PAPER_2,0xC5,0xC6},
{ITEM_TORN_RED_PAPER_MISS,0xC5,0xC6},
{ITEM_KEY_OF_SUPERINTENDANT,0xC7,0xC8},
{ITEM_KEY_ROCKER106,0xC9,0xCA},
{ITEM_CASSETTE_TAPE,0xCC,0xCD},
{ITEM_KEY_WITH_DOLL,0xCE,0xCF},
{ITEM_CHARM_OF_SUCCUBUS,0xD0,0xD1},
{ITEM_KEY_OF_SICKROOM,0x18A,0x18B},
{ITEM_RED_ENVELOPE,0xD6,0xD7},
{ITEM_SMALL_KEY,0xD8,0xD9},
{ITEM_CYNTHIAS_PASS,0xDB,0xDC},
{ITEM_OLD_DOLL,0xDD,0xDE},
{ITEM_MASTER_KEY_TO_APART,0xDF,0xE0},
{ITEM_ARMORIAL_MEDAL,0xE1,0xE2},
{ITEM_PICK_OF_HOPE,0xE3,0xE4},
{ITEM_NAVEL_STRING,0xE5,0xE6},
{ITEM_ALESSAS_SPEAR,0xD2,0xD3},
{ITEM_DIRTY_ENVELOPE,0x0,0x0},
{ITEM_TOY_KEY,0x103,0x104},
{ITEM_1SS_COIN_DIRTY,0x106,0x107},
{ITEM_1SS_COIN,0x10B,0x10C},
{ITEM_SB24_KEY,0x10F,0x110},
{ITEM_HANDLE,0x113,0x114},
{ITEM_DOLLS_HEAD,0x118,0x119},
{ITEM_DOLLS_RIGHT_ARM,0x11D,0x11E},
{ITEM_DOLLS_LEFT_ARM,0x127,0x128},
{ITEM_DOLLS_RIGHT_LEG,0x12C,0x12D},
{ITEM_DOLLS_LEFT_LEG,0x131,0x132},
{ITEM_UNDERGROUND_KEY,0x186,0x187},
{ITEM_PRISONERS_SHIRT,0xF6,0xF7},
{ITEM_BILLIARD_BALL,0x136,0x137},
{ITEM_STUFFED_CAT,0x13C,0x13D},
{ITEM_VOLLEYBALL,0x142,0x143},
{ITEM_SMALL_CANDLE_PACKED,0x148,0x149},
{ITEM_SMALL_CANDLE,0x148,0x149},
{ITEM_GHOSTS_KEY,0x14E,0x14F},
{ITEM_DIRTY_STONE1,0x165,0x166},
{ITEM_DIRTY_STONE2,0x165,0x166},
{ITEM_DIRTY_STONE3,0x165,0x166},
{ITEM_DIRTY_STONE4,0x165,0x166},
{ITEM_DIRTY_STONE5,0x165,0x166},
{ITEM_CHANNELING_STONE1,0x16A,0x16B},
{ITEM_CHANNELING_STONE2,0x16A,0x16B},
{ITEM_CHANNELING_STONE3,0x16A,0x16B},
{ITEM_CHANNELING_STONE4,0x16A,0x16B},
{ITEM_CHANNELING_STONE5,0x16A,0x16B},
{ITEM_PLATE_OF_TEMPTATION,0x151,0x152},
{ITEM_PLATE_OF_ORIGIN,0x156,0x157},
{ITEM_PLATE_OF_SURVEILLANCE,0x15B,0x15C},
{ITEM_PLATE_OF_CHAOS,0x160,0x161},
{ITEM_ALBERT_SPORTS_KEY,0xF1,0xF2},
{ITEM_UNIFORM,0x18C,0x18D},
{ITEM_MZ_UPPER_KEY,0x190,0x191},
{ITEM_TRAILER_KEY,0xED,0xEE},
{ITEM_HANDBAG,0xE8,0xE9},
{ITEM_SUBMACHINEGUN,0x16E,0x16F},
{ITEM_BLACKJACK,0x173,0x174},
{ITEM_HORSEWHIP,0x178,0x179},
{ITEM_CHAIN,0x17D,0x17E},
{ITEM_CUSTOM_WEAPON, 2020, 2021 }
};