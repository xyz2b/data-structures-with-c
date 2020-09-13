//
// Created by 焦宏宇 on 2020/2/17.
//

#ifndef DATA_STRUCTURES_ARRAY_SEGMENT_TREE_H
#define DATA_STRUCTURES_ARRAY_SEGMENT_TREE_H


#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define OVERFLOW -1
typedef int Status;

#include "../../arrays/dynamic_array/dynamic_array.h"


typedef struct array_segment_tree_s{
    dynamic_array_t *dynamic_a;
} array_segment_tree_t;

typedef Status (*to_string_s)(void *value, char *string);
typedef void *(*merge_s)(void *value1, void *value2, void *e);


array_segment_tree_t *array_segment_tree(int capacity, int element_size);
void *array_segment_tree_get(array_segment_tree_t *array_segment_t, int index, void *ret);
Status array_segment_tree_build(dynamic_array_t *arr, array_segment_tree_t *array_segment_t, int index, int l, int r, merge_s merge_t);
void array_segment_tree_show(array_segment_tree_t *array_segment_t, to_string_s to_string_t);
Status array_segment_tree_query_r(array_segment_tree_t *array_segment_t, int data_length, int query_l, int query_r, void *ret, merge_s merge_t);
dynamic_array_t *array_segment_tree_array(void *arr, int capacity, int element_size);
Status array_segment_tree_set_r(dynamic_array_t *arr, array_segment_tree_t *array_segment_t, int index, void *e, merge_s merge_t);

#endif //DATA_STRUCTURES_ARRAY_SEGMENT_TREE_H
