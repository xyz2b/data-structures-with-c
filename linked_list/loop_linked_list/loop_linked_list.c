//
// Created by 焦宏宇 on 2020/2/10.
//

#include "loop_linked_list.h"
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

// 创建node with next and prev and e
loop_node_s *loop_node_n_p(loop_node_s *next,loop_node_s *prev, int data_size, void *e)
{
    loop_node_s *n = (loop_node_s *)malloc(sizeof(loop_node_s));
    void *elem = (char *)malloc(data_size);

    if(!n || !elem){
        // 存储分配失败
        free(n);
        free(elem);
        return NULL;
    }

    memcpy(elem, e, data_size);

    n->data = elem;
    n->next = next;
    n->prev = prev;
    n->data_size = data_size;

    return n;
}

// 创建node with prev and e
loop_node_s *loop_node_p(loop_node_s *prev, int data_size, void *e)
{
    loop_node_s *n = (loop_node_s *)malloc(sizeof(loop_node_s));
    void *elem = (char *)malloc(data_size);

    if(!n || !elem){
        // 存储分配失败
        free(n);
        free(elem);
        return NULL;
    }

    memcpy(elem, e, data_size);

    n->data = elem;
    n->next = NULL;
    n->prev = prev;
    n->data_size = data_size;

    return n;
}

// 创建node with next and e
loop_node_s *loop_node_n(loop_node_s *next, int data_size, void *e)
{
    loop_node_s *n = (loop_node_s *)malloc(sizeof(loop_node_s));
    void *elem = (char *)malloc(data_size);

    if(!n || !elem){
        // 存储分配失败
        free(n);
        free(elem);
        return NULL;
    }

    memcpy(elem, e, data_size);

    n->data = elem;
    n->next = next;
    n->prev = NULL;
    n->data_size = data_size;

    return n;
}

// 创建node with e
loop_node_s *loop_node_e(int data_size, void *e)
{
    loop_node_s *n = (loop_node_s *)malloc(sizeof(loop_node_s));
    void *elem = (char *)malloc(data_size);

    if(!n || !elem){
        // 存储分配失败
        free(n);
        free(elem);
        return NULL;
    }

    memcpy(elem, e, data_size);

    n->data = elem;
    n->next = NULL;
    n->prev = NULL;
    n->data_size = data_size;

    return n;
}

// 创建node without next and e
loop_node_s *loop_node(int data_size)
{
    loop_node_s *n = (loop_node_s *)malloc(sizeof(loop_node_s));

    if(!n){
        // 存储分配失败
        free(n);
        return NULL;
    }

    n->data = NULL;
    n->next = NULL;
    n->prev = NULL;
    n->data_size = data_size;

    return n;
}

// 查看node
Status loop_node_show(loop_node_s *n, to_string_s to_string_t)
{
    if(n == NULL){
        return OVERFLOW;
    }

    char buffer[200];

    (*to_string_t)(n->data, buffer);
    printf("%s", buffer);

    return OK;
}

// 销毁node
Status loop_node_destroy(loop_node_s **n)
{
    if(*n == NULL){
        return OVERFLOW;
    }

    free((*n)->data);

    (*n)->next = NULL;
    (*n)->prev = NULL;
    (*n)->data = NULL;
    (*n)->data_size = 0;

    free(*n);
    *n = NULL;

    return OK;
}

// 创建链表
loop_linked_list_t *loop_linked_list(int data_size)
{
    loop_linked_list_t *loop_linked_l = (loop_linked_list_t *)malloc(sizeof(loop_linked_list_t));

    if(!loop_linked_l){
        // 存储分配失败
        return NULL;
    }

    loop_node_s *n = loop_node(data_size);

    loop_linked_l->size = 0;
    loop_linked_l->dummy_head = n;
    loop_linked_l->dummy_head->prev = n;
    loop_linked_l->dummy_head->next = n;
    loop_linked_l->data_size = data_size;

    return loop_linked_l;
}

// 获取链表中元素个数
int loop_linked_list_size(loop_linked_list_t *loop_linked_l)
{
    if(loop_linked_l == NULL){
        return OVERFLOW;
    }

    return loop_linked_l->size;
}

// 判断链表是否为空
bool loop_linked_list_is_empty(loop_linked_list_t *loop_linked_l)
{
    if(loop_linked_l == NULL){
        return OVERFLOW;
    }

    return loop_linked_l->size == 0;
}

// 在链表索引为index的位置插入新元素e
Status loop_linked_list_insert(loop_linked_list_t *loop_linked_l, int index, void *e)
{
    if(loop_linked_l == NULL){
        return OVERFLOW;
    }

    if(index < 0 || index > loop_linked_l->size){
        return OVERFLOW;
    }

    if(index <= loop_linked_l->size / 2){
        loop_node_s *prev = loop_linked_l->dummy_head;
        for(int i = 0; i < index; i ++){
            prev = prev->next;
        }

        loop_node_s *n = loop_node_n_p(prev->next, prev, loop_linked_l->data_size, e);
        prev->next->prev = n;
        prev->next = n;

        loop_linked_l->size ++;

        return OK;
    } else {
        loop_node_s *prev = loop_linked_l->dummy_head;
        for(int i = 0; i < loop_linked_l->size - index - 1; i ++){
            prev = prev->prev;
        }

        loop_node_s *n = loop_node_n_p(prev->next, prev, loop_linked_l->data_size, e);
        prev->next->prev = n;
        prev->next = n;

        loop_linked_l->size ++;

        return OK;
    }


}

// 在链表头插入新元素e
Status loop_linked_list_insert_first(loop_linked_list_t *loop_linked_l, void *e)
{
    if(loop_linked_l == NULL){
        return OVERFLOW;
    }

    Status ok = loop_linked_list_insert(loop_linked_l, 0, e);
    if(ok == OVERFLOW){
        return OVERFLOW;
    }

    return OK;
}

// 在链表的末尾插入新元素e
Status loop_linked_list_insert_last(loop_linked_list_t *loop_linked_l, void *e)
{
    int ok = loop_linked_list_insert(loop_linked_l, loop_linked_l->size, e);
    if(ok == OVERFLOW){
        return OVERFLOW;
    }

    return OK;
}

// 获取链表第index位置的元素
Status loop_linked_list_get(loop_linked_list_t *loop_linked_l, int index, void *ret)
{
    if(loop_linked_l == NULL || ret == NULL){
        exit(OVERFLOW);
    }

    if(index < 0 || index >= loop_linked_l->size)
        // index索引非法，需要0<=index<=size
        exit(OVERFLOW);

    if(index <= loop_linked_l->size / 2) {
        loop_node_s *cur = loop_linked_l->dummy_head->next;
        for (int i = 0; i < index; i++) {
            cur = cur->next;
        }

        void *elem = cur->data;
        memcpy(ret, elem, cur->data_size);

        return OK;
    } else {
        loop_node_s *cur = loop_linked_l->dummy_head->prev;
        for (int i = 0; i < loop_linked_l->size - index - 1; i++) {
            cur = cur->next;
        }

        void *elem = cur->data;
        memcpy(ret, elem, cur->data_size);

        return OK;
    }
}

// 获取链表的第一个元素
Status loop_linked_list_get_first(loop_linked_list_t *loop_linked_l, void *ret)
{
    loop_linked_list_get(loop_linked_l, 0, ret);

    return OK;
}

// 获取链表的最后一个元素
Status loop_linked_list_get_last(loop_linked_list_t *loop_linked_l, void *ret)
{
    loop_linked_list_get(loop_linked_l, loop_linked_l->size - 1, ret);

    return OK;
}

// 修改链表的第index位置的元素
Status loop_linked_list_set(loop_linked_list_t *loop_linked_l, int index, void *e)
{
    if(loop_linked_l == NULL){
        exit(OVERFLOW);
    }

    if(index < 0 || index >= loop_linked_l->size)
        // index索引非法，需要0<=index<=size
        exit(OVERFLOW);

    if(index <= loop_linked_l->size / 2) {
        loop_node_s *cur = loop_linked_l->dummy_head->next;
        for (int i = 0; i < index; i++) {
            cur = cur->next;
        }

        void *elem = cur->data;
        memcpy(elem, e, cur->data_size);

        return OK;
    } else {
        loop_node_s *cur = loop_linked_l->dummy_head->prev;
        for (int i = 0; i < loop_linked_l->size - index - 1; i++) {
            cur = cur->next;
        }

        void *elem = cur->data;
        memcpy(elem, e, cur->data_size);

        return OK;
    }
}

// 查找链表中是否有元素e
bool loop_linked_list_contain(loop_linked_list_t *loop_linked_l, void *e)
{
    if(loop_linked_l == NULL){
        exit(OVERFLOW);
    }

    for(loop_node_s *cur = loop_linked_l->dummy_head->next; cur != loop_linked_l->dummy_head; cur = cur->next){
        void *elem = cur->data;
        if(memcmp(e, elem, cur->data_size) == 0)
            return true;
    }

    return false;
}

// 查看链表
Status loop_linked_list_show(loop_linked_list_t *loop_linked_l, to_string_s to_string_t)
{
    if(loop_linked_l == NULL){
        exit(OVERFLOW);
    }

    printf("loop linked list, size: %d, data_size: %d\n", loop_linked_l->size, loop_linked_l->data_size);
    printf("head <-> ");

    loop_node_s *cur = loop_linked_l->dummy_head->next;

    while (cur != loop_linked_l->dummy_head){
        loop_node_show(cur, to_string_t);
        printf("%s", " <-> ");
        cur = cur->next;
    }

    if(cur == loop_linked_l->dummy_head)
        printf("%s", "head");

    printf("\n");

    return OK;
}

// 删除链表index位置的元素
Status loop_linked_list_remove(loop_linked_list_t *loop_linked_l, int index, void *ret)
{
    if(loop_linked_l == NULL){
        return OVERFLOW;
    }

    if(index < 0 || index > loop_linked_l->size){
        return OVERFLOW;
    }
    if(index <= loop_linked_l->size / 2) {
        loop_node_s *cur = loop_linked_l->dummy_head->next;
        for (int i = 0; i < index; i++) {
            cur = cur->next;
        }

        cur->prev->next = cur->next;
        cur->next->prev = cur->prev;

        cur->next = NULL;
        cur->prev = NULL;
        loop_linked_l->size--;

        void *elem = cur->data;
        memcpy(ret, elem, cur->data_size);
        loop_node_destroy(&cur);

        return OK;
    } else {
        loop_node_s *cur = loop_linked_l->dummy_head->prev;
        for (int i = 0; i < loop_linked_l->size - index - 1; i++) {
            cur = cur->prev;
        }

        cur->prev->next = cur->next;
        cur->next->prev = cur->prev;

        cur->next = NULL;
        cur->prev = NULL;
        loop_linked_l->size--;

        void *elem = cur->data;
        memcpy(ret, elem, cur->data_size);
        loop_node_destroy(&cur);

        return OK;
    }
}

// 删除链表第一个元素
Status loop_linked_list_remove_first(loop_linked_list_t *loop_linked_l, void *ret)
{
    Status ok = loop_linked_list_remove(loop_linked_l, 0, ret);
    if(ok == OVERFLOW)
        return OVERFLOW;

    return OK;
}

// 删除链表的最后一个元素
Status loop_linked_list_remove_last(loop_linked_list_t *loop_linked_l, void *ret)
{
    Status ok = loop_linked_list_remove(loop_linked_l, loop_linked_l->size - 1, ret);
    if(ok == OVERFLOW)
        return OVERFLOW;

    return OK;
}

// 将链表清空
Status loop_linked_list_clear(loop_linked_list_t *loop_linked_l)
{
    if(loop_linked_l == NULL){
        return OVERFLOW;
    }

    loop_node_s *cur = loop_linked_l->dummy_head->next;
    while (cur != loop_linked_l->dummy_head){
        loop_node_s *temp = cur->next;
        loop_node_destroy(&cur);
        cur = temp;
    }
    loop_linked_l->dummy_head->next = loop_linked_l->dummy_head;
    loop_linked_l->dummy_head->prev = loop_linked_l->dummy_head;
    loop_linked_l->size = 0;

    return OK;
}

// 销毁链表
Status loop_linked_list_destroy(loop_linked_list_t **loop_linked_l)
{
    if(loop_linked_l == NULL){
        return OVERFLOW;
    }

    loop_linked_list_clear(*loop_linked_l);
    loop_node_destroy(&((*loop_linked_l)->dummy_head));
    free(*loop_linked_l);
    *loop_linked_l = NULL;

    return OK;
}