//
// Created by 焦宏宇 on 2020/2/23.
//

#ifndef DATA_STRUCTURES_two_three_tree_H
#define DATA_STRUCTURES_two_three_tree_H
#include <stdbool.h>
#include "../stacks/linked_list_stack/linked_list_stack.h"
#include "../queues/linked_list_queue/linked_list_queue.h"

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define OVERFLOW -1
typedef int Status;


typedef struct two_three_tree_node_s
{
    void *left_data;  /*3节点中较小的数据域或2节点的数据域*/
    void *right_data; /*3节点中较大的数据域*/
    bool three;  /*是否是3节点*/
    struct two_three_tree_node_s *left, *middle ,*right; /*指针域*/
} two_three_tree_node_t;

typedef struct two_three_tree_s
{
    int data_size; /*数据域元数的大小*/
    int size; /*树的大小*/
    two_three_tree_node_t *root;
} two_three_tree_t;

typedef Status (*to_string_s)(void *value, char *string);
typedef int (*compare_s)(void *value1, void *value2);

two_three_tree_t *two_three_tree(int data_size);
int two_three_tree_size(two_three_tree_t *two_three_t);
bool two_three_tree_is_empty(two_three_tree_t *two_three_t);
Status two_three_tree_add_r(two_three_tree_t *two_three_t, void *e, compare_s compare_t);
bool two_three_tree_contain_r(two_three_tree_t *two_three_t, void *e, compare_s compare_t);
void two_three_tree_pre_order_r(two_three_tree_t *two_three_t, to_string_s to_string_t);
void two_three_tree_in_order_r(two_three_tree_t *two_three_t, to_string_s to_string_t);
void two_three_tree_post_order_r(two_three_tree_t *two_three_t, to_string_s to_string_t);
Status two_three_tree_minimum_r(two_three_tree_t *two_three_t, void *ret);
Status two_three_tree_maximum_r(two_three_tree_t *two_three_t, void *ret);
Status two_three_tree_remove_minimum_r(two_three_tree_t *two_three_t, void *ret);
Status two_three_tree_remove_maximum_r(two_three_tree_t *two_three_t, void *ret);
Status two_three_tree_remove_r(two_three_tree_t *two_three_t, void *e, compare_s compare_t);
Status two_three_tree_clear_r(two_three_tree_t *two_three_t);
Status two_three_tree_destroy(two_three_tree_t **two_three_t);





#endif //DATA_STRUCTURES_two_three_tree_H
