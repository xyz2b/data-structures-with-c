//
// Created by 焦宏宇 on 2020/2/12.
//

#ifndef DATA_STRUCTURES_basic_BST_H
#define DATA_STRUCTURES_basic_BST_H
#include <stdbool.h>
#include "../../stacks/linked_list_stack/linked_list_stack.h"
#include "../../queues/linked_list_queue/linked_list_queue.h"

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define OVERFLOW -1
typedef int Status;


typedef struct basic_bst_node_s
{
    void *data;  /*数据域*/
    struct basic_bst_node_s *left, *right; /*指针域*/
} basic_bst_node_t;

typedef struct basic_bst_s
{
    int data_size; /*数据域元数的大小*/
    int size; /*树的大小*/
    basic_bst_node_t *root;
} basic_bst_t;

typedef Status (*to_string_s)(void *value, char *string);
typedef int (*compare_s)(void *value1, void *value2);

basic_bst_t *basic_bst(int data_size);
int basic_bst_size(basic_bst_t *bst_tree);
bool basic_bst_is_empty(basic_bst_t *bst_tree);
Status basic_bst_add_r(basic_bst_t *bst_tree, void *e, compare_s compare_t);
bool basic_bst_contain_r(basic_bst_t *bst_tree, void *e, compare_s compare_t);
void basic_bst_pre_order_r(basic_bst_t *bst_tree, to_string_s to_string_t);
void basic_bst_in_order_r(basic_bst_t *bst_tree, to_string_s to_string_t);
void basic_bst_post_order_r(basic_bst_t *bst_tree, to_string_s to_string_t);
void basic_bst_pre_order_nr(basic_bst_t *bst_tree, to_string_s to_string_t);
void basic_bst_level_order_nr(basic_bst_t *bst_tree, to_string_s to_string_t);
Status basic_bst_minimum_r(basic_bst_t *bst_tree, void *ret);
Status basic_bst_maximum_r(basic_bst_t *bst_tree, void *ret);
Status basic_bst_remove_minimum_r(basic_bst_t *bst_tree, void *ret);
Status basic_bst_remove_maximum_r(basic_bst_t *bst_tree, void *ret);
Status basic_bst_remove_r(basic_bst_t *bst_tree, void *e, compare_s compare_t);
Status basic_bst_clear_r(basic_bst_t *bst_tree);
Status basic_bst_destroy(basic_bst_t **bst_tree);
Status basic_bst_floor_r(basic_bst_t *bst_tree, void *e, void *ret, compare_s compare_t);
Status basic_bst_ceil_r(basic_bst_t *bst_tree, void *e, void *ret, compare_s compare_t);


#endif //DATA_STRUCTURES_basic_BST_H
