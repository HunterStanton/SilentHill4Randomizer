#pragma once

struct Door {
	float bmin[3];
	unsigned char door_no;
	unsigned char scene_no;
	short door_type;
	float bmax[3];
	int door_material;
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

extern DoorLinkTableEntry* rl_connection_data;
extern DoorLinkTableEntry* sb_connection_data;
extern std::vector<char> rl_possible_destinations;
void InitializeGameSceneLinkFunctions();
