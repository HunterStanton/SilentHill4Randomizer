#include "stdafx.h"
#include "sh4/game/gamemain/game_gi_para.h"
#include "Randomizer.h"
#include <plog/Log.h>

std::vector<_GetItemParamFileDt> item_param_fileid_default = {
	{ 0xF050F057, 0xF070F057, ITEM_HOLY_CANDLE }
};

std::vector<_GetItemParamFileDt> item_param_fileid = {
	// vanilla items
	{ 0xf000f003, 0xf001f003, ITEM_SMALL_BULLET }, { 0xf002f003, 0xf003f003, ITEM_LARGE_BULLET }, { 0xf00ef003, 0xf00ff003, ITEM_SILVER_BULLET },
	{ 0xf00af003, 0xf00bf003, ITEM_HOLY_CANDLE }, { 0xf00cf003, 0xf00df003, ITEM_SAINT_MEDALLION }, { 0xf004f003, 0xf005f003, ITEM_HEALTH_DRINK },
	{ 0xf006f003, 0xf007f003, ITEM_FIRST_AID_KIT }, { 0xf008f003, 0xf009f003, ITEM_AMPLE }, { 0xf000f192, 0xf001f192, ITEM_ALESSAS_SPEAR },
	{ 0xf012f003, 0xf013f003, ITEM_PLATE_OF_TEMPTATION }, { 0xf014f003, 0xf015f003, ITEM_PLATE_OF_ORIGIN }, { 0xf016f003, 0xf017f003, ITEM_PLATE_OF_SURVEILLANCE },
	{ 0xf018f003, 0xf019f003, ITEM_PLATE_OF_CHAOS }, { 0xf04cf057, 0xf06ef057, ITEM_FINISHER }, { 0xf01cf003, 0xf01df003, ITEM_DIRTY_STONE1 },
	{ 0xf01cf003, 0xf01df003, ITEM_DIRTY_STONE2 }, { 0xf01cf003, 0xf01df003, ITEM_DIRTY_STONE3 }, { 0xf01cf003, 0xf01df003, ITEM_DIRTY_STONE4 },
	{ 0xf01cf003, 0xf01df003, ITEM_DIRTY_STONE5 }, { 0xf00ef057, 0xf05bf057, ITEM_DRIVER }, { 0xf012f057, 0xf05cf057, ITEM_SPOON },
	{ 0xf016f057, 0xf05df057, ITEM_MID_MASHY }, { 0xf01af057, 0xf05ef057, ITEM_MASHY_IRON }, { 0xf01ef057, 0xf05ff057, ITEM_MASHY },
	{ 0xf022f057, 0xf060f057, ITEM_SPADE_MASHY }, { 0xf026f057, 0xf061f057, ITEM_MASHY_NIBLICK }, { 0xf02af057, 0xf062f057, ITEM_PITCHER },
	{ 0xf02ef057, 0xf063f057, ITEM_NIBLICK }, { 0xf032f057, 0xf064f057, ITEM_PITCHING_WEDGE }, { 0xf036f057, 0xf065f057, ITEM_SAND_WEDGE },
	{ 0xf03af057, 0xf066f057, ITEM_PUTTER }, { 0xf00ff057, 0xf05bf057, ITEM_DRIVER_BROKEN }, { 0xf013f057, 0xf05cf057, ITEM_SPOON_BROKEN },
	{ 0xf017f057, 0xf05df057, ITEM_MID_MASHY_BROKEN }, { 0xf01bf057, 0xf05ef057, ITEM_MASHY_IRON_BROKEN }, { 0xf01ff057, 0xf05ff057, ITEM_MASHY_BROKEN },
	{ 0xf023f057, 0xf060f057, ITEM_SPADE_MASHY_BROKEN }, { 0xf027f057, 0xf061f057, ITEM_MASHY_NIBLICK_BROKEN }, { 0xf02bf057, 0xf062f057, ITEM_PITCHER_BROKEN },
	{ 0xf02ff057, 0xf063f057, ITEM_NIBLICK_BROKEN }, { 0xf033f057, 0xf064f057, ITEM_PITCHING_WEDGE_BROKEN }, { 0xf037f057, 0xf065f057, ITEM_SAND_WEDGE_BROKEN },
	{ 0xf03bf057, 0xf066f057, ITEM_PUTTER_BROKEN }, { 0xf000f004, 0xf001f004, ITEM_IRON_PIPE }, { 0xf00cf057, 0xf05af057, ITEM_HANDGUN },
	{ 0xf004f057, 0xf056f057, ITEM_WINE_BOTTLE }, { 0xf005f057, 0xf057f057, ITEM_WINE_BOTTLE_BROKEN }, { 0xf000f01c, 0xf001f01c, ITEM_CUTTER_KNIFE },
	{ 0xf002f01c, 0xf003f01c, ITEM_STUN_GUN }, { 0xf046f057, 0xf06bf057, ITEM_SPRAY }, { 0xf002f004, 0xf003f004, ITEM_SCOOP },
	{ 0xf000f018, 0xf001f018, ITEM_CHOCOLATE_MILK }, { 0xf000f019, 0xf001f019, ITEM_CHARM_OF_SUCCUBUS }, { 0xf002f019, 0xf003f019, ITEM_RED_ENVELOPE },
	{ 0xf004f019, 0xf005f019, ITEM_DIRTY_ENVELOPE }, { 0xf000f01b, 0xf001f01b, ITEM_KEY_WITH_DOLL }, { 0xf01af003, 0xf01bf003, ITEM_RED_DIARY_0408 },
	{ 0xf01af003, 0xf01bf003, ITEM_RED_DIARY_0404 }, { 0xf01af003, 0xf01bf003, ITEM_RED_DIARY_0502 }, { 0xf01af003, 0xf01bf003, ITEM_RED_DIARY_0514 },
	{ 0xf01af003, 0xf01bf003, ITEM_RED_DIARY_0520 }, { 0xf01af003, 0xf01bf003, ITEM_RED_DIARY_0611 }, { 0xf01af003, 0xf01bf003, ITEM_RED_DIARY_0614 },
	{ 0xf01af003, 0xf01bf003, ITEM_RED_DIARY_SOMETIMEAGO }, { 0xf01af003, 0xf01bf003, ITEM_RED_DIARY_0713 }, { 0xf01af003, 0xf01bf003, ITEM_RED_DIARY_0720 },
	{ 0xf01af003, 0xf01bf003, ITEM_RED_DIARY_0717 }, { 0xf01af003, 0xf01bf003, ITEM_RED_DIARY_0718 }, { 0xf01af003, 0xf01bf003, ITEM_RED_DIARY_0723 },
	{ 0xf01af003, 0xf01bf003, ITEM_RED_DIARY_0725 }, { 0xf014f017, 0xf015f017, ITEM_FIRST_LETTER }, { 0xf016f017, 0xf017f017, ITEM_SCRAP_OF_BOOK },
	{ 0xf009f017, 0xf00af017, ITEM_SUPERINTENDANTS_MEMO }, { 0xf00bf017, 0xf00cf017, ITEM_SCRAP_OF_RED_DIARY }, { 0xf00df017, 0xf00ef017, ITEM_SCRAP_OF_RED_DIARY_2 },
	{ 0xf00ff017, 0xf010f017, ITEM_MIKES_LOVELETTER }, { 0xf000f01d, 0xf001f01d, ITEM_JOSEPHS_LETTER }, { 0xf000f063, 0xf001f063, ITEM_HANDLE },
	{ 0xf002f063, 0xf003f063, ITEM_COIN_OF_LYNCHSTREETLINE }, { 0xf004f063, 0xf005f063, ITEM_CYNTHIAS_PASS }, { 0xf00bf0b6, 0xf002f0b6, ITEM_CHAIN },
	{ 0xf00af05a, 0xf005f05a, ITEM_HORSEWHIP }, { 0xf03ef057, 0xf067f057, ITEM_PICK_OF_DESPAIR }, { 0xf005f0b6, 0xf000f0b6, ITEM_DOLLS_HEAD },
	{ 0xf006f0b6, 0xf000f0b6, ITEM_DOLLS_RIGHT_ARM }, { 0xf007f0b6, 0xf000f0b6, ITEM_DOLLS_LEFT_ARM }, { 0xf008f0b6, 0xf000f0b6, ITEM_DOLLS_RIGHT_LEG },
	{ 0xf009f0b6, 0xf000f0b6, ITEM_DOLLS_LEFT_LEG }, { 0xf002f0b5, 0xf000f0b5, ITEM_SHOVEL_WITH_BLOOD_CHARACTER }, { 0xf00af0b6, 0xf001f0b6, ITEM_ARMORIAL_MEDAL },
	{ 0xf003f0b5, 0xf001f0b5, ITEM_SCRAP_OF_BIBLE }, { 0xf00cf0b6, 0xf003f0b6, ITEM_HOLY_MOTHER_21_SACRAMENTS }, { 0xf004f0b5, 0xf005f0b5, ITEM_TRAILER_KEY },
	{ 0xf04af057, 0xf06df057, ITEM_CLUB }, { 0xf00df0b6, 0xf004f0b6, ITEM_BURNED_OUT_MEMO }, { 0xf000f16d, 0xf001f16d, ITEM_OLD_DOLL },
	{ 0xf002f16d, 0xf003f16d, ITEM_CASSETTE_TAPE }, { 0xf004f16d, 0xf005f16d, ITEM_MASTER_KEY_TO_APART }, { 0xf006f16d, 0xf007f16d, ITEM_KEY_OF_SUPERINTENDANT },
	{ 0xf008f16d, 0xf009f16d, ITEM_KEY_ROCKER106 }, { 0xf00af16d, 0xf00bf16d, ITEM_RED_PAPER_1 }, { 0xf00af16d, 0xf00bf16d, ITEM_RED_PAPER_2 },
	{ 0xf00af16d, 0xf00bf16d, ITEM_RED_PAPER_3 }, { 0xf00af16d, 0xf00bf16d, ITEM_RED_PAPER_4 }, { 0xf00af16d, 0xf00bf16d, ITEM_RED_PAPER_5 },
	{ 0xf00af16d, 0xf00bf16d, ITEM_RED_PAPER_6 }, { 0xf00cf16d, 0xf00df16d, ITEM_TORN_RED_PAPER_1 }, { 0xf00cf16d, 0xf00df16d, ITEM_TORN_RED_PAPER_2 },
	{ 0xf00cf16d, 0xf00df16d, ITEM_TORN_RED_PAPER_MISS }, { 0xf00ef16d, 0xf00ff16d, ITEM_SUPERINTENDANTS_DIARY }, { 0xf010f16d, 0xf011f16d, ITEM_DIARY_OF_NEIGHBOUR }, { 0xf010f16d, 0xf011f16d, ITEM_JOSEPHS_REPORT },
	{ 0xf042f057, 0xf069f057, ITEM_REVOLVER }, { 0xf010f003, 0xf011f003, ITEM_NAVEL_STRING }, { 0xf000f0e5, 0xf001f0e5, ITEM_PICK_OF_HOPE },
	{ 0xf002f0e5, 0xf003f0e5, ITEM_RED_BOOK }, { 0xf004f0e5, 0xf005f0e5, ITEM_PICTURE_BOOK }, { 0xf01af003, 0xf01bf003, ITEM_RED_DIARY_0802 },
	{ 0xf01af003, 0xf01bf003, ITEM_RED_DIARY_0803 }, { 0xf01af003, 0xf01bf003, ITEM_RED_DIARY_0804 }, { 0xf01af003, 0xf01bf003, ITEM_RED_DIARY_0805 },
	{ 0xf01af003, 0xf01bf003, ITEM_RED_DIARY_0728 }, { 0xf01af003, 0xf01bf003, ITEM_RED_DIARY_0729 }, { 0xf01af003, 0xf01bf003, ITEM_RED_DIARY_0807 },
	{ 0xf006f0e5, 0xf007f0e5, ITEM_UNIFORM }, { 0xf000f144, 0xf001f144, ITEM_KEY_OF_SICKROOM }, { 0xf01ef003, 0xf01ff003, ITEM_NURSE_MEMO },
	{ 0xf002f144, 0xf003f144, ITEM_HANDBAG }, { 0xf000f057, 0xf054f057, ITEM_RUSTY_HATCHET }, { 0xf000f11a, 0xf001f11a, ITEM_BILLIARD_BALL },
	{ 0xf002f11a, 0xf003f11a, ITEM_STUFFED_CAT }, { 0xf004f11a, 0xf005f11a, ITEM_VOLLEYBALL }, { 0xf006f11a, 0xf007f11a, ITEM_SMALL_CANDLE_PACKED },
	{ 0xf008f11a, 0xf009f11a, ITEM_SMALL_CANDLE }, { 0xf000f119, 0xf001f119, ITEM_ALBERT_SPORTS_KEY }, { 0xf00af11a, 0xf00bf11a, ITEM_MEMOIRS },
	{ 0xf01ef003, 0xf01ff003, ITEM_BARTENDERS_MEMO }, { 0xf01ef003, 0xf01ff003, ITEM_BARTENDERS_MEMO2 }, { 0xf002f119, 0xf003f119, ITEM_ALBERT_SPORTS_KEY },
	{ 0xf007f05a, 0xf002f05a, ITEM_SUBMACHINEGUN }, { 0xf002f19a, 0xf003f19a, ITEM_PASSWORD_MEMO }, { 0xf000f19a, 0xf001f19a, ITEM_REPORT_1F },
	{ 0xf000f19a, 0xf001f19a, ITEM_REPORT_2F }, { 0xf000f19a, 0xf001f19a, ITEM_PRISONERS_DIARY }, { 0xf020f003, 0xf021f003, ITEM_SENTINELS_DIARY },
	{ 0xf020f003, 0xf021f003, ITEM_EXPLORERS_MEMO }, { 0xf004f19a, 0xf005f19a, ITEM_PRISONERS_SHIRT }, { 0xf006f19a, 0xf007f19a, ITEM_BLACKJACK },
	{ 0xf002f057, 0xf055f057, ITEM_METAL_BAT }, { 0xf008f057, 0xf058f057, ITEM_CHAIN_SAW }, { 0xf008f19a, 0xf009f19a, ITEM_UNDERGROUND_KEY },
	{ 0xf00af19a, 0xf00bf19a, ITEM_MZ_UPPER_KEY }, { 0xf000f1d1, 0xf001f1d1, ITEM_SUPERINTENDANTS_DIARY_COUT },
	// custom items
	{ 0xF046F057, 0xF075F057, ITEM_GREEN_HYPER_SPRAY },
	{ 0xF073F057, 0xF074F057, ITEM_GOLD_PIPE },
	{ 0xF073F057, 0xF076F057, ITEM_SILVER_PIPE },
};


injector::hook_back<unsigned int(__cdecl*)(GameItem)> GameGetItemParamTexId;
unsigned int GameGetItemParamTexIdHook(GameItem item)
{

	if (settings.bInGameOptions)
	{
		if (miscOptionGetPtr.fun()->random_items == 0)
		{
			return GameGetItemParamTexId.fun(item);
		}
	}
	else if (settings.bRandomItems == false)
	{
		return GameGetItemParamTexId.fun(item);
	}

	if (ITEM_FIRST_AID_KIT < item && item < ITEM_KEY_OF_LIBERATION)
	{
		// check if the player has enabled extra content, if not only give vanilla items
		if ((settings.bInGameOptions == true && miscOptionGetPtr.fun()->extra_content == 1) || (settings.bInGameOptions == false && settings.bExtraContent == true))
		{
			for (int i = 0; i < item_param_fileid.size(); i++)
			{
				if (item_param_fileid[i].item == weaponSwapsWithExtra[item])
				{
					return item_param_fileid[i].tex_id;
				}
			}
		}
		else
		{
			return GameGetItemParamTexId.fun(weaponSwaps[item]);
		}
	}

	return GameGetItemParamTexId.fun(item);
}

injector::hook_back<unsigned int(__cdecl*)(GameItem)> GameGetItemParamModelId;
unsigned int GameGetItemParamModelIdHook(GameItem item)
{
	if (settings.bInGameOptions)
	{
		if (miscOptionGetPtr.fun()->random_items == 0)
		{
			return GameGetItemParamModelId.fun(item);
		}
	}
	else if (settings.bRandomItems == false)
	{
		return GameGetItemParamModelId.fun(item);
	}

	if (ITEM_FIRST_AID_KIT < item && item < ITEM_KEY_OF_LIBERATION)
	{
		// check if the player has enabled extra content, if not only give vanilla items
		if ((settings.bInGameOptions == true && miscOptionGetPtr.fun()->extra_content == 1) || (settings.bInGameOptions == false && settings.bExtraContent == true))
		{
			for (int i = 0; i < item_param_fileid.size(); i++)
			{
				if (item_param_fileid[i].item == weaponSwapsWithExtra[item])
				{
					return item_param_fileid[i].model_id;
				}
			}
		}
		else
		{
			return GameGetItemParamModelId.fun(weaponSwaps[item]);
		}
	}

	return GameGetItemParamModelId.fun(item);
}

/*
injector::hook_back<_ItemMsgCtrlDt* (__cdecl*)(GameItem)> GameGetItemMsgCtrlDt;
_ItemMsgCtrlDt* GameGetItemMsgCtrlDtHook(GameItem item)
{
	if (settings.bInGameOptions)
	{
		if (miscOptionGetPtr.fun()->random_items == 0)
		{
			return GameGetItemMsgCtrlDt.fun(item);
		}
	}
	else if (settings.bRandomItems == false)
	{
		return GameGetItemMsgCtrlDt.fun(item);
	}

	if (ITEM_FIRST_AID_KIT < item && item < ITEM_KEY_OF_LIBERATION)
	{
		// check if the player has enabled extra content, if not only give vanilla items
		if ((settings.bInGameOptions == true && miscOptionGetPtr.fun()->extra_content == 1) || (settings.bInGameOptions == false && settings.bExtraContent == true))
		{
			return GameGetItemMsgCtrlDt.fun(weaponSwapsWithExtra[item]);
		}
		else
		{
			return GameGetItemMsgCtrlDt.fun(weaponSwaps[item]);
		}
	}

	return GameGetItemMsgCtrlDt.fun(item);
}
*/

void InitializeGameGIParaFunctions()
{
	GameGetItemParamModelId.fun = injector::MakeCALL(0x004cf5c7, GameGetItemParamModelIdHook, true).get();

	GameGetItemParamTexId.fun = injector::MakeCALL(0x004cf5de, GameGetItemParamTexIdHook, true).get();
}