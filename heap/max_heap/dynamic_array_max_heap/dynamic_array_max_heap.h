//
// Created by 焦宏宇 on 2020/2/16.
//

#ifndef DATA_STRUCTURES_DYNAMIC_ARRAY_MAX_HEAP_H
#define DATA_STRUCTURES_DYNAMIC_ARRAY_MAX_HEAP_H

#include "../../../arrays/dynamic_array/dynamic_array.h"


typedef struct dynamic_array_max_heap_s{
    dynamic_array_t *dynamic_a;
} dynamic_array_max_heap_t;

typedef int (*compare_s)(void *value1, void *value2);

dynamic_array_max_heap_t *dynamic_array_max_heap_c(int capacity, int element_size);
dynamic_array_max_heap_t *dynamic_array_max_heap(int element_size);
int dynamic_array_max_heap_size(dynamic_array_max_heap_t *dynamic_array_max_h);
int dynamic_array_max_heap_capacity(dynamic_array_max_heap_t *dynamic_array_max_h);
bool dynamic_array_max_heap_is_empty(dynamic_array_max_heap_t *dynamic_array_max_h);
Status dynamic_array_max_heap_add(dynamic_array_max_heap_t *dynamic_array_max_h, void *e, compare_s compare_t);
void *dynamic_array_max_heap_find_max(dynamic_array_max_heap_t *dynamic_array_max_h, void *ret);
void *dynamic_array_max_heap_extract_max(dynamic_array_max_heap_t *dynamic_array_max_h, void *ret, compare_s compare_t);
Status dynamic_array_max_heap_clear(dynamic_array_max_heap_t *dynamic_array_max_h);
Status dynamic_array_max_heap_destroy(dynamic_array_max_heap_t **dynamic_array_max_h);
void *dynamic_array_max_heap_replace(dynamic_array_max_heap_t *dynamic_array_max_h, void *e, void *ret, compare_s compare_t);
dynamic_array_max_heap_t *dynamic_array_max_heap_heapify(void *arr, int arr_length, int elem_size, compare_s compare_t);


#endif //DATA_STRUCTURES_DYNAMIC_ARRAY_MAX_HEAP_H
