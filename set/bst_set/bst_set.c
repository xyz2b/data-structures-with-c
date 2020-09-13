//
// Created by 焦宏宇 on 2020/2/14.
//

#include "bst_set.h"
#include <stdlib.h>

// 生成集合
bst_set_t *bst_set(int data_size)
{
    bst_set_t *set = (bst_set_t *)malloc(sizeof(bst_set_t));
    if(!set)
        return NULL;

    set->basic_bst_tree =  basic_bst(data_size);

    return set;
}

// 获取集合的大小
int bst_set_size(bst_set_t *set)
{
    if(!set)
        return OVERFLOW;

    return set->basic_bst_tree->size;
}

// 集合是否为空
bool bst_set_is_empty(bst_set_t *set)
{
    if(!set)
        return OVERFLOW;

    return set->basic_bst_tree->size == 0;
}

// 添加元素e
Status bst_set_add(bst_set_t *set, void *e, compare_s compare_t)
{
    basic_bst_add_r(set->basic_bst_tree, e, compare_t);

    return OK;
}

// 是否包含元素e
bool bst_set_contain(bst_set_t *set, void *e, compare_s compare_t)
{
    return basic_bst_contain_r(set->basic_bst_tree, e, compare_t);
}

// 删除元素e
Status bst_set_remove(bst_set_t *set, void *e, compare_s compare_t)
{
    basic_bst_remove_r(set->basic_bst_tree, e, compare_t);

    return OK;
}

// 删除最大的元素
Status bst_set_remove_maximum(bst_set_t *set, void *ret)
{
    basic_bst_remove_maximum_r(set->basic_bst_tree, ret);

    return OK;
}

// 清空集合
Status bst_set_clear(bst_set_t *set)
{
    basic_bst_clear_r(set->basic_bst_tree);

    return OK;
}

// 销毁集合
Status bst_set_destroy(bst_set_t **set)
{
    basic_bst_destroy(&((*set)->basic_bst_tree));
    *set = NULL;

    return OK;
}