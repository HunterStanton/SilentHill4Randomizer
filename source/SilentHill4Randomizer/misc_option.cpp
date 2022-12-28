#include "stdafx.h"
#include "sh4/game/misc/misc_option.h"
#include "sh4/game/message/message_load.h"
#include <plog/Log.h>


std::vector<OptionMenuItem> extraOptionMenuItems = {
	// vanilla settings
	{
		0x524a20,
		0x413ca0,
		0,
		0x654c2c,
		7,
		42,
		0x523150},
	{0x524af0,
	 0x413cb0,
	 0,
	 0x654c18,
	 2,
	 43,
	 0x525480},
	{0x524e40,
	 0x413cd0,
	 0,
	 0x654c18,
	 2,
	 47,
	 0x5254a0},
	{0x524da0,
	 0x413cc0,
	 0,
	 0x654c48,
	 3,
	 44,
	 0x00525490},
	{0x524760,
	 0x413c40,
	 0,
	 0x654c18,
	 2,
	 33,
	 0x00525430},
	 {0x524830,
	 0x413c50,
	 0,
	 0x654c18,
	 2,
	 34,
	 0x00525440},
	{0x524f20,
	 0x413cf0,
	 0,
	 0x654c18,
	 2,
	 120,
	 0x525470},

	 // new randomizer settings
	 {
		 (int)&change_random_enemies,
		 (int)&get_random_enemies,
		 0,
		 0x654c18,
		 2,
		 2000,
		 (int)&get_random_enemies_expl},

	 {(int)&change_random_items,
	  (int)&get_random_items,
	  0,
	  0x654c18,
	  2,
	  2001,
	  (int)&get_random_items_expl},

	 {(int)&change_random_models,
	  (int)&get_random_models,
	  0,
	  0x654c18,
	  2,
	  2002,
	  (int)&get_random_models_expl},

	  {(int)&change_random_damage,
	  (int)&get_random_damage,
	  0,
	  0x654c18,
	  2,
	  2004,
	  (int)&get_random_damage_expl},

	  {(int)&change_extra_content,
	  (int)&get_extra_content,
	  0,
	  0x654c18,
	  2,
	  2003,
	  (int)&get_extra_content_expl},

	  {(int)&change_fog_approaches,
	  (int)&get_fog_approaches,
	  0,
	  0x654c18,
	  2,
	  2005,
	  (int)&get_fog_approaches_expl},

	  // exit button
	  {
		  0x524f90,
		  0x51eb10,
		  0,
		  0x654c54,
		  1,
		  48,
		  0x401010} };

std::vector<int> optionMenuTitleMessages = {
	0x6E,
	0x6F,
	0x70
};

std::vector<int> optionItemCounts = {
	7,
	7,
	(int)extraOptionMenuItems.size()
};

std::vector<int> optionItemPtrs = {
	0x00654cc0,
	0x00654d88,
	*(int*)&extraOptionMenuItems
};

void ApplyIngameOptionsPatches()
{
	// to anyone reading this code and wondering what is happening with these patches:
	// SH4 hardcodes its menus. These pointers point to structures containing information about the individual menu items such as display name, description, etc.
	// By overwriting the original pointer with a pointer to our custom extraOptionMenuItems structure we can add new items to existing menus
	injector::WriteMemory<int>(0x00523dae, *(int*)&optionItemPtrs, true);
	injector::WriteMemory<int>(0x005264a1, *(int*)&optionItemPtrs, true);
	injector::WriteMemory<int>(0x0052623e, *(int*)&optionItemPtrs, true);
	injector::WriteMemory<int>(0x00526322, *(int*)&optionItemPtrs, true);

	// Adjust the menu item counts so our new items will appear
	injector::WriteMemory<int>(0x00523da0, *(int*)&optionMenuTitleMessages, true);
	injector::WriteMemory<int>(0x00523d91, *(int*)&optionItemCounts, true);
	injector::WriteMemory<int>(0x00523d33, *(int*)&optionItemCounts, true);

	// adjust spacing on options menu so more items can fit
	// in the future the move would be to create an "Option 4 (Randomizer)" menu to fit all the randomizer stuff
	// slotting it into extra feels weird
	injector::WriteMemory<int>(0x00523db8, 0x20, true);
	injector::WriteMemory<char>(0x00523e0b, 0x15, true);

	// move menu title text to Y pos 0
	injector::WriteMemory<char>(0x005259bb, 0x0, true);
	injector::WriteMemory<char>(0x005259d0, 0x0, true);

	// hide arrows
	injector::MakeNOP(0x0052671f, 5, true);
	injector::MakeNOP(0x005267e1, 5, true);



	miscOptionGetPtr.fun = injector::auto_pointer(0x005230c0);

	// hook to display custom text without needing to provide new message bins
	MessageAddress.fun = injector::MakeCALL(0x0050b594, MessageAddressHook, true).get();
	MessageAddress.fun = injector::MakeCALL(0x0050c30a, MessageAddressHook, true).get();
	MessageAddress.fun = injector::MakeCALL(0x0050b1cb, MessageAddressHook, true).get();
	MessageAddress.fun = injector::MakeCALL(0x0050b2ae, MessageAddressHook, true).get();
	MessageAddress.fun = injector::MakeCALL(0x0050b5ce, MessageAddressHook, true).get();
	MessageAddress.fun = injector::MakeCALL(0x0050c2aa, MessageAddressHook, true).get();
	MessageAddress.fun = injector::MakeCALL(0x0050c34a, MessageAddressHook, true).get();
	MessageAddress.fun = injector::MakeCALL(0x005573ed, MessageAddressHook, true).get();
}

injector::hook_back<GameOptions* (__cdecl*)()> miscOptionGetPtr;

// game calls the change functions with two params, a ptr to the options struct and the new option index
// naming convention following what the game itself uses
int change_random_enemies(GameOptions* opt, int num)
{
	Sleep(100);
	opt->random_enemies = ((opt->random_enemies + -1 + num) % num);
	return 0;
}

int get_random_enemies()
{
	return miscOptionGetPtr.fun()->random_enemies;
}

int get_random_enemies_expl()
{
	return 2100;
}

int change_random_items(GameOptions* opt, int num)
{
	Sleep(100);
	opt->random_items = ((opt->random_items + -1 + num) % num);
	return 0;
}

int get_random_items()
{
	return miscOptionGetPtr.fun()->random_items;
}

int get_random_items_expl()
{
	return 2101;
}

int change_random_models(GameOptions* opt, int num)
{
	Sleep(100);
	opt->random_models = ((opt->random_models + -1 + num) % num);
	return 0;
}

int get_random_models()
{
	return miscOptionGetPtr.fun()->random_models;
}

int get_random_models_expl()
{
	return 2102;
}

int change_random_damage(GameOptions* opt, int num)
{
	Sleep(100);
	opt->random_damage = ((opt->random_damage + -1 + num) % num);
	return 0;
}

int get_random_damage()
{
	return miscOptionGetPtr.fun()->random_damage;
}

int get_random_damage_expl()
{
	return 2104;
}

int change_extra_content(GameOptions* opt, int num)
{
	Sleep(100);
	opt->extra_content = ((opt->extra_content + -1 + num) % num);
	return 0;
}

int get_extra_content()
{
	return miscOptionGetPtr.fun()->extra_content;
}

int get_extra_content_expl()
{
	return 2103;
}

int change_fog_approaches(GameOptions* opt, int num)
{
	Sleep(100);
	opt->fog_approaches = ((opt->fog_approaches + -1 + num) % num);
	return 0;
}

int get_fog_approaches()
{
	return miscOptionGetPtr.fun()->fog_approaches;
}

int get_fog_approaches_expl()
{
	return 2105;
}