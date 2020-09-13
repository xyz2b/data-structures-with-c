//
// Created by 焦宏宇 on 2020/2/9.
//

#include "linked_list_queue.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

// 创建队列
linked_list_queue_t *linked_list_queue(int data_size)
{
    linked_list_queue_t *linked_list_q = (linked_list_queue_t *)malloc(sizeof(linked_list_queue_t));

    if(!linked_list_q){
        // 存储分配失败
        return NULL;
    }

    linked_list_q->head = NULL;
    linked_list_q->tail = NULL;
    linked_list_q->size = 0;
    linked_list_q->data_size = data_size;

    return linked_list_q;
}

// 获取队列的元素个数
int linked_list_queue_size(linked_list_queue_t *linked_list_q)
{
    if(linked_list_q == NULL){
        exit(OVERFLOW);
    }

    return linked_list_q->size;
}

// 判断队列是否为空
bool linked_list_queue_is_empty(linked_list_queue_t *linked_list_q)
{
    if(linked_list_q == NULL){
        exit(OVERFLOW);
    }

    return linked_list_q->size == 0;
}

// 入队
Status linked_list_queue_enqueue(linked_list_queue_t *linked_list_q, void *e)
{
    if(linked_list_q == NULL){
        exit(OVERFLOW);
    }

    if(linked_list_q->tail == NULL){
        linked_list_q->tail = node_e(linked_list_q->data_size, e);
        linked_list_q->head = linked_list_q->tail;
    } else {
        linked_list_q->tail->next = node_e(linked_list_q->data_size, e);
        linked_list_q->tail = linked_list_q->tail->next;
    }
    linked_list_q->size ++;

    return OK;
}

// 出队
Status linked_list_queue_dequeue(linked_list_queue_t *linked_list_q, void *ret)
{
    if(linked_list_q == NULL){
        exit(OVERFLOW);
    }

    if(linked_list_queue_is_empty(linked_list_q)){
        exit(OVERFLOW);
    }

    node_s *n = linked_list_q->head;
    linked_list_q->head = linked_list_q->head->next;
    n->next = NULL;
    if(linked_list_q->head == NULL)
        linked_list_q->tail = NULL;
    linked_list_q->size --;

    void *elem = n->data;
    memcpy(ret, elem, n->data_size);
    node_destroy(&n);

    return OK;
}

// 查看队首的元素
Status linked_list_queue_front(linked_list_queue_t *linked_list_q, void *ret)
{
    if(linked_list_q == NULL){
        exit(OVERFLOW);
    }

    void *elem = linked_list_q->head->data;
    memcpy(ret, elem, linked_list_q->data_size);

    return OK;
}

// 查看队列
Status linked_list_queue_show(linked_list_queue_t *linked_list_q, to_string_s to_string_t)
{
    if(linked_list_q == NULL){
        exit(OVERFLOW);
    }

    printf("%s", "Queue: front ");
    node_s *cur = linked_list_q->head;
    while (cur != NULL){
        node_show(cur, to_string_t);
        printf("%s", "->");
        cur = cur->next;
    }
    printf("%s\n", "NULL tail");

    return OK;
}

// 清空队列
Status linked_list_queue_clear(linked_list_queue_t *linked_list_q)
{
    if(linked_list_q == NULL){
        return OVERFLOW;
    }

    node_s *cur = linked_list_q->head;
    while (cur != NULL){
        node_s *temp = cur->next;
        node_destroy(&cur);
        cur = temp;
    }
    linked_list_q->head = NULL;
    linked_list_q->tail = NULL;
    linked_list_q->size = 0;

    return OK;
}

// 销毁队列
Status linked_list_queue_destroy(linked_list_queue_t **linked_list_q)
{
    if(linked_list_q == NULL){
        return OVERFLOW;
    }

    linked_list_queue_clear(*linked_list_q);
    free(*linked_list_q);
    *linked_list_q = NULL;

    return OK;
}