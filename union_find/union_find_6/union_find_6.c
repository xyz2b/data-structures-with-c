//
// Created by 焦宏宇 on 6060/6/60.
//

#include "union_find_6.h"
#include <stdlib.h>
#include <string.h>

// 初始化并查集
union_find_6_t *union_find_6(int size)
{
    union_find_6_t *union_f = (union_find_6_t *)malloc(sizeof(union_find_6_t));

    void *parent = (char *)malloc(size * sizeof(int));

    void *rk = (char *)malloc(size * sizeof(int));
    if(!union_f || !parent || !rk){
        free(union_f);
        free(parent);
        free(rk);
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
        memcpy(rk + i * sizeof(int), &init_e, sizeof(int));
    }

    union_f->parent = parent;
    union_f->union_find_size = size;
    union_f->elem_size = sizeof(int);
    union_f->rank = rk;

    return union_f;
}

// 查看数组中index位置元素
int union_find_array_index_elem_6(void *arr, int index)
{
    return *(int*)(arr + index * sizeof(int));
}

// 将元素e赋值给数组中index位置
void union_find_array_elem_copy_6(void *arr, int index, int e)
{
    memcpy(arr + index * sizeof(int), &e, sizeof(int));
}

// 查看并查集的大小
int union_find_6_size(union_find_6_t *union_f)
{
    return union_f->union_find_size;
}

// 查找过程，查找元素p对应的集合ID
// O(h)，h为树的高度
int union_find_6_find(union_find_6_t *union_f, int p)
{
    if(p < 0 || p >= union_f->union_find_size)
    {
        exit(OVERFLOW);
    }

    // p不是根节点
    if(p != union_find_array_index_elem_6(union_f->parent, p)){
        // parent[p]=find(parent[p])
        int parent_p = union_find_array_index_elem_6(union_f->parent, p);
        union_find_array_elem_copy_6(union_f->parent, p, union_find_6_find(union_f, parent_p));
    }

    // return parent[p]
    return union_find_array_index_elem_6(union_f->parent, p);
}

// 查询两个元素是否同属于一个集合
bool union_find_6_is_connected(union_find_6_t *union_f, int p, int q)
{
    return union_find_6_find(union_f, p) == union_find_6_find(union_f, q);
}

// 对元素p和元素q执行union操作
Status union_find_6_union(union_find_6_t *union_f, int p, int q)
{
    int p_root = union_find_6_find(union_f, p);
    int q_root = union_find_6_find(union_f, q);

    if(p_root == q_root)
        return OK;

    int p_root_rank = union_find_array_index_elem_6(union_f->rank, p_root);
    int q_root_rank = union_find_array_index_elem_6(union_f->rank, q_root);

    if(p_root_rank > q_root_rank){
        // parent[q_root]=p_root
        union_find_array_elem_copy_6(union_f->parent, q_root, p_root);
    } else if(p_root_rank < q_root_rank){
        // parent[p_root]=q_root
        union_find_array_elem_copy_6(union_f->parent, p_root, q_root);
    } else { // p_root_rank == q_root_rank
        // parent[q_root]=p_root
        union_find_array_elem_copy_6(union_f->parent, q_root, p_root);
        // rank[p_root]+=1
        union_find_array_elem_copy_6(union_f->rank, p_root, p_root_rank + 1);
    }

    return OK;
}