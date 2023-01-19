#pragma once

struct Model {
    unsigned int id;
    unsigned int revision;
    unsigned int initial_matrices_offset;
    unsigned int n_skeletons;
    unsigned int skeleton_structure_offset;
    unsigned int n_skeleton_pairs;
    unsigned int skeleton_pairs_offset;
    unsigned int default_pcms_offset;
    unsigned int n_vu1_parts;
    unsigned int vu1_parts_offset;
    unsigned int n_vu0_parts;
    unsigned int vu0_parts_offset;
    unsigned int n_texture_blocks;
    unsigned int texture_blocks_offset;
    unsigned int n_text_poses;
    unsigned int text_poses_offset;
    unsigned int text_pos_params_offset;
    unsigned int n_cluster_nodes;
    unsigned int cluster_nodes_offset;
    unsigned int n_clusters;
    unsigned int clusters_offset;
    unsigned int n_func_data;
    unsigned int func_data_offset;
    unsigned int hit_offset;
    unsigned int box_offset;
    unsigned int flag;
    unsigned int relative_matrices_offset;
    unsigned int relative_transes_offset;
    unsigned int hits_offset;
    unsigned int reserved_1d;
    unsigned int tanmparams;
    unsigned int textureextras;
};