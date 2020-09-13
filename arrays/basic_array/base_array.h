//
// Created by 焦宏宇 on 2020/2/8.
//

#ifndef DATASTRUCTURES_BASE_ARRAY_H
#define DATASTRUCTURES_BASE_ARRAY_H
#include <stdbool.h>
#include <string.h>

#define DEFAULTCAPACITY 10

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define OVERFLOW -1
typedef int Status;

void *basic_array_c(int capacity, int element_size);
void *basic_array(int element_size);
Status basic_array_index_copy(void *arr, int elem_size, int src_index, int dst_index);
Status basic_array_elem_copy(void *arr, int elem_size, int index, void *e);
void *basic_array_get_elem(void *arr, int elem_size, int index, void *ret);
bool basic_array_elem_cmp(void *arr, int elem_size, int index, void *e);
Status basic_array_arr_copy(void *src_arr, void *dst_arr, int begin_index, int end_index, int elem_size);
Status basic_array_copy(void *src_arr, void *dst_arr, int src_index, int dst_index, int elem_size);
Status basic_array_destroy(void **arr);
Status basic_array_segment_copy(void *arr, int elem_size, int src_index, int dst_index, size_t n);
Status basic_array_elem_swap(void *arr, int i, int j, int elem_size);

#endif //DATASTRUCTURES_BASE_ARRAY_H
