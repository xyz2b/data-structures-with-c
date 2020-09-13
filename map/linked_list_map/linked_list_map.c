//
// Created by 焦宏宇 on 2020/2/15.
//

#include "linked_list_map.h"
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

// 创建node with next and key and value
linked_list_map_node_s *linked_list_map_node_n_k_v(linked_list_map_node_s *next, int *key, int key_data_size, void *value, int value_data_size)
{
    linked_list_map_node_s *n = (linked_list_map_node_s *)malloc(sizeof(linked_list_map_node_s));
    void *k = (char *)malloc(key_data_size);
    void *v = (char *)malloc(value_data_size);

    if(!n || !k || ! v){
        // 存储分配失败
        free(n);
        free(k);
        free(v);
        return NULL;
    }

    if(key != NULL)
        memcpy(k, key, key_data_size);
    if(value != NULL)
        memcpy(v, value, value_data_size);

    n->key = k;
    n->value = v;
    n->next = next;
    n->key_data_size = key_data_size;
    n->value_data_size = value_data_size;

    return n;
}

// 创建node with key
linked_list_map_node_s *linked_list_map_node_k(int *key, int key_data_size, int value_data_size)
{
    linked_list_map_node_s *n = (linked_list_map_node_s *)malloc(sizeof(linked_list_map_node_s));
    void *k = (char *)malloc(key_data_size);

    if(!n || !k){
        // 存储分配失败
        free(n);
        free(k);
        return NULL;
    }

    memcpy(k, key, key_data_size);

    n->key = k;
    n->value = NULL;
    n->next = NULL;
    n->key_data_size = key_data_size;
    n->value_data_size = value_data_size;

    return n;
}

// 创建node without any
linked_list_map_node_s *linked_list_map_node(int key_data_size, int value_data_size)
{
    linked_list_map_node_s *n = (linked_list_map_node_s *)malloc(sizeof(linked_list_map_node_s));

    if(!n){
        // 存储分配失败
        free(n);
        return NULL;
    }


    n->key = NULL;
    n->value = NULL;
    n->key_data_size = key_data_size;
    n->value_data_size = value_data_size;
    n->next = NULL;

    return n;
}

// 查看node
Status linked_list_map_node_show(linked_list_map_node_s *n, to_string_s to_string_t)
{
    if(n == NULL){
        return OVERFLOW;
    }

    char buffer[200];

    (*to_string_t)(n->key, buffer);
    printf("%s: ", buffer);
    (*to_string_t)(n->value, buffer);
    printf("%s", buffer);

    return OK;
}

// 销毁node
Status linked_list_map_node_destroy(linked_list_map_node_s **n)
{
    if(*n == NULL){
        return OVERFLOW;
    }

    free((*n)->key);
    free((*n)->value);

    (*n)->next = NULL;
    (*n)->key = NULL;
    (*n)->value = NULL;
    (*n)->key_data_size = 0;
    (*n)->value_data_size = 0;

    free(*n);
    *n = NULL;

    return OK;
}

// 创建映射
linked_list_map_t *linked_list_map(int key_data_size, int value_data_size)
{
    linked_list_map_t *linked_list_mp = (linked_list_map_t *)malloc(sizeof(linked_list_map_t));

    if(!linked_list_mp){
        // 存储分配失败
        return NULL;
    }

    linked_list_map_node_s *n = linked_list_map_node(key_data_size, value_data_size);

    linked_list_mp->size = 0;
    linked_list_mp->dummy_head = n;
    linked_list_mp->key_data_size = key_data_size;
    linked_list_mp->value_data_size = value_data_size;

    return linked_list_mp;
}

// 获取映射中元素个数
int linked_list_map_size(linked_list_map_t *linked_list_mp)
{
    if(linked_list_mp == NULL){
        return OVERFLOW;
    }

    return linked_list_mp->size;
}

// 判断映射是否为空
bool linked_list_map_is_empty(linked_list_map_t *linked_list_mp)
{
    if(linked_list_mp == NULL){
        return OVERFLOW;
    }

    return linked_list_mp->size == 0;
}

// 查找链表中是否有元素e
bool linked_list_map_contain(linked_list_map_t *linked_list_mp, void *key)
{
    if(linked_list_mp == NULL){
        exit(OVERFLOW);
    }

    for(linked_list_map_node_s *cur = linked_list_mp->dummy_head->next; cur != NULL; cur = cur->next){
        void *k = cur->key;
        if(memcmp(key, k, cur->key_data_size) == 0)
            return true;
    }

    return false;
}

// 获取key的节点
linked_list_map_node_s *linked_list_map_get_node(linked_list_map_t *linked_list_mp, linked_list_map_node_s *ret_node, void *key, compare_s compare_t)
{
    linked_list_map_node_s *cur = linked_list_mp->dummy_head->next;
    while (cur != NULL){
        if((*compare_t)(key, cur->key) == 0){
            // 将源链表中的节点复制一份新的，避免节点被销毁之后，指针指向不对，用于获取源链表中数据
            if(ret_node != NULL){
                memcpy(ret_node, cur, sizeof(linked_list_map_node_s));
                return ret_node;
            }
            // 获取源链表中的节点，节点销毁，数据即不存在，用于修改源链表中数据
            return cur;
        }
        cur = cur->next;
    }

    return NULL;
}

// 获取key对应的value
void *linked_list_map_get(linked_list_map_t *linked_list_mp, void *key, void *ret_value, compare_s compare_t)
{
    linked_list_map_node_s *linked_list_map_n = linked_list_map_node_n_k_v(NULL, key, linked_list_mp->key_data_size, NULL, linked_list_mp->value_data_size);
    // 单独赋值给一个指针的原因是，如果返回了NULL，直接赋值给上面创建的节点的指针，会导致上面创建的节点无法销毁
    linked_list_map_node_s *ret = linked_list_map_get_node(linked_list_mp, linked_list_map_n, key, compare_t);

    if(ret != NULL)
        memcpy(ret_value, ret->value, ret->value_data_size);

    linked_list_map_node_destroy(&linked_list_map_n);

    return ret_value;
}

// 如果key存在就更新value，如果key不存在就新添加
Status linked_list_map_add(linked_list_map_t *linked_list_mp, void *key, void *value, compare_s compare_t)
{
    linked_list_map_node_s *linked_list_map_n = linked_list_map_get_node(linked_list_mp, NULL, key, compare_t);

    if(linked_list_map_n == NULL){
        linked_list_mp->dummy_head->next = linked_list_map_node_n_k_v(linked_list_mp->dummy_head->next, key, linked_list_mp->key_data_size, value, linked_list_mp->value_data_size);
        linked_list_mp->size ++;
    }
    else {
        memcpy(linked_list_map_n->value, value, linked_list_map_n->value_data_size);
    }

    return OK;
}


// 修改key的value
Status linked_list_map_set(linked_list_map_t *linked_list_mp, void *key, void *value, compare_s compare_t)
{
    linked_list_map_node_s *linked_list_map_n = linked_list_map_get_node(linked_list_mp, NULL, key, compare_t);

    if(linked_list_map_n == NULL){
        exit(OVERFLOW);
    }

    memcpy(linked_list_map_n->value, value, linked_list_map_n->value_data_size);

    return OK;
}

// 删除key，返回value
void *linked_list_map_remove(linked_list_map_t *linked_list_mp, void *key, void *ret_value, compare_s compare_t)
{
    if(linked_list_mp == NULL){
        exit(OVERFLOW);
    }

    linked_list_map_node_s *prev = linked_list_mp->dummy_head;
    while(prev->next != NULL){
        if((*compare_t)(key, prev->next->key) == 0){
            break;
        }
        prev = prev->next;
    }

    if(prev->next != NULL){
        linked_list_map_node_s *del_node = prev->next;
        prev->next = del_node->next;
        del_node->next = NULL;
        linked_list_mp->size --;

        memcpy(ret_value, del_node->value, del_node->value_data_size);

        linked_list_map_node_destroy(&del_node);

        return ret_value;
    }

    return NULL;
}

// 查看映射
Status linked_list_map_show(linked_list_map_t *linked_list_mp, to_string_s to_string_t)
{
    if(linked_list_mp == NULL){
        exit(OVERFLOW);
    }

    linked_list_map_node_s *cur = linked_list_mp->dummy_head->next;
    while (cur != NULL){
        linked_list_map_node_show(cur, to_string_t);
        printf("\n");
        cur = cur->next;
    }

    return OK;
}

// 将链表清空
Status linked_list_map_clear(linked_list_map_t *linked_list_mp)
{
    if(linked_list_mp == NULL){
        return OVERFLOW;
    }

    linked_list_map_node_s *cur = linked_list_mp->dummy_head->next;
    while (cur != NULL){
        linked_list_map_node_s *temp = cur->next;
        linked_list_map_node_destroy(&cur);
        cur = temp;
    }

    linked_list_mp->dummy_head->next = NULL;
    linked_list_mp->size = 0;

    return OK;
}

// 销毁链表
Status linked_list_map_destroy(linked_list_map_t **linked_list_mp)
{
    if(linked_list_mp == NULL){
        return OVERFLOW;
    }

    linked_list_map_clear(*linked_list_mp);
    linked_list_map_node_destroy(&((*linked_list_mp)->dummy_head));
    free(*linked_list_mp);
    *linked_list_mp = NULL;

    return OK;
}