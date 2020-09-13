//
// Created by 焦宏宇 on 2020/2/14.
//

#ifndef DATA_STRUCTURES_BST_SET_H
#define DATA_STRUCTURES_BST_SET_H

#include "../../bst/basic_bst/basic_bst.h"

typedef struct bst_set_s
{
    struct basic_bst_s *basic_bst_tree;
} bst_set_t;


bst_set_t *bst_set(int data_size);
int bst_set_size(bst_set_t *set);
bool bst_set_is_empty(bst_set_t *set);
Status bst_set_add(bst_set_t *set, void *e, compare_s compare_t);
bool bst_set_contain(bst_set_t *set, void *e, compare_s compare_t);
Status bst_set_remove(bst_set_t *set, void *e, compare_s compare_t);
Status bst_set_clear(bst_set_t *set);
Status bst_set_destroy(bst_set_t **set);
Status bst_set_remove_maximum(bst_set_t *set, void *ret);


#endif //DATA_STRUCTURES_BST_SET_H
