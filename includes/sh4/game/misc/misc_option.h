#pragma once

struct GameOptions
{
	int resolution[2];
	char head_motion;
	char hide_gauge;
	char hide_icon;
	char vibration;
	char sound;
	char bgm_vol;
	char se_vol;
	char keyconf;
	char brightness;
	char language;
	char subtitles;
	char blood_col;
	char noise_eff;
	char contrast;
	char cam_reverse;
	char move_parallel;
	char is_walk;
	char realtime_shadows;

	// this typically has 6 bytes of padding but we can use it to store our new settings
	// this will be committed to the players gamesave and doesn't cause issues when the randomizer isn't running
	// it is a win-win
	char random_enemies;
	char random_items;
	char random_models;
	char extra_content;
	char random_damage;
	char fog_approaches;
};

extern injector::hook_back<GameOptions* (__cdecl*)()> miscOptionGetPtr;

struct OptionMenuItem
{
	int change;			 // pointer to func ran when value changes
	int get_val;		 // pointer to func that gets value
	int buru_cnt;		 // ???
	int MesId_val;		 // pointer to message indices for the option values
	int MesId_val_num;	 // number of possible options
	int MesId_item;		 // pointer to message index for the option name
	int get_expl_mes_id; // pointer to func that returns the message index for the option's "explanation text"
};

void ApplyIngameOptionsPatches();
int change_random_enemies(GameOptions* opt, int num);
int change_random_items(GameOptions* opt, int num);
int change_random_models(GameOptions* opt, int num);
int change_random_damage(GameOptions* opt, int num);
int change_extra_content(GameOptions* opt, int num);
int change_fog_approaches(GameOptions* opt, int num);
int get_random_enemies();
int get_random_items();
int get_random_models();
int get_random_damage();
int get_extra_content();
int get_fog_approaches();
int get_random_enemies_expl();
int get_random_items_expl();
int get_random_models_expl();
int get_random_damage_expl();
int get_extra_content_expl();
int get_fog_approaches_expl();


// this is typically hardcoded in the exe
extern std::vector<OptionMenuItem> extraOptionMenuItems;

extern std::vector<int> optionMenuTitleMessages;

extern std::vector<int> optionItemCounts;

extern std::vector<int> optionItemPtrs;