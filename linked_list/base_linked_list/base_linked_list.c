//
// Created by 焦宏宇 on 2020/2/8.
//

#include "base_linked_list.h"
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

// 创建node with next and e
node_s *node_n(node_s *next, int data_size, void *e)
{
    node_s *n = (node_s *)malloc(sizeof(node_s));
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
    n->data_size = data_size;

    return n;
}

// 创建node without next and with e
node_s *node_e(int data_size, void *e)
{
    node_s *n = (node_s *)malloc(sizeof(node_s));
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
    n->data_size = data_size;

    return n;
}

// 创建node without next and e
node_s *node(int data_size)
{
    node_s *n = (node_s *)malloc(sizeof(node_s));

    if(!n){
        // 存储分配失败
        free(n);
        return NULL;
    }

    n->data = NULL;
    n->next = NULL;
    n->data_size = data_size;

    return n;
}

// 查看node
Status node_show(node_s *n, to_string_s to_string_t)
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
Status node_destroy(node_s **n)
{
    if(*n == NULL){
        return OVERFLOW;
    }

    free((*n)->data);

    (*n)->next = NULL;
    (*n)->data = NULL;
    (*n)->data_size = 0;

    free(*n);
    *n = NULL;

    return OK;
}

// 创建链表
linked_list_t *linked_list(int data_size)
{
    linked_list_t *linked_l = (linked_list_t *)malloc(sizeof(linked_list_t));

    if(!linked_l){
        // 存储分配失败
        return NULL;
    }

    node_s *n = node(data_size);

    linked_l->size = 0;
    linked_l->dummy_head = n;
    linked_l->data_size = data_size;

    return linked_l;
}

// 获取链表中元素个数
int linked_list_size(linked_list_t *linked_l)
{
    if(linked_l == NULL){
        return OVERFLOW;
    }

    return linked_l->size;
}

// 判断链表是否为空
bool linked_list_is_empty(linked_list_t *linked_l)
{
    if(linked_l == NULL){
        return OVERFLOW;
    }

    return linked_l->size == 0;
}

// 在链表索引为index的位置插入新元素e
Status linked_list_insert(linked_list_t *linked_l, int index, void *e)
{
    if(linked_l == NULL){
        return OVERFLOW;
    }

    if(index < 0 || index > linked_l->size){
        return OVERFLOW;
    }

    node_s *prev = linked_l->dummy_head;
    for(int i = 0; i < index; i ++){
        prev = prev->next;
    }

//    node_s *n = node_e(e);
//    n->next = prev->next;
//    prev->next = n;
    prev->next = node_n(prev->next, linked_l->data_size, e);
    linked_l->size ++;

    return OK;
}

// 在链表头插入新元素e
Status linked_list_insert_first(linked_list_t *linked_l, void *e)
{
    if(linked_l == NULL){
        return OVERFLOW;
    }

    Status ok = linked_list_insert(linked_l, 0, e);
    if(ok == OVERFLOW){
        return OVERFLOW;
    }

    return OK;
}

// 在链表的末尾插入新元素e
Status linked_list_insert_last(linked_list_t *linked_l, void *e)
{
    int ok = linked_list_insert(linked_l, linked_l->size, e);
    if(ok == OVERFLOW){
        return OVERFLOW;
    }

    return OK;
}

// 获取链表第index位置的元素
Status linked_list_get(linked_list_t *linked_l, int index, void *ret)
{
    if(linked_l == NULL || ret == NULL){
        exit(OVERFLOW);
    }

    if(index < 0 || index >= linked_l->size)
        // index索引非法，需要0<=index<=size
        exit(OVERFLOW);

    node_s *cur = linked_l->dummy_head->next;
    for(int i = 0; i < index; i++){
        cur = cur->next;
    }

    void *elem = cur->data;
    memcpy(ret, elem, cur->data_size);

    return OK;
}

// 获取链表的第一个元素
Status linked_list_get_first(linked_list_t *linked_l, void *ret)
{
    linked_list_get(linked_l, 0, ret);

    return OK;
}

// 获取链表的最后一个元素
Status linked_list_get_last(linked_list_t *linked_l, void *ret)
{
    linked_list_get(linked_l, linked_l->size - 1, ret);

    return OK;
}

// 修改链表的第index位置的元素
Status linked_list_set(linked_list_t *linked_l, int index, void *e)
{
    if(linked_l == NULL){
        exit(OVERFLOW);
    }

    if(index < 0 || index >= linked_l->size)
        // index索引非法，需要0<=index<=size
        exit(OVERFLOW);

    node_s *cur = linked_l->dummy_head->next;
    for(int i = 0; i < index; i++){
        cur = cur->next;
    }

    void *elem = cur->data;
    memcpy(elem, e, cur->data_size);

    return OK;
}

// 查找链表中是否有元素e
bool linked_list_contain(linked_list_t *linked_l, void *e)
{
    if(linked_l == NULL){
        exit(OVERFLOW);
    }

    for(node_s *cur = linked_l->dummy_head->next; cur != NULL; cur = cur->next){
        void *elem = cur->data;
        if(memcmp(e, elem, cur->data_size) == 0)
            return true;
    }

    return false;
}

// 查看链表
Status linked_list_show(linked_list_t *linked_l, to_string_s to_string_t)
{
    if(linked_l == NULL){
        exit(OVERFLOW);
    }

    node_s *cur = linked_l->dummy_head->next;
    while (cur != NULL){
        node_show(cur, to_string_t);
        printf("%s", "->");
        cur = cur->next;
    }
    printf("%s\n", "NULL");

    return OK;
}

// 删除链表index位置的元素
Status linked_list_remove(linked_list_t *linked_l, int index, void *ret)
{
    if(linked_l == NULL){
        return OVERFLOW;
    }

    if(index < 0 || index > linked_l->size){
        return OVERFLOW;
    }

    node_s *prev = linked_l->dummy_head;
    for(int i = 0; i < index; i ++){
        prev = prev->next;
    }

//    node_s *n = node_e(e);
//    n->next = prev->next;
//    prev->next = n;
    node_s *n = prev->next;
    prev->next = n->next;
    n->next = NULL;
    linked_l->size --;

    if(ret!=NULL){
        void *elem = n->data;
        memcpy(ret, elem, n->data_size);
    }
    node_destroy(&n);

    return OK;
}

// 删除链表第一个元素
Status linked_list_remove_first(linked_list_t *linked_l, void *ret)
{
    Status ok = linked_list_remove(linked_l, 0, ret);
    if(ok == OVERFLOW)
        return OVERFLOW;

    return OK;
}

// 删除链表的最后一个元素
Status linked_list_remove_last(linked_list_t *linked_l, void *ret)
{
    Status ok = linked_list_remove(linked_l, linked_l->size - 1, ret);
    if(ok == OVERFLOW)
        return OVERFLOW;

    return OK;
}

// 返回元素e的index
int linked_list_elem_index(linked_list_t *linked_l, void *e, compare_s compare_t)
{
    if(linked_l == NULL){
        return OVERFLOW;
    }

    node_s *cur = linked_l->dummy_head->next;
    for(int i = 0; i < linked_l->size; i ++){
        if((*compare_t)(e, cur->data) == 0){
            return i;
        }
        cur = cur->next;
    }

    return -1;
}

// 从链表中删除元素e
Status linked_list_remove_elem(linked_list_t *linked_l, void *e, compare_s compare_t)
{
    if(linked_l == NULL){
        return OVERFLOW;
    }

    node_s *prev = linked_l->dummy_head;
    while(prev->next != NULL){
        if((*compare_t)(e, prev->next->data) == 0){
            break;
        }
        prev = prev->next;
    }

    if(prev->next != NULL){
        node_s *del_node = prev->next;
        prev->next = del_node->next;
        del_node->next = NULL;
        linked_l->size --;

        node_destroy(&del_node);
    }

    return OK;
}

// 将链表清空
Status linked_list_clear(linked_list_t *linked_l)
{
    if(linked_l == NULL){
        return OVERFLOW;
    }

    node_s *cur = linked_l->dummy_head->next;
    while (cur != NULL){
        node_s *temp = cur->next;
        node_destroy(&cur);
        cur = temp;
    }

    linked_l->dummy_head->next = NULL;
    linked_l->size = 0;

    return OK;
}

// 销毁链表
Status linked_list_destroy(linked_list_t **linked_l)
{
    if(linked_l == NULL){
        return OVERFLOW;
    }

    linked_list_clear(*linked_l);
    node_destroy(&((*linked_l)->dummy_head));
    free(*linked_l);
    *linked_l = NULL;

    return OK;
}