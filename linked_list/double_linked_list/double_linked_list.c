//
// Created by 焦宏宇 on 2020/2/10.
//

#include "double_linked_list.h"
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

// 创建node with next and prev and e
double_node_s *double_node_n_p(double_node_s *next,double_node_s *prev, int data_size, void *e)
{
    double_node_s *n = (double_node_s *)malloc(sizeof(double_node_s));
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
double_node_s *double_node_p(double_node_s *prev, int data_size, void *e)
{
    double_node_s *n = (double_node_s *)malloc(sizeof(double_node_s));
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
double_node_s *double_node_n(double_node_s *next, int data_size, void *e)
{
    double_node_s *n = (double_node_s *)malloc(sizeof(double_node_s));
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
double_node_s *double_node_e(int data_size, void *e)
{
    double_node_s *n = (double_node_s *)malloc(sizeof(double_node_s));
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
double_node_s *double_node(int data_size)
{
    double_node_s *n = (double_node_s *)malloc(sizeof(double_node_s));

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
Status double_node_show(double_node_s *n, to_string_s to_string_t)
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
Status double_node_destroy(double_node_s **n)
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
double_linked_list_t *double_linked_list(int data_size)
{
    double_linked_list_t *double_linked_l = (double_linked_list_t *)malloc(sizeof(double_linked_list_t));

    if(!double_linked_l){
        // 存储分配失败
        return NULL;
    }

    double_node_s *n = double_node(data_size);

    double_linked_l->size = 0;
    double_linked_l->dummy_head = n;
    double_linked_l->data_size = data_size;

    return double_linked_l;
}

// 获取链表中元素个数
int double_linked_list_size(double_linked_list_t *double_linked_l)
{
    if(double_linked_l == NULL){
        return OVERFLOW;
    }

    return double_linked_l->size;
}

// 判断链表是否为空
bool double_linked_list_is_empty(double_linked_list_t *double_linked_l)
{
    if(double_linked_l == NULL){
        return OVERFLOW;
    }

    return double_linked_l->size == 0;
}

// 在链表索引为index的位置插入新元素e
Status double_linked_list_insert(double_linked_list_t *double_linked_l, int index, void *e)
{
    if(double_linked_l == NULL){
        return OVERFLOW;
    }

    if(index < 0 || index > double_linked_l->size){
        return OVERFLOW;
    }

    double_node_s *prev = double_linked_l->dummy_head;
    for(int i = 0; i < index; i ++){
        prev = prev->next;
    }

    double_node_s *n = double_node_n_p(prev->next, prev, double_linked_l->data_size, e);
    if(prev->next != NULL)
        prev->next->prev = n;
    prev->next = n;

    double_linked_l->size ++;

    return OK;
}

// 在链表头插入新元素e
Status double_linked_list_insert_first(double_linked_list_t *double_linked_l, void *e)
{
    if(double_linked_l == NULL){
        return OVERFLOW;
    }

    Status ok = double_linked_list_insert(double_linked_l, 0, e);
    if(ok == OVERFLOW){
        return OVERFLOW;
    }

    return OK;
}

// 在链表的末尾插入新元素e
Status double_linked_list_insert_last(double_linked_list_t *double_linked_l, void *e)
{
    int ok = double_linked_list_insert(double_linked_l, double_linked_l->size, e);
    if(ok == OVERFLOW){
        return OVERFLOW;
    }

    return OK;
}

// 获取链表第index位置的元素
Status double_linked_list_get(double_linked_list_t *double_linked_l, int index, void *ret)
{
    if(double_linked_l == NULL || ret == NULL){
        exit(OVERFLOW);
    }

    if(index < 0 || index >= double_linked_l->size)
        // index索引非法，需要0<=index<=size
        exit(OVERFLOW);

    double_node_s *cur = double_linked_l->dummy_head->next;
    for(int i = 0; i < index; i++){
        cur = cur->next;
    }

    void *elem = cur->data;
    memcpy(ret, elem, cur->data_size);

    return OK;
}

// 获取链表的第一个元素
Status double_linked_list_get_first(double_linked_list_t *double_linked_l, void *ret)
{
    double_linked_list_get(double_linked_l, 0, ret);

    return OK;
}

// 获取链表的最后一个元素
Status double_linked_list_get_last(double_linked_list_t *double_linked_l, void *ret)
{
    double_linked_list_get(double_linked_l, double_linked_l->size - 1, ret);

    return OK;
}

// 修改链表的第index位置的元素
Status double_linked_list_set(double_linked_list_t *double_linked_l, int index, void *e)
{
    if(double_linked_l == NULL){
        exit(OVERFLOW);
    }

    if(index < 0 || index >= double_linked_l->size)
        // index索引非法，需要0<=index<=size
        exit(OVERFLOW);

    double_node_s *cur = double_linked_l->dummy_head->next;
    for(int i = 0; i < index; i++){
        cur = cur->next;
    }

    void *elem = cur->data;
    memcpy(elem, e, cur->data_size);

    return OK;
}

// 查找链表中是否有元素e
bool double_linked_list_contain(double_linked_list_t *double_linked_l, void *e)
{
    if(double_linked_l == NULL){
        exit(OVERFLOW);
    }

    for(double_node_s *cur = double_linked_l->dummy_head->next; cur != NULL; cur = cur->next){
        void *elem = cur->data;
        if(memcmp(e, elem, cur->data_size) == 0)
            return true;
    }

    return false;
}

// 查看链表
Status double_linked_list_show(double_linked_list_t *double_linked_l, to_string_s to_string_t)
{
    if(double_linked_l == NULL){
        exit(OVERFLOW);
    }

    double_node_s *cur = double_linked_l->dummy_head->next;
    while (cur != NULL){
        double_node_show(cur, to_string_t);
        printf("%s", "<->");
        cur = cur->next;
    }
    printf("%s\n", "NULL");

    return OK;
}

// 删除链表index位置的元素
Status double_linked_list_remove(double_linked_list_t *double_linked_l, int index, void *ret)
{
    if(double_linked_l == NULL){
        return OVERFLOW;
    }

    if(index < 0 || index > double_linked_l->size){
        return OVERFLOW;
    }

    double_node_s *cur = double_linked_l->dummy_head->next;
    for(int i = 0; i < index; i ++){
        cur = cur->next;
    }

    cur->prev->next = cur->next;
    cur->next->prev = cur->prev;

    cur->next = NULL;
    cur->prev = NULL;
    double_linked_l->size --;

    void *elem = cur->data;
    memcpy(ret, elem, cur->data_size);
    double_node_destroy(&cur);

    return OK;
}

// 删除链表第一个元素
Status double_linked_list_remove_first(double_linked_list_t *double_linked_l, void *ret)
{
    Status ok = double_linked_list_remove(double_linked_l, 0, ret);
    if(ok == OVERFLOW)
        return OVERFLOW;

    return OK;
}

// 删除链表的最后一个元素
Status double_linked_list_remove_last(double_linked_list_t *double_linked_l, void *ret)
{
    Status ok = double_linked_list_remove(double_linked_l, double_linked_l->size - 1, ret);
    if(ok == OVERFLOW)
        return OVERFLOW;

    return OK;
}

// 将链表清空
Status double_linked_list_clear(double_linked_list_t *double_linked_l)
{
    if(double_linked_l == NULL){
        return OVERFLOW;
    }

    double_node_s *cur = double_linked_l->dummy_head->next;
    while (cur != NULL){
        double_node_s *temp = cur->next;
        double_node_destroy(&cur);
        cur = temp;
    }

    double_linked_l->dummy_head->next = NULL;

    double_linked_l->size = 0;

    return OK;
}

// 销毁链表
Status double_linked_list_destroy(double_linked_list_t **double_linked_l)
{
    if(double_linked_l == NULL){
        return OVERFLOW;
    }

    double_linked_list_clear(*double_linked_l);
    double_node_destroy(&((*double_linked_l)->dummy_head));
    free(*double_linked_l);
    *double_linked_l = NULL;

    return OK;
}