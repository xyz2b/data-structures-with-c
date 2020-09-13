//
// Created by 焦宏宇 on 2020/2/7.
//

#ifndef DATASTRUCTURES_ARRAY_STACK_H
#define DATASTRUCTURES_ARRAY_STACK_H

#include "../../arrays/dynamic_array/dynamic_array.h"

struct array_stack_s
{
    dynamic_array_t *array;
};



#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define OVERFLOW -1
typedef int Status;



typedef struct array_stack_s array_stack_t;

array_stack_t *array_stack_c(int capacity, int element_size);
array_stack_t *array_stack(int element_size);
int array_stack_size(array_stack_t *array_stack);
int array_stack_capacity(array_stack_t *array_stack);
bool array_stack_is_empty(array_stack_t *array_stack);
Status array_stack_push(array_stack_t *array_stack, void *e);
Status array_stack_pop(array_stack_t *array_stack, void *ret);
Status array_stack_peek(array_stack_t *array_stack, void *ret);
void array_stack_show(array_stack_t *array_stack, to_string_s to_string_t);
Status array_stack_clear(array_stack_t *array_stack);
Status array_stack_destroy(array_stack_t **array_stack);



#endif //DATASTRUCTURES_ARRAY_STACK_H