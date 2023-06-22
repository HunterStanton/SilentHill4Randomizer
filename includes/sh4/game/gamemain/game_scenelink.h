#pragma once

// controls which sound effect is played when the door is entered
enum DoorMaterial : int
{
	DOOR_MAT_NONE,
	DOOR_MAT_STEEL,
	DOOR_MAT_WOOD,
	DOOR_MAT_ELEVATOR,
	DOOR_MAT_KOSHI, // machine translated as waist? not sure what this is in eng
	DOOR_MAT_LARGE,
	DOOR_MAT_TRAIN,
	DOOR_MAT_MAX
};

struct Door {
	float bmin[3];
	unsigned char door_no;
	unsigned char scene_no;
	short door_type;
	float bmax[3];
	DoorMaterial door_material;
	float start_position[3];
	float start_direction[3];
};

struct SceneData {
	int n_doors;
	Door doors[1];
};

struct DoorLinkData {
	unsigned char start_scene;
	unsigned char end_scene;
};

struct DoorLinkTableEntry {
	int n_scenes;
	int n_doorlinks;
	DoorLinkData* doorlinks_data_offset;
	void* doorlinks_call_functions;
	SceneData* scene_data_offsets[1];
};

enum RLPossibleDestinations : char
{
	BATHROOM = 2,
	BEDROOM = 3,
	UTILITY_ROOM = 4
};

extern DoorLinkTableEntry* rl_connection_data;
extern DoorLinkTableEntry* sb_connection_data;
extern std::vector<RLPossibleDestinations> rl_possible_destinations;
void InitializeGameSceneLinkFunctions();
