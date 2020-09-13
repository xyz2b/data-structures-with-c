//
// Created by 焦宏宇 on 2020/2/8.
//

#include "loop_queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 初始化循环队列 with capacity
loop_queue_t *loop_queue_c(int capacity, int element_size)
{
    loop_queue_t *loop_q = (loop_queue_t *)malloc(sizeof(loop_queue_t));
    void *arr = (char *)basic_array_c(capacity + 1, element_size);

    if(!loop_q || !arr){
        // 存储分配失败
        free(loop_q);
        basic_array_destroy(&arr);
        return NULL;
    }

    loop_q->capacity = capacity;
    loop_q->element_size = element_size;

    loop_q->data = arr;
    loop_q->size = 0;
    loop_q->front = loop_q->tail = 0;

    return loop_q;
}

// 初始化循环队列，默认capacity
loop_queue_t *loop_queue(int element_size)
{
    loop_queue_t *loop_q = loop_queue_c(DEFAULTCAPACITY, element_size);
    if(!loop_q){
        return NULL;
    }

    return loop_q;
}

// 获取循环队列的元素个数
int loop_queue_size(loop_queue_t *loop_q)
{
    if(loop_q == NULL){
        exit(OVERFLOW);
    }

    return loop_q->size;
}

// 获取循环队列的容量
int loop_queue_capacity(loop_queue_t *loop_q)
{
    if(loop_q == NULL){
        exit(OVERFLOW);
    }

    return loop_q->capacity;
}

// 循环队列是否为空
bool loop_queue_is_empty(loop_queue_t *loop_q)
{
    if(loop_q == NULL){
        exit(OVERFLOW);
    }

    return loop_q->front == loop_q->tail;
}

// 调整数组capacity
Status loop_queue_resize(loop_queue_t *loop_q, int new_capacity)
{
    void *arr = (char *)basic_array_c(new_capacity + 1, loop_q->element_size);
    if(!arr)  // 存储分配失败
        return ERROR;

    for (int i = 0; i < loop_q->size; i++) {
        basic_array_copy(loop_q->data, arr, (i + loop_q->front) % (loop_q->capacity + 1), i, loop_q->element_size);
    }


    basic_array_destroy(&(loop_q->data));
    loop_q->data = NULL;

    loop_q->data = arr;
    loop_q->capacity = new_capacity;

    loop_q->front = 0;
    loop_q->tail = loop_q->size;

    return OK;
}

// 入队
Status loop_queue_enqueue(loop_queue_t *loop_q, void *e)
{
    if(loop_q == NULL){
        // 循环队列不存在
        exit(OVERFLOW);
    }

    if((loop_q->tail + 1) % (loop_q->capacity + 1) == loop_q->front)
        // 队列已满，扩容
        loop_queue_resize(loop_q, 2 * loop_q->capacity);

    basic_array_elem_copy(loop_q->data, loop_q->element_size, loop_q->tail, e);

    loop_q->tail = (loop_q->tail + 1) % (loop_q->capacity + 1);
    loop_q->size ++;

    return OK;
}

// 出队，出队元素存在ret中
Status loop_queue_dequeue(loop_queue_t *loop_q, void *ret)
{
    if(loop_q == NULL){
        exit(OVERFLOW);
    }

    if(loop_queue_is_empty(loop_q))
        // 队列为空
        exit(OVERFLOW);

    void *elem = basic_array_get_elem(loop_q->data, loop_q->element_size, loop_q->front, NULL);
    memcpy(ret, elem, loop_q->element_size);

    loop_q->front = (loop_q->front + 1) % (loop_q->capacity + 1);
    loop_q->size --;

    if(loop_q->size == loop_q->capacity/4 && loop_q->capacity/2 != 0)
        // 数组使用量等于capacity/4，缩容1/2(防止复杂度震荡)
        loop_queue_resize(loop_q, loop_q->capacity/2);

    return OK;
}

// 查看队首的元素，存放在ret中
Status loop_queue_front(loop_queue_t *loop_q, void *ret)
{
    if(loop_q == NULL || ret == NULL){
        exit(OVERFLOW);
    }

    if(loop_queue_is_empty(loop_q))
        // 队列为空
        exit(OVERFLOW);

    void *elem = basic_array_get_elem(loop_q->data, loop_q->element_size, loop_q->front, NULL);
    memcpy(ret, elem, loop_q->element_size);

    return OK;
}


// 清空队列
Status loop_queue_clear(loop_queue_t *loop_q)
{
    if(loop_q == NULL){
        exit(OVERFLOW);
    }

    loop_q->size = 0;
    return OK;
}

// 销毁数组
Status loop_queue_destroy(loop_queue_t **loop_q)
{
    if(*loop_q == NULL){
        exit(OVERFLOW);
    }

    basic_array_destroy(&(*loop_q)->data);

    (*loop_q)->data = NULL;
    (*loop_q)->size = 0;
    (*loop_q)->capacity = 0;
    (*loop_q)->front = (*loop_q)->tail = 0;

    free(*loop_q);

    *loop_q = NULL;

    return OK;
}

// 查看队列信息，需要传入调用方定义的将调用方自定义的类型转换成数组的函数to_string
void loop_queue_show(loop_queue_t *loop_q, to_string_s to_string_t)
{
    if(loop_q == NULL){
        exit(OVERFLOW);
    }

    void *ret = (char *)malloc(loop_q->element_size);
    if(!ret)  // 存储分配失败
        exit(OVERFLOW);

    printf("Array: size = %d, capacity = %d, elem_size = %d\n", loop_q->size, loop_q->capacity, loop_q->element_size);
    printf("front [");

    for(int i = loop_q->front; i != loop_q->tail; i = (i + 1) % (loop_q->capacity + 1))
    {
        // TODO: 解决类型转换后接收字符串的数组buffer容量大小固定问题
        char buffer[200];

        void *elem = basic_array_get_elem(loop_q->data, loop_q->element_size, i, NULL);
        memcpy(ret, elem, loop_q->element_size);

        int ok = (*to_string_t)(ret, buffer);
        if(ok != OK){
            free(ret);
            exit(ERROR);
        }
        if((i + 1) % (loop_q->capacity + 1) != loop_q->tail){
            printf("%s, ", buffer);
        } else {
            printf("%s", buffer);
        }
    }

    printf("] tail\n");

    free(ret);
}