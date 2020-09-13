//
// Created by 焦宏宇 on 2020/2/16.
//

#include "max_heap_priority_queue.h"
#include <stdio.h>
#include <stdlib.h>

// 初始化队列 with capacity
max_heap_priority_queue_t *max_heap_priority_queue_c(int capacity, int element_size)
{
    dynamic_array_max_heap_t *max_h = dynamic_array_max_heap_c(capacity, element_size);
    if(!max_h){
        // 存储分配失败
        return NULL;
    }

    max_heap_priority_queue_t *q = (max_heap_priority_queue_t *)malloc(sizeof(max_heap_priority_queue_t));
    if(!q){
        // 存储分配失败
        free(q);
        return NULL;
    }

    q->max_h = max_h;

    return q;
}

// 初始化队列，默认容量
max_heap_priority_queue_t *max_heap_priority_queue(int element_size)
{
    dynamic_array_max_heap_t *max_h = dynamic_array_max_heap(element_size);
    if(!max_h){
        // 存储分配失败
        return NULL;
    }

    max_heap_priority_queue_t *q = (max_heap_priority_queue_t *)malloc(sizeof(max_heap_priority_queue_t));
    if(!q){
        // 存储分配失败
        free(q);
        return NULL;
    }

    q->max_h = max_h;

    return q;
}

// 获取队列的元素个数
int max_heap_priority_queue_size(max_heap_priority_queue_t *q)
{
    if(q == NULL){
        exit(OVERFLOW);
    }

    return dynamic_array_max_heap_size(q->max_h);
}

// 判断队列是否为空
bool max_heap_priority_queue_is_empty(max_heap_priority_queue_t *q)
{
    if(q == NULL){
        exit(OVERFLOW);
    }

    return dynamic_array_max_heap_is_empty(q->max_h) == 0;
}

// 获取队列的容积
int max_heap_priority_queue_capacity(max_heap_priority_queue_t *q)
{
    if(q == NULL){
        exit(OVERFLOW);
    }

    return dynamic_array_max_heap_capacity(q->max_h);
}

// 入队
Status max_heap_priority_queue_enqueue(max_heap_priority_queue_t *q, void *e, compare_s compare_t)
{
    if(q == NULL){
        exit(OVERFLOW);
    }

    Status ok = dynamic_array_max_heap_add(q->max_h, e, compare_t);
    if(!ok){
        return ERROR;
    }

    return OK;
}

// 出队
Status max_heap_priority_queue_dequeue(max_heap_priority_queue_t *q, void *ret, compare_s compare_t)
{
    if(q == NULL){
        exit(OVERFLOW);
    }

    void *r = dynamic_array_max_heap_extract_max(q->max_h, ret, compare_t);
    if(r == NULL){
        return ERROR;
    }

    return OK;
}

// 查看队首的元素
Status max_heap_priority_queue_front(max_heap_priority_queue_t *q, void *ret)
{
    if(q == NULL){
        exit(OVERFLOW);
    }

    void *r = dynamic_array_max_heap_find_max(q->max_h, ret);
    if(r == NULL){
        return ERROR;
    }

    return OK;
}

// 清空队列
Status max_heap_priority_queue_clear(max_heap_priority_queue_t *q)
{
    if(q == NULL){
        exit(OVERFLOW);
    }

    dynamic_array_max_heap_clear(q->max_h);

    return OK;
}

// 销毁队列
Status max_heap_priority_queue_destroy(max_heap_priority_queue_t **q)
{
    if(*q == NULL){
        exit(OVERFLOW);
    }

    dynamic_array_max_heap_destroy(&((*q)->max_h));

    free(*q);
    *q = NULL;

    return OK;
}