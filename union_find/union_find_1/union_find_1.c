//
// Created by 焦宏宇 on 2020/2/20.
//

#include "union_find_1.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// 初始化并查集
union_find_1_t *union_find_1(int size, int elem_size)
{
    union_find_1_t *union_f = (union_find_1_t *)malloc(sizeof(union_find_1_t));

    void *id = (char *)malloc(size * elem_size);
    if(!union_f || !id){
        free(union_f);
        free(id);
        exit(OVERFLOW);
    }

//    int arr[size];
//    for(int i = 0; i < size; i ++){
//        arr[i] = i;
//    }
//    memcpy(id, arr, size * elem_size);


    for(int i = 0; i < size; i ++){
        memcpy(id + i * elem_size, &i, elem_size);
    }

    union_f->id = id;
    union_f->size = size;
    union_f->elem_size = elem_size;

    return union_f;
}

// 查看并查集的大小
int union_find_1_size(union_find_1_t *union_f)
{
    return union_f->size;
}

// 查找元素所属的集合ID
void *union_find_1_find(union_find_1_t *union_f, int p, void *id)
{
    if(p < 0 || p >= union_f->size)
    {
        exit(OVERFLOW);
    }
    void *p_id = union_f->id + p * union_f->elem_size;
    if(id != NULL){
        memcpy(id, p_id, union_f->elem_size);
        return id;
    }

    return p_id;
}

// 查询两个元素是否同属于一个集合
bool union_find_1_is_connected(union_find_1_t *union_f, int p, int q)
{
    return memcmp(union_find_1_find(union_f, p, NULL), union_find_1_find(union_f, q, NULL), union_f->elem_size) == 0;
}

// 对元素p和元素q执行union操作
Status union_find_1_union(union_find_1_t *union_f, int p, int q)
{
    void *p_id = union_find_1_find(union_f, p, NULL);
    void *q_id = union_find_1_find(union_f, q, NULL);

    if(p_id == q_id)
        return OK;

    for(int i = 0; i < union_f->size; i++){ // if(id[i] == q_id){id[i] = p_id; }
        if(memcmp(union_f->id + i * union_f->elem_size, q_id, union_f->elem_size) == 0){
            memcpy(union_f->id + i *union_f->elem_size, p_id, union_f->elem_size);
            int t = *(int*)(union_f->id + i *union_f->elem_size);
        }
    }
    return OK;
}


