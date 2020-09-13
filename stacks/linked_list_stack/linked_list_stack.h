//
// Created by 焦宏宇 on 2020/2/9.
//

#ifndef DATA_STRUCTURES_LINKED_LIST_STACK_H
#define DATA_STRUCTURES_LINKED_LIST_STACK_H
#include "../../linked_list/base_linked_list/base_linked_list.h"

struct linked_list_stack_s
{
    linked_list_t *linked_l;
};



#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define OVERFLOW -1
typedef int Status;



typedef struct linked_list_stack_s linked_list_stack_t;

linked_list_stack_t *linked_list_stack(int data_size);
int linked_list_stack_size(linked_list_stack_t *linked_list_s);
bool linked_list_stack_is_empty(linked_list_stack_t *linked_list_s);
Status linked_list_stack_push(linked_list_stack_t *linked_list_s, void *e);
Status linked_list_stack_pop(linked_list_stack_t *linked_list_s, void *ret);
Status linked_list_stack_peek(linked_list_stack_t *linked_list_s, void *ret);
Status linked_list_stack_show(linked_list_stack_t *linked_list_s, to_string_s to_string_t);
Status linked_list_stack_clear(linked_list_stack_t *linked_list_s);
Status linked_list_stack_destroy(linked_list_stack_t **linked_list_s);

#endif //DATA_STRUCTURES_LINKED_LIST_STACK_H
