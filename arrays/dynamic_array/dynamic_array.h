//
// Created by 焦宏宇 on 2020/2/4.
//

#include <stdbool.h>

#ifndef DATASTRUCTURES_DYNAMICARRAY_H
#define DATASTRUCTURES_DYNAMICARRAY_H
#include "../basic_array/base_array.h"

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define OVERFLOW -1
typedef int Status;

struct dynamic_array_s
{
    void* data;
    int element_size;
    int size;
    int capacity;
};

typedef struct dynamic_array_s dynamic_array_t;

typedef Status (*to_string_s)(void *value, char *string);

dynamic_array_t *array_c(int capacity, int element_size);
dynamic_array_t *array(int element_size);
int array_size(dynamic_array_t *dynamic_array);
int array_capacity(dynamic_array_t *dynamic_array);
bool array_is_empty(dynamic_array_t *dynamic_array);
Status array_insert(dynamic_array_t *dynamic_array, int index, void *e);
Status array_insert_last(dynamic_array_t *dynamic_array, void *e);
Status array_insert_first(dynamic_array_t *dynamic_array, void *e);
void *array_get(dynamic_array_t *dynamic_array, int index, void *ret);
Status array_get_last(dynamic_array_t *dynamic_array, void *ret);
Status array_get_first(dynamic_array_t *dynamic_array, void *ret);
Status array_set(dynamic_array_t *dynamic_array, int index, void *e);
bool array_contain(dynamic_array_t *dynamic_array, void *e);
int array_find(dynamic_array_t *dynamic_array, void *e);
Status array_remove(dynamic_array_t *dynamic_array, int index, void *ret);
Status array_remove_last(dynamic_array_t *dynamic_array, void *ret);
Status array_remove_first(dynamic_array_t *dynamic_array, void *ret);
Status array_remove_elem(dynamic_array_t *dynamic_array, void *e);
void array_show(dynamic_array_t *dynamic_array, to_string_s to_string_t);
Status array_clear(dynamic_array_t *dynamic_array);
Status array_destroy(dynamic_array_t **dynamic_array);
void array_swap(dynamic_array_t *dynamic_array, int i, int j);
dynamic_array_t *array_basic_arr_to_dynamic_arr(void *arr, int arr_length, int element_size);

#endif //DATASTRUCTURES_DYNAMICARRAY_H