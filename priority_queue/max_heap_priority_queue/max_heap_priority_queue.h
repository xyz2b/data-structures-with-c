//
// Created by 焦宏宇 on 2020/2/16.
//

#ifndef DATA_STRUCTURES_MAX_HEAP_PRIORITY_QUEUE_H
#define DATA_STRUCTURES_MAX_HEAP_PRIORITY_QUEUE_H

#include "../../heap/max_heap/dynamic_array_max_heap/dynamic_array_max_heap.h"

typedef struct max_heap_priority_queue_s{
    dynamic_array_max_heap_t *max_h;
} max_heap_priority_queue_t;


max_heap_priority_queue_t *max_heap_priority_queue_c(int capacity, int element_size);
max_heap_priority_queue_t *max_heap_priority_queue(int element_size);
int max_heap_priority_queue_size(max_heap_priority_queue_t *q);
bool max_heap_priority_queue_is_empty(max_heap_priority_queue_t *q);
int max_heap_priority_queue_capacity(max_heap_priority_queue_t *q);
Status max_heap_priority_queue_enqueue(max_heap_priority_queue_t *q, void *e, compare_s compare_t);
Status max_heap_priority_queue_dequeue(max_heap_priority_queue_t *q, void *ret, compare_s compare_t);
Status max_heap_priority_queue_front(max_heap_priority_queue_t *q, void *ret);
Status max_heap_priority_queue_clear(max_heap_priority_queue_t *q);
Status max_heap_priority_queue_destroy(max_heap_priority_queue_t **q);



#endif //DATA_STRUCTURES_MAX_HEAP_PRIORITY_QUEUE_H
