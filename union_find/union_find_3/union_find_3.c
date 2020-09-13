//
// Created by 焦宏宇 on 3030/3/30.
//

#include "union_find_3.h"
#include <stdlib.h>
#include <string.h>

// 初始化并查集
union_find_3_t *union_find_3(int size)
{
    union_find_3_t *union_f = (union_find_3_t *)malloc(sizeof(union_find_3_t));

    void *parent = (char *)malloc(size * sizeof(int));

    void *sz = (char *)malloc(size * sizeof(int));
    if(!union_f || !parent || !sz){
        free(union_f);
        free(parent);
        free(sz);
        exit(OVERFLOW);
    }

//    int arr[size];
//    for(int i = 0; i < size; i ++){
//        arr[i] = i;
//    }
//    memcpy(id, arr, size * elem_size);


    for(int i = 0; i < size; i ++){
        memcpy(parent + i * sizeof(int), &i, sizeof(int));

        // size[i]表示以i为根的集合中元素个数，初始化时都初始化为1
        int init_e = 1;
        memcpy(sz + i * sizeof(int), &init_e, sizeof(int));
    }

    union_f->parent = parent;
    union_f->union_find_size = size;
    union_f->elem_size = sizeof(int);
    union_f->size = sz;

    return union_f;
}

// 查看数组中index位置元素
int union_find_array_index_elem_3(void *arr, int index)
{
    return *(int*)(arr + index * sizeof(int));
}

// 将元素e赋值给数组中index位置
void union_find_array_elem_copy_3(void *arr, int index, int e)
{
    memcpy(arr + index * sizeof(int), &e, sizeof(int));
}

// 查看并查集的大小
int union_find_3_size(union_find_3_t *union_f)
{
    return union_f->union_find_size;
}

// 查找过程，查找元素p对应的集合ID
// O(h)，h为树的高度
int union_find_3_find(union_find_3_t *union_f, int p)
{
    if(p < 0 || p >= union_f->union_find_size)
    {
        exit(OVERFLOW);
    }

    // p不是根节点
    while(p != union_find_array_index_elem_3(union_f->parent, p)){
        p = union_find_array_index_elem_3(union_f->parent, p);
    }

    return p;
}

// 查询两个元素是否同属于一个集合
bool union_find_3_is_connected(union_find_3_t *union_f, int p, int q)
{
    return union_find_3_find(union_f, p) == union_find_3_find(union_f, q);
}

// 对元素p和元素q执行union操作
Status union_find_3_union(union_find_3_t *union_f, int p, int q)
{
    int p_root = union_find_3_find(union_f, p);
    int q_root = union_find_3_find(union_f, q);

    if(p_root == q_root)
        return OK;

    int p_root_size = union_find_array_index_elem_3(union_f->size, p_root);
    int q_root_size = union_find_array_index_elem_3(union_f->size, q_root);

    if(p_root_size > q_root_size){
        // parent[q_root]=p_root
        union_find_array_elem_copy_3(union_f->parent, q_root, p_root);
        // size[p_root]=size[p_root]+size[q_root]
        union_find_array_elem_copy_3(union_f->size, p_root, p_root_size + q_root_size);
    } else{ // p_root_size <= q_root_size
        // parent[p_root]=q_root
        union_find_array_elem_copy_3(union_f->parent, p_root, q_root);
        // size[q_root]=size[q_root]+size[p_root]
        union_find_array_elem_copy_3(union_f->size, q_root, q_root_size + p_root_size);
    }

    return OK;
}