#include "stdafx.h"
#include "Randomizer.h"
#include "sh4/game/gamemain/game_item.h"
#include "sh4/game/player/player_anime_proc.h"
#include "sh4/game/player/battle/player_weapon.h"
#include "sh4/game/misc/misc_itemicon.h"
#include "sh4/game/misc/misc_iexplanation.h"
#include "sh4/sys/apps/sf_obj.h"
#include "sh4/game/eileen/eileen.h"
#include "sh4/game/gamemain/stage_info.h"
#include "sh4/game/message/message_handle.h"
#include "sh4/game/misc/misc_option.h"
#include <plog/Log.h>


// all the weapons that can appear in the weapon loot pool
std::vector<GameItem> possibleWeapons = { ITEM_HANDGUN, ITEM_REVOLVER, ITEM_IRON_PIPE,
ITEM_CUTTER_KNIFE, ITEM_METAL_BAT, ITEM_DRIVER, ITEM_SPOON, ITEM_MID_MASHY, ITEM_MASHY_IRON,
ITEM_MASHY, ITEM_SPADE_MASHY, ITEM_MASHY_NIBLICK, ITEM_PITCHER, ITEM_NIBLICK, ITEM_PITCHING_WEDGE,
ITEM_SAND_WEDGE, ITEM_PUTTER, ITEM_WINE_BOTTLE, ITEM_WINE_BOTTLE_BROKEN, ITEM_SCOOP, ITEM_RUSTY_HATCHET,
ITEM_PICK_OF_DESPAIR, ITEM_STUN_GUN, ITEM_SPRAY, ITEM_CHAIN_SAW, ITEM_CLUB };

// all the weapons that can appear in the weapon loot pool with extra content enabled
std::vector<GameItem> possibleWeaponsWithExtra = { ITEM_HANDGUN, ITEM_REVOLVER, ITEM_IRON_PIPE,
ITEM_CUTTER_KNIFE, ITEM_METAL_BAT, ITEM_DRIVER, ITEM_SPOON, ITEM_MID_MASHY, ITEM_MASHY_IRON,
ITEM_MASHY, ITEM_SPADE_MASHY, ITEM_MASHY_NIBLICK, ITEM_PITCHER, ITEM_NIBLICK, ITEM_PITCHING_WEDGE,
ITEM_SAND_WEDGE, ITEM_PUTTER, ITEM_WINE_BOTTLE, ITEM_WINE_BOTTLE_BROKEN, ITEM_SCOOP, ITEM_RUSTY_HATCHET,
ITEM_PICK_OF_DESPAIR, ITEM_STUN_GUN, ITEM_SPRAY, ITEM_CHAIN_SAW, ITEM_GREEN_HYPER_SPRAY, ITEM_GOLD_PIPE, ITEM_SILVER_PIPE, ITEM_CLUB };

// the weapon spawn + the weapon that will actually be given on pickup
std::unordered_map<GameItem, GameItem> weaponSwaps = { { ITEM_HANDGUN, ITEM_HANDGUN },
	{ ITEM_REVOLVER, ITEM_REVOLVER }, { ITEM_IRON_PIPE, ITEM_IRON_PIPE },
	{ ITEM_CUTTER_KNIFE, ITEM_CUTTER_KNIFE }, { ITEM_METAL_BAT, ITEM_METAL_BAT },
	{ ITEM_DRIVER, ITEM_DRIVER },
	{ ITEM_SPOON, ITEM_SPOON },
	{ ITEM_MID_MASHY, ITEM_MID_MASHY },
	{ ITEM_MASHY_IRON, ITEM_MASHY_IRON },
	{ ITEM_MASHY, ITEM_MASHY },
	{ ITEM_SPADE_MASHY, ITEM_SPADE_MASHY },
	{ ITEM_MASHY_NIBLICK, ITEM_MASHY_NIBLICK },
	{ ITEM_PITCHER, ITEM_PITCHER },
	{ ITEM_NIBLICK, ITEM_NIBLICK },
	{ ITEM_PITCHING_WEDGE, ITEM_PITCHING_WEDGE },
	{ ITEM_SAND_WEDGE, ITEM_SAND_WEDGE },
	{ ITEM_PUTTER, ITEM_PUTTER },
	{ ITEM_WINE_BOTTLE, ITEM_WINE_BOTTLE },
	{ ITEM_SCOOP, ITEM_SCOOP }, { ITEM_RUSTY_HATCHET, ITEM_RUSTY_HATCHET },
	{ ITEM_PICK_OF_DESPAIR, ITEM_PICK_OF_DESPAIR }, { ITEM_STUN_GUN, ITEM_STUN_GUN },
	{ ITEM_SPRAY, ITEM_SPRAY }, { ITEM_CHAIN_SAW, ITEM_CHAIN_SAW } };

// the weapon spawn + the weapon that will actually be given on pickup if extra content is enabled
std::unordered_map<GameItem, GameItem> weaponSwapsWithExtra = { { ITEM_HANDGUN, ITEM_HANDGUN },
	{ ITEM_REVOLVER, ITEM_REVOLVER }, { ITEM_IRON_PIPE, ITEM_IRON_PIPE },
	{ ITEM_CUTTER_KNIFE, ITEM_CUTTER_KNIFE }, { ITEM_METAL_BAT, ITEM_METAL_BAT },
	{ ITEM_DRIVER, ITEM_DRIVER },
	{ ITEM_SPOON, ITEM_SPOON },
	{ ITEM_MID_MASHY, ITEM_MID_MASHY },
	{ ITEM_MASHY_IRON, ITEM_MASHY_IRON },
	{ ITEM_MASHY, ITEM_MASHY },
	{ ITEM_SPADE_MASHY, ITEM_SPADE_MASHY },
	{ ITEM_MASHY_NIBLICK, ITEM_MASHY_NIBLICK },
	{ ITEM_PITCHER, ITEM_PITCHER },
	{ ITEM_NIBLICK, ITEM_NIBLICK },
	{ ITEM_PITCHING_WEDGE, ITEM_PITCHING_WEDGE },
	{ ITEM_SAND_WEDGE, ITEM_SAND_WEDGE },
	{ ITEM_PUTTER, ITEM_PUTTER },
	{ ITEM_WINE_BOTTLE, ITEM_WINE_BOTTLE },
	{ ITEM_SCOOP, ITEM_SCOOP }, { ITEM_RUSTY_HATCHET, ITEM_RUSTY_HATCHET },
	{ ITEM_PICK_OF_DESPAIR, ITEM_PICK_OF_DESPAIR }, { ITEM_STUN_GUN, ITEM_STUN_GUN },
	{ ITEM_SPRAY, ITEM_SPRAY }, { ITEM_CHAIN_SAW, ITEM_CHAIN_SAW } };

void InstallItemHooks()
{

	GameItemGet.fun = injector::MakeCALL(0x00516d2f, GameItemGetHook, true).get();

	GameItemGetAttr.fun = injector::MakeCALL(0x0051007a, GameItemGetAttrHook, true).get();
	GameItemGetAttr.fun = injector::MakeCALL(0x00510090, GameItemGetAttrHook, true).get();
	GameItemGetAttr.fun = injector::MakeCALL(0x005107f4, GameItemGetAttrHook, true).get();
	GameItemGetAttr.fun = injector::MakeCALL(0x00511b8b, GameItemGetAttrHook, true).get();
	GameItemGetAttr.fun = injector::MakeCALL(0x00511bf1, GameItemGetAttrHook, true).get();
	GameItemGetAttr.fun = injector::MakeCALL(0x00511c53, GameItemGetAttrHook, true).get();
	GameItemGetAttr.fun = injector::MakeCALL(0x00511cb9, GameItemGetAttrHook, true).get();
	GameItemGetAttr.fun = injector::MakeCALL(0x005121e3, GameItemGetAttrHook, true).get();
	GameItemGetAttr.fun = injector::MakeCALL(0x0051262f, GameItemGetAttrHook, true).get();
	GameItemGetAttr.fun = injector::MakeCALL(0x00512dd1, GameItemGetAttrHook, true).get();
	GameItemGetAttr.fun = injector::MakeCALL(0x00513315, GameItemGetAttrHook, true).get();
	GameItemGetAttr.fun = injector::MakeCALL(0x00513334, GameItemGetAttrHook, true).get();
	GameItemGetAttr.fun = injector::MakeCALL(0x005173f6, GameItemGetAttrHook, true).get();
	GameItemGetAttr.fun = injector::MakeCALL(0x00517507, GameItemGetAttrHook, true).get();
	GameItemGetAttr.fun = injector::MakeCALL(0x00530249, GameItemGetAttrHook, true).get();
	GameItemGetAttr.fun = injector::MakeCALL(0x00530295, GameItemGetAttrHook, true).get();

	// use DLL-supplied item icon tables instead of the hardcoded ones
	injector::WriteMemory<int>(0x00513889, *(int*)&small_icon_tbl, true);
	injector::WriteMemory<int>(0x00513948, *(int*)&large_icon_tbl, true);
	injector::WriteMemory<char>(0x0051389d, (char)small_icon_tbl.size(), true);
	injector::WriteMemory<char>(0x0051395d, (char)large_icon_tbl.size(), true);
	/*injector::WriteMemory<int>(0x00513889, *(int*)&small_icon_tbl, true);
	injector::WriteMemory<int>(0x00513948, *(int*)&large_icon_tbl, true);
	injector::WriteMemory<char>(0x0051389d, (char)small_icon_tbl.size(), true);
	injector::WriteMemory<char>(0x0051395d, (char)large_icon_tbl.size(), true);*/

	injector::MakeCALL(0x00514838, injector::auto_pointer(0x00513940), true);

	injector::WriteMemory<int>(0x0050efc6, *(int*)&item_message_table, true);
	injector::WriteMemory<char>(0x0050efda, (char)item_message_table.size(), true);
	injector::WriteMemory<char>(0x0050efbf, ITEM_KIND_CUSTOM_MAX, true);

	GameItemWeaponEquip.fun = injector::MakeCALL(0x00516b80, GameItemWeaponEquipHook, true).get();

	GameItemIsEileenWeapon.fun = injector::MakeCALL(0x00512236, GameItemIsEileenWeaponHook, true).get();
	GameItemIsEileenWeapon.fun = injector::MakeCALL(0x00514d6f, GameItemIsEileenWeaponHook, true).get();

	GameItemIsWeapon.fun = injector::MakeCALL(0x004f5e62, GameItemIsWeaponHook, true).get();
	GameItemIsWeapon.fun = injector::MakeCALL(0x00514d07, GameItemIsWeaponHook, true).get();
	GameItemIsWeapon.fun = injector::MakeCALL(0x00516b37, GameItemIsWeaponHook, true).get();
	GameItemIsWeapon.fun = injector::MakeCALL(0x00516b69, GameItemIsWeaponHook, true).get();

	GameItemUseItem.fun = injector::MakeCALL(0x00530214, GameItemUseItemHook, true).get();

	// replace hardcoded combat animation tables with our own
	injector::WriteMemory<int>(0x0052e359, *(int*)&motion_battle, true);
	injector::WriteMemory<int>(0x0052e39f, *(int*)&motion_battle, true);
	injector::WriteMemory<int>(0x0052e3ed, *(int*)&motion_battle, true);
	injector::WriteMemory<int>(0x0052e490, *(int*)&motion_battle, true);
	injector::WriteMemory<int>(0x0052e5af, *(int*)&motion_battle, true);
	injector::WriteMemory<int>(0x0052e69c, *(int*)&motion_battle, true);
	injector::WriteMemory<int>(0x0052e6d9, *(int*)&motion_battle, true);
	injector::WriteMemory<int>(0x0052e829, *(int*)&motion_battle, true);
	injector::WriteMemory<int>(0x0052e854, *(int*)&motion_battle, true);
	injector::WriteMemory<int>(0x0052e8f7, *(int*)&motion_battle, true);
	injector::WriteMemory<int>(0x0052e91a, *(int*)&motion_battle, true);
	injector::WriteMemory<int>(0x0052e9a6, *(int*)&motion_battle, true);

	// replace hardcoded weapon time tables with our own
	injector::WriteMemory<int>(0x005439ef + 3, *(int*)&wp_time_table, true);
	injector::WriteMemory<int>(0x00543a1f + 3, *(int*)&wp_time_table, true);
	injector::WriteMemory<int>(0x00543a4f + 3, *(int*)&wp_time_table, true);
	injector::WriteMemory<int>(0x00543ac0 + 3, *(int*)&wp_time_table, true);
	injector::WriteMemory<int>(0x00543b3f + 3, *(int*)&wp_time_table, true);
	injector::WriteMemory<int>(0x00543bef + 3, *(int*)&wp_time_table, true);
	injector::WriteMemory<int>(0x005444b8 + 3, *(int*)&wp_time_table, true);
	injector::WriteMemory<int>(0x005444f1 + 3, *(int*)&wp_time_table, true);
	injector::WriteMemory<int>(0x00544519 + 3, *(int*)&wp_time_table, true);
	injector::WriteMemory<int>(0x005452bd + 3, *(int*)&wp_time_table, true);
	injector::WriteMemory<int>(0x005452e2 + 3, *(int*)&wp_time_table, true);
	injector::WriteMemory<int>(0x00545323 + 3, *(int*)&wp_time_table, true);
	injector::WriteMemory<int>(0x0054534f + 3, *(int*)&wp_time_table, true);
	injector::WriteMemory<int>(0x00545362 + 3, *(int*)&wp_time_table, true);
	injector::WriteMemory<int>(0x00545387 + 3, *(int*)&wp_time_table, true);
	injector::WriteMemory<int>(0x005453c8 + 3, *(int*)&wp_time_table, true);
	injector::WriteMemory<int>(0x005453ed + 3, *(int*)&wp_time_table, true);
	injector::WriteMemory<int>(0x0054542f + 3, *(int*)&wp_time_table, true);
	injector::WriteMemory<int>(0x00545468 + 3, *(int*)&wp_time_table, true);
	injector::WriteMemory<int>(0x00545491 + 3, *(int*)&wp_time_table, true);

	// replace hardcoded weapon tables with our own
	injector::WriteMemory<int>(0x00544e3f + 2, *(int*)&wp_table + 12, true);
	injector::WriteMemory<int>(0x00544e4b + 2, *(int*)&wp_table + 4, true);
	injector::WriteMemory<int>(0x00544e6b + 2, *(int*)&wp_table + 16, true);
	injector::WriteMemory<int>(0x00544e94 + 2, *(int*)&wp_table + 12, true);
	injector::WriteMemory<int>(0x00544ea4 + 2, *(int*)&wp_table + 8, true);
	injector::WriteMemory<int>(0x00544ec0 + 2, *(int*)&wp_table + 20, true);

	// replace hardcoded weapon parameters with our own
	injector::WriteMemory<int>(0x00544d1f + 3, *(int*)&wp_param, true);
	injector::WriteMemory<int>(0x00544d5e + 3, *(int*)&wp_param, true);
	injector::WriteMemory<int>(0x00544ca0 + 2, *(int*)&wp_param + 4, true);
	injector::WriteMemory<int>(0x00544ca8 + 2, *(int*)&wp_param + 8, true);
	injector::WriteMemory<int>(0x00544cb1 + 2, *(int*)&wp_param + 12, true);
	injector::WriteMemory<int>(0x00544cba + 2, *(int*)&wp_param + 16, true);
	injector::WriteMemory<int>(0x00544de4 + 3, *(int*)&wp_param + 20, true);

	// replace hardcoded attack tables with our own
	injector::WriteMemory<int>(0x00543cad, *(int*)&attack_tbl, true);
	injector::WriteMemory<int>(0x00544dbc, *(int*)&attack_tbl, true);
	injector::WriteMemory<int>(0x00543ca4, *(int*)&attack_tbl + 4, true);

	// replace hardcoded sidestep animation tables with our own
	injector::WriteMemory<int>(0x00543c60, *(int*)&sidestep_anim, true);
	injector::WriteMemory<int>(0x00543c68, *(int*)&sidestep_anim, true);
}

injector::hook_back<GameItemAttribute(__cdecl*)(GameItem)> GameItemGetAttr;
GameItemAttribute __cdecl GameItemGetAttrHook(GameItem item)
{
	switch (item) {
	case ITEM_GOLD_PIPE:
	case ITEM_GREEN_HYPER_SPRAY:
	case ITEM_SILVER_PIPE:
		return GameItemAttribute::ITEM_ATTR_WEAPON;
	case ITEM_RED_CHRISM:
	case ITEM_LOADS_PRAYER:
		return GameItemAttribute::ITEM_ATTR_RECOVERY;
	default:
		return GameItemGetAttr.fun(item);
	}
}

injector::hook_back<int(__cdecl*)(GameItem)> GameItemIsEileenWeapon;
int __cdecl GameItemIsEileenWeaponHook(GameItem item)
{
	switch (item) {
	case ITEM_GOLD_PIPE:
	case ITEM_GREEN_HYPER_SPRAY:
	case ITEM_SILVER_PIPE:
		return 0;
	default:
		return GameItemIsEileenWeapon.fun(item);
	}
}

injector::hook_back<int(__cdecl*)(GameItem)> GameItemIsWeapon;
int __cdecl GameItemIsWeaponHook(GameItem item)
{
	switch (item) {
	case ITEM_GOLD_PIPE:
	case ITEM_GREEN_HYPER_SPRAY:
	case ITEM_SILVER_PIPE:
		return 1;
	default:
		return GameItemIsWeapon.fun(item);
	}
}

injector::hook_back<int(__cdecl*)(int)> GameItemWeaponEquip;
int __cdecl GameItemWeaponEquipHook(int num)
{
	// read the player's current inventory items
	GameItemData itemData = injector::ReadMemory<GameItemData>(0x013d7b60, true);

	auto kind = itemData.possession[num].kind;
	switch (kind) {
	case ITEM_GOLD_PIPE:
	case ITEM_GREEN_HYPER_SPRAY:
	case ITEM_SILVER_PIPE:
		return 1;
	default:
		if (0xF < kind && kind < 0x36)
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
}

injector::hook_back<GameItemResult(__cdecl*)(int)> GameItemUseItem;
GameItemResult __cdecl GameItemUseItemHook(int num)
{
	sfObj* eilObj = injector::ReadMemory<sfObj*>(0x00fce6b4, true);
	EileenWork* eilWork = 0;

	GameItemData itemData = injector::ReadMemory<GameItemData>(0x013d7b60, true);
	GameItem kind = itemData.possession[num].kind;

	switch (kind)
	{
	case ITEM_LOADS_PRAYER:
		if (eilObj != 0)
		{
			eilWork = (EileenWork*)eilObj->work_pt0;
		}
		else {
			return ITEM_RESULT_NONE;
		}
		if (eilWork->curse_value < 0.1f)
		{
			eilWork->curse_value = 0.0f;
			eilWork->curse_value_base = 0.0f;
			eilWork->curse_value_current = 0.0f;
		}
		eilWork->curse_value = (eilWork->curse_value - 0.1f);
		eilWork->curse_value_base = (eilWork->curse_value - 0.1f);
		eilWork->curse_value_current = (eilWork->curse_value - 0.1f);
		return ITEM_RESULT_USE;
	case ITEM_RED_CHRISM:
		if (eilObj != 0)
		{
			eilWork = (EileenWork*)eilObj->work_pt0;
		}
		else {
			return ITEM_RESULT_NONE;
		}
		if (eilWork->curse_value < 0.25f)
		{
			eilWork->curse_value = 0.0f;
			eilWork->curse_value_base = 0.0f;
			eilWork->curse_value_current = 0.0f;
		}
		eilWork->curse_value = (eilWork->curse_value - 0.25f);
		eilWork->curse_value_base = (eilWork->curse_value - 0.25f);
		eilWork->curse_value_current = (eilWork->curse_value - 0.25f);
		return ITEM_RESULT_USE;
	default:
		return GameItemUseItem.fun(num);
	}
}

injector::hook_back<bool(__cdecl*)(GameItem)> GameItemGet;
bool __cdecl GameItemGetHook(GameItem item)
{

	if (settings.bInGameOptions)
	{
		if (miscOptionGetPtr.fun()->random_items == 0)
		{
			return GameItemGet.fun(item);
		}
	}
	else if (settings.bRandomItems == false)
	{
		return GameItemGet.fun(item);
	}

	// don't change the torch pickup since bad RNG could make it impossible to progress otherwise
	if (item == ITEM_CLUB)
	{
		return GameItemGet.fun(item);
	}

	int newWeapon = 0;

	// original item is a weapon
	if (ITEM_FIRST_AID_KIT < item && item < ITEM_KEY_OF_LIBERATION)
	{
		// check if the player has enabled extra content, if not only give vanilla items
		if ((settings.bInGameOptions == true && miscOptionGetPtr.fun()->extra_content == 1) || (settings.bInGameOptions == false && settings.bExtraContent == true))
		{
			newWeapon = weaponSwapsWithExtra[item];
		}
		else
		{
			newWeapon = weaponSwaps[item];
		}


		PLOG(plog::info) << "Adding weapon " << newWeapon << " to inventory, original weapon was " << item;
		return GameItemGet.fun(static_cast<GameItem>(newWeapon));
	}

	// original item is a consumable of some kind
	if (ITEM_EMPTY < item && item < ITEM_HANDGUN)
	{
		newWeapon = consumableGenerator(mainRng);

		// don't give player new Eileen consumable items unless the game is in the second half + they have enabled extra content
		if ((settings.bInGameOptions == true && miscOptionGetPtr.fun()->extra_content == 0) || (settings.bInGameOptions == false && settings.bExtraContent == false))
		{
			if (newWeapon == ITEM_RED_CHRISM)
				newWeapon = ITEM_FINISHER;
			if (newWeapon == ITEM_LOADS_PRAYER)
				newWeapon = ITEM_SAINT_MEDALLION;
		}
		else
		{
			if (StageInfoIsLatterHalf.fun() == 0)
			{
				if (newWeapon == ITEM_RED_CHRISM)
					newWeapon = ITEM_FINISHER;
				if (newWeapon == ITEM_LOADS_PRAYER)
					newWeapon = ITEM_SAINT_MEDALLION;
			}
		}


		PLOG(plog::info) << "Adding consumable item " << newWeapon << " to inventory, original consumable item was " << item;
		return GameItemGet.fun(static_cast<GameItem>(newWeapon));
	}

	return GameItemGet.fun(item);
}