//
// Created by 焦宏宇 on 2020/2/14.
//

#ifndef DATA_STRUCTURES_LINKED_LIST_SET_H
#define DATA_STRUCTURES_LINKED_LIST_SET_H

#include "../../linked_list/base_linked_list/base_linked_list.h"

typedef struct linked_list_set_s
{
    struct linked_list_s *linked_l;
} linked_list_set_t;


linked_list_set_t *linked_list_sets(int data_size);
int linked_list_set_size(linked_list_set_t *set);
bool linked_list_set_is_empty(linked_list_set_t *set);
Status linked_list_set_add(linked_list_set_t *set, void *e);
bool linked_list_set_contain(linked_list_set_t *set, void *e);
Status linked_list_set_remove(linked_list_set_t *set, void *e, compare_s compare_t);
Status linked_list_set_clear(linked_list_set_t *set);
Status linked_list_set_destroy(linked_list_set_t **set);


#endif //DATA_STRUCTURES_LINKED_LIST_SET_H
