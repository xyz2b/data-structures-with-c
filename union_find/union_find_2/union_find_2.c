//
// Created by 焦宏宇 on 2020/2/20.
//

#include "union_find_2.h"
#include <stdlib.h>
#include <string.h>

// 初始化并查集
union_find_2_t *union_find_2(int size)
{
    union_find_2_t *union_f = (union_find_2_t *)malloc(sizeof(union_find_2_t));

    void *parent = (char *)malloc(size * sizeof(int));
    if(!union_f || !parent){
        free(union_f);
        free(parent);
        exit(OVERFLOW);
    }

//    int arr[size];
//    for(int i = 0; i < size; i ++){
//        arr[i] = i;
//    }
//    memcpy(id, arr, size * elem_size);


    for(int i = 0; i < size; i ++){
        memcpy(parent + i * sizeof(int), &i, sizeof(int));
    }

    union_f->parent = parent;
    union_f->size = size;
    union_f->elem_size = sizeof(int);

    return union_f;
}

// 查看数组中index位置元素
int union_find_array_index_elem_2(void *arr, int index)
{
    return *(int*)(arr + index * sizeof(int));
}

// 将元素e赋值给数组中index位置
void union_find_array_elem_copy_2(void *arr, int index, int e)
{
    memcpy(arr + index * sizeof(int), &e, sizeof(int));
}

// 查看并查集的大小
int union_find_2_size(union_find_2_t *union_f)
{
    return union_f->size;
}

// 查找过程，查找元素p对应的集合ID
// O(h)，h为树的高度
int union_find_2_find(union_find_2_t *union_f, int p)
{
    if(p < 0 || p >= union_f->size)
    {
        exit(OVERFLOW);
    }

    while(p != union_find_array_index_elem_2(union_f->parent, p)){
        p = union_find_array_index_elem_2(union_f->parent, p);
    }

    return p;
}

// 查询两个元素是否同属于一个集合
bool union_find_2_is_connected(union_find_2_t *union_f, int p, int q)
{
    return union_find_2_find(union_f, p) == union_find_2_find(union_f, q);
}

// 对元素p和元素q执行union操作
Status union_find_2_union(union_find_2_t *union_f, int p, int q)
{
    int p_root = union_find_2_find(union_f, p);
    int q_root = union_find_2_find(union_f, q);

    if(p_root == q_root)
        return OK;

    // parent[p_id]=q_id
    union_find_array_elem_copy_2(union_f->parent, p_root, q_root);
    return OK;
}