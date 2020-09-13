//
// Created by 焦宏宇 on 2020/2/23.
//

#ifndef DATA_STRUCTURES_RB_TREE_H
#define DATA_STRUCTURES_RB_TREE_H
#include <stdbool.h>
#include "../set/bst_set/bst_set.h"

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define OVERFLOW -1
typedef int Status;


#define black false
#define red true

typedef struct rb_tree_node_s
{
    void *value;
    void *key;
    struct rb_tree_node_s *left, *right; /*指针域*/
    bool color;
} rb_tree_node_t;

typedef struct rb_tree_s
{
    int key_data_size;
    int value_data_size;
    int size; /*树的大小*/
    rb_tree_node_t *root;
} rb_tree_t;

typedef Status (*to_string_s)(void *value, char *string);
typedef int (*compare_s)(void *value1, void *value2);


rb_tree_t *rb_tree(int key_data_size, int value_data_size);
int rb_tree_size(rb_tree_t *rb_tree_tree);
bool rb_tree_is_empty(rb_tree_t *rb_tree_tree);
Status rb_tree_add_r(rb_tree_t *rb_tree_tree, void *key, void *value, compare_s compare_t);
bool rb_tree_contain_r(rb_tree_t *rb_tree_tree, void *key, compare_s compare_t);
void *rb_tree_get_r(rb_tree_t *rb_tree_tree, void *key, void *ret_value, compare_s compare_t);
Status rb_tree_set(rb_tree_t *rb_tree_tree, void *key, void *value, compare_s compare_t);
void *rb_tree_remove_r(rb_tree_t *rb_tree_tree, void *key, void *ret_value, compare_s compare_t);
Status rb_tree_clear_r(rb_tree_t *rb_tree_tree);
Status rb_tree_destroy(rb_tree_t **rb_tree_tree);
bst_set_t *rb_tree_key_set_r(rb_tree_t *rb_tree_tree, bst_set_t *set, compare_s compare_t);

#endif //DATA_STRUCTURES_RB_TREE_H
