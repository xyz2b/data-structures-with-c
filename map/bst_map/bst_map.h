//
// Created by 焦宏宇 on 2020/2/15.
//

#ifndef DATA_STRUCTURES_BST_MAP_H
#define DATA_STRUCTURES_BST_MAP_H
#include <stdbool.h>
#include "../../set/bst_set/bst_set.h"

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define OVERFLOW -1
typedef int Status;



typedef struct bst_map_node_s
{
    void *value;
    void *key;
    struct bst_map_node_s *left, *right; /*指针域*/
} bst_map_node_t;

typedef struct bst_map_s
{
    int key_data_size;
    int value_data_size;
    int size; /*树的大小*/
    bst_map_node_t *root;
} bst_map_t;

typedef Status (*to_string_s)(void *value, char *string);
typedef int (*compare_s)(void *value1, void *value2);


bst_map_t *bst_map(int key_data_size, int value_data_size);
int bst_map_size(bst_map_t *bst_map_tree);
bool bst_map_is_empty(bst_map_t *bst_map_tree);
Status bst_map_add_r(bst_map_t *bst_map_tree, void *key, void *value, compare_s compare_t);
bool bst_map_contain_r(bst_map_t *bst_map_tree, void *key, compare_s compare_t);
void *bst_map_get_r(bst_map_t *bst_map_tree, void *key, void *ret_value, compare_s compare_t);
Status bst_map_set(bst_map_t *bst_map_tree, void *key, void *value, compare_s compare_t);
void *bst_map_remove_r(bst_map_t *bst_map_tree, void *key, void *ret_value, compare_s compare_t);
Status bst_map_clear_r(bst_map_t *bst_map_tree);
Status bst_map_destroy(bst_map_t **bst_map_tree);
bst_set_t *bst_map_key_set_r(bst_map_t *bst_map_tree, bst_set_t *set, compare_s compare_t);


#endif //DATA_STRUCTURES_BST_MAP_H
