//
// Created by 焦宏宇 on 2020/2/9.
//

#ifndef DATA_STRUCTURES_LINKED_LIST_QUEUE_H
#define DATA_STRUCTURES_LINKED_LIST_QUEUE_H
#include <stdbool.h>
#include "../../linked_list/base_linked_list/base_linked_list.h"


typedef struct linked_list_queue_s
{
    int size;
    int data_size; /*数据域元数的大小*/
    node_s *head, *tail; /*头结点和尾结点*/
}linked_list_queue_t;


linked_list_queue_t *linked_list_queue(int data_size);
int linked_list_queue_size(linked_list_queue_t *linked_list_q);
bool linked_list_queue_is_empty(linked_list_queue_t *linked_list_q);
Status linked_list_queue_enqueue(linked_list_queue_t *linked_list_q, void *e);
Status linked_list_queue_dequeue(linked_list_queue_t *linked_list_q, void *ret);
Status linked_list_queue_front(linked_list_queue_t *linked_list_q, void *ret);
Status linked_list_queue_show(linked_list_queue_t *linked_list_q, to_string_s to_string_t);
Status linked_list_queue_clear(linked_list_queue_t *linked_list_q);
Status linked_list_queue_destroy(linked_list_queue_t **linked_list_q);


#endif //DATA_STRUCTURES_LINKED_LIST_QUEUE_H
