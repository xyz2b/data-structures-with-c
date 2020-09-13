//
// Created by 焦宏宇 on 2020/2/15.
//

#include "linked_list_set.h"
#include <stdlib.h>


// 创建集合
linked_list_set_t *linked_list_sets(int data_size){
    linked_list_set_t *set = (linked_list_set_t *)malloc(sizeof(linked_list_set_t));
    if(!set)
        return NULL;

    set->linked_l =  linked_list(data_size);

    return set;
}

// 返回集合的大小
int linked_list_set_size(linked_list_set_t *set)
{
    return set->linked_l->size;
}

// 返回集合是否为空
bool linked_list_set_is_empty(linked_list_set_t *set)
{
    return linked_list_is_empty(set->linked_l);
}

// 添加元素
Status linked_list_set_add(linked_list_set_t *set, void *e)
{
    if(linked_list_contain(set->linked_l, e) == false)
        linked_list_insert_first(set->linked_l, e);

    return OK;
}

// 是否包含元素e
bool linked_list_set_contain(linked_list_set_t *set, void *e)
{
    return linked_list_contain(set->linked_l, e);
}

// 删除元素
Status linked_list_set_remove(linked_list_set_t *set, void *e, compare_s compare_t)
{
    linked_list_remove_elem(set->linked_l, e, compare_t);

    return OK;
}

// 清空
Status linked_list_set_clear(linked_list_set_t *set)
{
    linked_list_clear(set->linked_l);

    return OK;
}

// 销毁
Status linked_list_set_destroy(linked_list_set_t **set)
{
    linked_list_destroy(&((*set)->linked_l));

    return OK;
}