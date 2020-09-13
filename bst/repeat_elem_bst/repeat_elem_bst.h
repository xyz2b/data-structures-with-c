//
// Created by 焦宏宇 on 2020/2/12.
//

#ifndef DATA_STRUCTURES_REPEAT_ELEM_BST_H
#define DATA_STRUCTURES_REPEAT_ELEM_BST_H
#include <stdbool.h>
#include "../../stacks/linked_list_stack/linked_list_stack.h"
#include "../../queues/linked_list_queue/linked_list_queue.h"

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define OVERFLOW -1
typedef int Status;


typedef struct repeat_elem_bst_node_s
{
    void *data;  /*数据域*/
    struct repeat_elem_bst_node_s *left, *right; /*指针域*/
    int tree_size; /*该node作为根节点的树总共包含几个节点*/
    int depth;  /*该node处于树的第几层*/
    int count; /*重复元素的个数*/
} repeat_elem_bst_node_t;

typedef struct repeat_elem_bst_s
{
    int data_size; /*数据域元数的大小*/
    repeat_elem_bst_node_t *root;
} repeat_elem_bst_t;

typedef Status (*to_string_s)(void *value, char *string);
typedef int (*compare_s)(void *value1, void *value2);

repeat_elem_bst_t *repeat_elem_bst(int data_size);
int repeat_elem_bst_size(repeat_elem_bst_t *bst_tree);
bool repeat_elem_bst_is_empty(repeat_elem_bst_t *bst_tree);
Status repeat_elem_bst_add_r(repeat_elem_bst_t *bst_tree, void *e, compare_s compare_t);
bool repeat_elem_bst_contain_r(repeat_elem_bst_t *bst_tree, void *e, compare_s compare_t);
void repeat_elem_bst_pre_order_r(repeat_elem_bst_t *bst_tree, to_string_s to_string_t);
void repeat_elem_bst_in_order_r(repeat_elem_bst_t *bst_tree, to_string_s to_string_t);
void repeat_elem_bst_post_order_r(repeat_elem_bst_t *bst_tree, to_string_s to_string_t);
void repeat_elem_bst_pre_order_nr(repeat_elem_bst_t *bst_tree, to_string_s to_string_t);
void repeat_elem_bst_level_order_nr(repeat_elem_bst_t *bst_tree, to_string_s to_string_t);
Status repeat_elem_bst_minimum_r(repeat_elem_bst_t *bst_tree, void *ret);
Status repeat_elem_bst_maximum_r(repeat_elem_bst_t *bst_tree, void *ret);
Status repeat_elem_bst_remove_minimum_r(repeat_elem_bst_t *bst_tree, void *ret);
Status repeat_elem_bst_remove_maximum_r(repeat_elem_bst_t *bst_tree, void *ret);
Status repeat_elem_bst_remove_r(repeat_elem_bst_t *bst_tree, void *e, compare_s compare_t);
Status repeat_elem_bst_clear_r(repeat_elem_bst_t *bst_tree);
Status repeat_elem_bst_destroy(repeat_elem_bst_t **bst_tree);
Status repeat_elem_bst_floor_r(repeat_elem_bst_t *bst_tree, void *e, void *ret, compare_s compare_t);
Status repeat_elem_bst_ceil_r(repeat_elem_bst_t *bst_tree, void *e, void *ret, compare_s compare_t);
int repeat_elem_bst_rank_r(repeat_elem_bst_t *bst_tree, void *e, compare_s compare_t);
int repeat_elem_bst_elem_count_r(repeat_elem_bst_t *bst_tree, void *e, compare_s compare_t);
Status repeat_elem_bst_select_r(repeat_elem_bst_t *bst_tree, int index, void *ret, compare_s compare_t);


#endif //DATA_STRUCTURES_REPEAT_ELEM_BST_H
