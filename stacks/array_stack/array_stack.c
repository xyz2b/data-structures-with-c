//
// Created by 焦宏宇 on 2020/2/7.
//

#include "array_stack.h"
#include <stdio.h>
#include <stdlib.h>

// 初始化栈 with capacity
array_stack_t *array_stack_c(int capacity, int element_size)
{
    dynamic_array_t *arr = array_c(capacity, element_size);
    if(!arr){
        // 存储分配失败
        return NULL;
    }

    array_stack_t *array_stack = (array_stack_t *)malloc(sizeof(array_stack_t));
    if(!array_stack){
        // 存储分配失败
        free(array_stack);
        return NULL;
    }

    array_stack->array = arr;

    return array_stack;
}

// 初始化栈，默认容量
array_stack_t *array_stack(int element_size)
{
    dynamic_array_t *arr = array(element_size);
    if(!arr){
        // 存储分配失败
        return NULL;
    }

    array_stack_t *array_stack = (array_stack_t *)malloc(sizeof(array_stack_t));
    if(!array_stack){
        // 存储分配失败
        free(array_stack);
        return NULL;
    }

    array_stack->array = arr;

    return array_stack;
}

// 获取栈的元素个数
int array_stack_size(array_stack_t *array_stack)
{
    if(array_stack == NULL){
        exit(OVERFLOW);
    }

    return array_stack->array->size;
}

// 判断栈是否为空
bool array_stack_is_empty(array_stack_t *array_stack)
{
    if(array_stack == NULL){
        exit(OVERFLOW);
    }

    return array_stack->array->size == 0;
}

// 获取栈的容积
int array_stack_capacity(array_stack_t *array_stack)
{
    if(array_stack == NULL){
        exit(OVERFLOW);
    }

    return array_stack->array->capacity;
}

// 压栈
Status array_stack_push(array_stack_t *array_stack, void *e)
{
    if(array_stack == NULL){
        exit(OVERFLOW);
    }

    Status ok = array_insert_last(array_stack->array, e);
    if(!ok){
        return ERROR;
    }

    return OK;
}

// 出栈
Status array_stack_pop(array_stack_t *array_stack, void *ret)
{
    if(array_stack == NULL){
        exit(OVERFLOW);
    }

    Status ok = array_remove_last(array_stack->array, ret);
    if(!ok){
        return ERROR;
    }

    return OK;
}

// 查看栈顶的元素
Status array_stack_peek(array_stack_t *array_stack, void *ret)
{
    if(array_stack == NULL){
        exit(OVERFLOW);
    }

    Status ok = array_get_last(array_stack->array, ret);
    if(!ok){
        return ERROR;
    }

    return OK;
}

// 查看栈信息，需要传入调用方定义的将调用方自定义的类型转换成数组的函数to_string
void array_stack_show(array_stack_t *array_stack, to_string_s to_string_t)
{
    if(array_stack == NULL){
        exit(OVERFLOW);
    }

    void *ret = (char *)malloc(array_stack->array->element_size);
    if(!ret)  // 存储分配失败
        exit(OVERFLOW);

    printf("Stack: size = %d, capacity = %d, elem_size = %d\n", array_stack->array->size, array_stack->array->capacity, array_stack->array->element_size);
    printf("[");

    for(int i = 0; i < array_stack->array->size; i++)
    {
        // TODO: 解决类型转换后接收字符串的数组buffer容量大小固定问题
        char buffer[200];
        array_get(array_stack->array, i, ret);
        int ok = (*to_string_t)(ret, buffer);
        if(ok != OK){
            free(ret);
            exit(ERROR);
        }
        if(i == array_stack->array->size -1){
            printf("%s", buffer);
        } else {
            printf("%s, ", buffer);
        }
    }

    printf("] top\n");

    free(ret);
}

// 清空栈
Status array_stack_clear(array_stack_t *array_stack)
{
    if(array_stack == NULL){
        exit(OVERFLOW);
    }

    array_stack->array->size = 0;
    return OK;
}

// 销毁栈
Status array_stack_destroy(array_stack_t **array_stack)
{
    if(*array_stack == NULL){
        exit(OVERFLOW);
    }

    array_destroy(&((*array_stack)->array));

    (*array_stack)->array = NULL;

    free(*array_stack);

    *array_stack = NULL;

    return OK;
}