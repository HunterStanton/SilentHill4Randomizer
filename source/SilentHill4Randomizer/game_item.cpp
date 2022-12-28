#include "stdafx.h"
#include "Randomizer.h"
#include "sh4/game/gamemain/game_item.h"
#include "sh4/game/player/player_anime_proc.h"
#include "sh4/game/player/battle/player_weapon.h"
#include "sh4/game/misc/misc_itemicon.h"
#include "sh4/game/misc/misc_iexplanation.h"
#include "sh4/game/message/message_handle.h"
#include "sh4/game/misc/misc_option.h"
#include <plog/Log.h>


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

	injector::WriteMemory<int>(0x0050efc6, *(int*)&item_message_table, true);
	injector::WriteMemory<char>(0x0050efda, (char)item_message_table.size(), true);
	injector::WriteMemory<char>(0x0050efbf, 234, true);

	GameItemWeaponEquip.fun = injector::MakeCALL(0x00516b80, GameItemWeaponEquipHook, true).get();

	GameItemIsEileenWeapon.fun = injector::MakeCALL(0x00512236, GameItemIsEileenWeaponHook, true).get();
	GameItemIsEileenWeapon.fun = injector::MakeCALL(0x00514d6f, GameItemIsEileenWeaponHook, true).get();

	GameItemIsWeapon.fun = injector::MakeCALL(0x004f5e62, GameItemIsWeaponHook, true).get();
	GameItemIsWeapon.fun = injector::MakeCALL(0x00514d07, GameItemIsWeaponHook, true).get();
	GameItemIsWeapon.fun = injector::MakeCALL(0x00516b37, GameItemIsWeaponHook, true).get();
	GameItemIsWeapon.fun = injector::MakeCALL(0x00516b69, GameItemIsWeaponHook, true).get();

	GameItemUseItem.fun = injector::MakeCALL(0x00530214, GameItemUseItemHook, true).get();

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

	injector::WriteMemory<int>(0x00544e3f + 2, *(int*)&wp_table + 12, true);
	injector::WriteMemory<int>(0x00544e4b + 2, *(int*)&wp_table + 4, true);
	injector::WriteMemory<int>(0x00544e6b + 2, *(int*)&wp_table + 16, true);
	injector::WriteMemory<int>(0x00544e94 + 2, *(int*)&wp_table + 12, true);
	injector::WriteMemory<int>(0x00544ea4 + 2, *(int*)&wp_table + 8, true);
	injector::WriteMemory<int>(0x00544ec0 + 2, *(int*)&wp_table + 20, true);

	injector::WriteMemory<int>(0x00544d1f + 3, *(int*)&wp_param, true);
	injector::WriteMemory<int>(0x00544d5e + 3, *(int*)&wp_param, true);
	injector::WriteMemory<int>(0x00544ca0 + 2, *(int*)&wp_param + 4, true);
	injector::WriteMemory<int>(0x00544ca8 + 2, *(int*)&wp_param + 8, true);
	injector::WriteMemory<int>(0x00544cb1 + 2, *(int*)&wp_param + 12, true);
	injector::WriteMemory<int>(0x00544cba + 2, *(int*)&wp_param + 16, true);
	injector::WriteMemory<int>(0x00544de4 + 3, *(int*)&wp_param + 20, true);

	injector::WriteMemory<int>(0x00543cad, *(int*)&attack_tbl, true);
	injector::WriteMemory<int>(0x00544dbc, *(int*)&attack_tbl, true);
	injector::WriteMemory<int>(0x00543ca4, *(int*)&attack_tbl + 4, true);
}

injector::hook_back<GameItemAttribute(__cdecl*)(GameItem)> GameItemGetAttr;
GameItemAttribute __cdecl GameItemGetAttrHook(GameItem item)
{
	if (item == ITEM_CUSTOM_WEAPON)
	{
		return GameItemAttribute::ITEM_ATTR_WEAPON;
	}

	return GameItemGetAttr.fun(item);
}

injector::hook_back<int(__cdecl*)(GameItem)> GameItemIsEileenWeapon;
int __cdecl GameItemIsEileenWeaponHook(GameItem item)
{
	if (item == ITEM_CUSTOM_WEAPON)
	{
		return 0;
	}
	return GameItemIsEileenWeapon.fun(item);
}

injector::hook_back<int(__cdecl*)(GameItem)> GameItemIsWeapon;
int __cdecl GameItemIsWeaponHook(GameItem item)
{
	if (item == ITEM_CUSTOM_WEAPON)
	{
		return 1;
	}
	return GameItemIsWeapon.fun(item);
}

injector::hook_back<int(__cdecl*)(int)> GameItemWeaponEquip;
int __cdecl GameItemWeaponEquipHook(int num)
{
	// read the player's current inventory items
	GameItemData itemData = injector::ReadMemory<GameItemData>(0x013d7b60, true);

	auto kind = itemData.possession[num].kind;
	if (kind == ITEM_CUSTOM_WEAPON)
	{
		MessageExplanationPut.fun(0x0, 0xc5);
		return 1;
	}

	if (0xF < kind && kind < 0x36)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

injector::hook_back<GameItemResult(__cdecl*)(int)> GameItemUseItem;
GameItemResult __cdecl GameItemUseItemHook(int num)
{
	return GameItemUseItem.fun(num);
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
		newWeapon = ITEM_HANDGUN + (std::rand() % (ITEM_CHAIN_SAW - ITEM_HANDGUN + 1));
		PLOG(plog::info) << "Adding weapon " << newWeapon << " to inventory, original weapon was " << item;
		return GameItemGet.fun(static_cast<GameItem>(newWeapon));
	}

	// original item is a consumable of some kind
	if (ITEM_EMPTY < item && item < ITEM_HANDGUN)
	{
		newWeapon = ITEM_SMALL_BULLET + (std::rand() % (ITEM_FIRST_AID_KIT - ITEM_SMALL_BULLET + 1));

		// prevent giving the player unused/cut items
		if (newWeapon == ITEM_RED_CHRISM)
			newWeapon = ITEM_FINISHER;
		if (newWeapon == ITEM_LOADS_PRAYER)
			newWeapon = ITEM_SAINT_MEDALLION;

		PLOG(plog::info) << "Adding consumable item " << newWeapon << " to inventory, original consumable item was " << item;
		return GameItemGet.fun(static_cast<GameItem>(newWeapon));
	}

	return GameItemGet.fun(item);
}