//
// Created by 焦宏宇 on 2020/2/8.
//

#include "array_queue.h"
#include <stdio.h>
#include <stdlib.h>

// 初始化队列 with capacity
array_queue_t *array_queue_c(int capacity, int element_size)
{
    dynamic_array_t *arr = array_c(capacity, element_size);
    if(!arr){
        // 存储分配失败
        return NULL;
    }

    array_queue_t *array_queue = (array_queue_t *)malloc(sizeof(array_queue_t));
    if(!array_queue){
        // 存储分配失败
        free(array_queue);
        return NULL;
    }

    array_queue->array = arr;

    return array_queue;
}

// 初始化队列，默认容量
array_queue_t *array_queue(int element_size)
{
    dynamic_array_t *arr = array(element_size);
    if(!arr){
        // 存储分配失败
        return NULL;
    }

    array_queue_t *array_queue = (array_queue_t *)malloc(sizeof(array_queue_t));
    if(!array_queue){
        // 存储分配失败
        free(array_queue);
        return NULL;
    }

    array_queue->array = arr;

    return array_queue;
}

// 获取队列的元素个数
int array_queue_size(array_queue_t *array_queue)
{
    if(array_queue == NULL){
        exit(OVERFLOW);
    }

    return array_queue->array->size;
}

// 判断队列是否为空
bool array_queue_is_empty(array_queue_t *array_queue)
{
    if(array_queue == NULL){
        exit(OVERFLOW);
    }

    return array_queue->array->size == 0;
}

// 获取队列的容积
int array_queue_capacity(array_queue_t *array_queue)
{
    if(array_queue == NULL){
        exit(OVERFLOW);
    }

    return array_queue->array->capacity;
}

// 入队
Status array_queue_enqueue(array_queue_t *array_queue, void *e)
{
    if(array_queue == NULL){
        exit(OVERFLOW);
    }

    Status ok = array_insert_last(array_queue->array, e);
    if(!ok){
        return ERROR;
    }

    return OK;
}

// 出队
Status array_queue_dequeue(array_queue_t *array_queue, void *ret)
{
    if(array_queue == NULL){
        exit(OVERFLOW);
    }

    Status ok = array_remove_first(array_queue->array, ret);
    if(!ok){
        return ERROR;
    }

    return OK;
}

// 查看队首的元素
Status array_queue_front(array_queue_t *array_queue, void *ret)
{
    if(array_queue == NULL){
        exit(OVERFLOW);
    }

    Status ok = array_get_first(array_queue->array, ret);
    if(!ok){
        return ERROR;
    }

    return OK;
}

// 查看队列信息，需要传入调用方定义的将调用方自定义的类型转换成数组的函数to_string
void array_queue_show(array_queue_t *array_queue, to_string_s to_string_t)
{
    if(array_queue == NULL){
        exit(OVERFLOW);
    }

    void *ret = (char *)malloc(array_queue->array->element_size);
    if(!ret)  // 存储分配失败
        exit(OVERFLOW);

    printf("Queue: size = %d, capacity = %d, elem_size = %d\n", array_queue->array->size, array_queue->array->capacity, array_queue->array->element_size);
    printf("front [");

    for(int i = 0; i < array_queue->array->size; i++)
    {
        // TODO: 解决类型转换后接收字符串的数组buffer容量大小固定问题
        char buffer[200];
        array_get(array_queue->array, i, ret);
        int ok = (*to_string_t)(ret, buffer);
        if(ok != OK){
            free(ret);
            exit(ERROR);
        }
        if(i != array_queue->array->size -1){
            printf("%s, ", buffer);
        } else {
            printf("%s", buffer);
        }
    }

    printf("] tail\n");

    free(ret);
}

// 清空队列
Status array_queue_clear(array_queue_t *array_queue)
{
    if(array_queue == NULL){
        exit(OVERFLOW);
    }

    array_queue->array->size = 0;
    return OK;
}

// 销毁队列
Status array_queue_destroy(array_queue_t **array_queue)
{
    if(*array_queue == NULL){
        exit(OVERFLOW);
    }

    array_destroy(&((*array_queue)->array));

    (*array_queue)->array = NULL;

    free(*array_queue);

    *array_queue = NULL;

    return OK;
}