//
// Created by 焦宏宇 on 2020/2/21.
//

#ifndef DATA_STRUCTURES_AVL_TREE_H
#define DATA_STRUCTURES_AVL_TREE_H
#include <stdbool.h>
#include "../../arrays/dynamic_array/dynamic_array.h"

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define OVERFLOW -1
typedef int Status;



typedef struct avl_tree_node_s
{
    void *value;
    void *key;
    int height;
    struct avl_tree_node_s *left, *right; /*指针域*/
} avl_tree_node_t;

typedef struct avl_tree_s
{
    int key_data_size;
    int value_data_size;
    int size; /*树的大小*/
    avl_tree_node_t *root;
} avl_tree_t;

typedef Status (*to_string_s)(void *value, char *string);
typedef int (*compare_s)(void *value1, void *value2);


avl_tree_t *avl_tree(int key_data_size, int value_data_size);
int avl_tree_size(avl_tree_t *avl_tree_tree);
bool avl_tree_is_empty(avl_tree_t *avl_tree_tree);
Status avl_tree_add_r(avl_tree_t *avl_tree_tree, void *key, void *value, compare_s compare_t);
bool avl_tree_contain_r(avl_tree_t *avl_tree_tree, void *key, compare_s compare_t);
void *avl_tree_get_r(avl_tree_t *avl_tree_tree, void *key, void *ret_value, compare_s compare_t);
Status avl_tree_set(avl_tree_t *avl_tree_tree, void *key, void *value, compare_s compare_t);
void *avl_tree_remove_r(avl_tree_t *avl_tree_tree, void *key, void *ret_value, compare_s compare_t);
Status avl_tree_clear_r(avl_tree_t *avl_tree_tree);
Status avl_tree_destroy(avl_tree_t **avl_tree_tree);
bool avl_tree_is_bst(avl_tree_t *avl_tree_tree, compare_s compare_t);
bool avl_tree_is_balance_r(avl_tree_t *avl_tree);

#endif //DATA_STRUCTURES_AVL_TREE_H
