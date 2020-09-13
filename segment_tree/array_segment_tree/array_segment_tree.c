//
// Created by 焦宏宇 on 2020/2/17.
//

#include "array_segment_tree.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// 初始化数组
dynamic_array_t *array_segment_tree_array(void *arr, int capacity, int element_size)
{
    dynamic_array_t *dynamic_a = array_basic_arr_to_dynamic_arr(arr, capacity, element_size);

    return dynamic_a;
}

//  初始化线段树
array_segment_tree_t *array_segment_tree(int capacity, int element_size)
{
    // TODO: 初始化数组申请内存时候，内存的内容是随机的，因为是用malloc申请的，没进行任何初始化，有可能随机的内容和你需要存入的内容是一样的，导致混乱，要把内存的值初始化一个都不会有的值
    array_segment_tree_t *array_segment_t = (array_segment_tree_t *)malloc(sizeof(array_segment_tree_t));
    dynamic_array_t *dynamic_a = array_c(4 * capacity, element_size);

    if(!array_segment_t || !dynamic_a){
        // 存储分配失败
        free(array_segment_t);
        return NULL;
    }

    array_segment_t->dynamic_a = dynamic_a;
    array_segment_t->dynamic_a->size = array_segment_t->dynamic_a->capacity;

    return array_segment_t;
}

// 获取index位置的元素
void *array_segment_tree_get(array_segment_tree_t *array_segment_t, int index, void *ret)
{
    if(index < 0||index > array_segment_t->dynamic_a->size){
        exit(OVERFLOW);
    }
    void *elem = array_get(array_segment_t->dynamic_a, index, ret);
    return elem;
}

// 将e赋值给数组index位置
void array_segment_tree_array_set(array_segment_tree_t *array_segment_t, int index, void *e)
{
    basic_array_elem_copy(array_segment_t->dynamic_a->data, array_segment_t->dynamic_a->element_size, index, e);
}

// 获取左孩子节点的索引
int array_segment_tree_left_child(int index)
{
    return index * 2 + 1;
}

// 获取右孩子节点的索引
int array_segment_tree_right_child(int index)
{
    return index * 2 + 2;
}

// 由给定的数组创建线段树
// 参数: 数组 | 线段树 | 当前所要创建的线段树根节点所对应的索引(tree_index) | 对于当前节点来说它所表示区间的左右端点(l/r)，对应到数组中的索引为l/r
Status array_segment_tree_build(dynamic_array_t *arr, array_segment_tree_t *array_segment_t, int tree_index, int l, int r, merge_s merge_t)
{
    // 如果左右端点相同，说明就只有一个元素， 直接将该元素赋给当前节点即可
    if(l == r){
        // 因为线段树对应的数组不会有增删只有修改，所以不需要新创建一块内存把返回的内容复制过来
        void *e = basic_array_get_elem(arr->data, arr->element_size, l, NULL);
        array_segment_tree_array_set(array_segment_t, tree_index, e);
        return OK;
    }

    int left_tree_index = array_segment_tree_left_child(tree_index);
    int right_tree_index = array_segment_tree_right_child(tree_index);

    // 计算区间的中间点
    int mid = l + (r - l) / 2;
    // 生成左子树，传入左子树的根的索引
    array_segment_tree_build(arr, array_segment_t, left_tree_index, l, mid, merge_t);
    // 生成右子树，传入右子树的根的索引
    array_segment_tree_build(arr, array_segment_t, right_tree_index, mid + 1, r, merge_t);

    // 当前节点的值等于左右孩子merge之后的值
    // merge操作具体怎么做由调用者定义，然后在生成线段树的时候传入merge函数即可
    void *e = (char *)malloc(arr->element_size);
    (*merge_t)(array_segment_tree_get(array_segment_t, left_tree_index, NULL), array_segment_tree_get(array_segment_t, right_tree_index, NULL), e);
    array_segment_tree_array_set(array_segment_t, tree_index, e);
    free(e);

    return OK;
}


// tree_index是线段树中根的索引 | [l, r]表示该节点所表示的区间端点，对应到数组中的索引为l/r | 搜索的区间[query_l, query_r]，对应到数组中的索引为query_l/query_r
void *array_segment_tree_query(array_segment_tree_t *array_segment_t, int tree_index, int l, int r, int query_l, int query_r, void *ret, merge_s merge_t)
{
    if(query_l == l && query_r == r){
        array_segment_tree_get(array_segment_t, tree_index, ret);
        return ret;
    }

    // 计算区间的中间点
    int mid = l + (r - l) / 2;
    int left_tree_index = array_segment_tree_left_child(tree_index);
    int right_tree_index = array_segment_tree_right_child(tree_index);

    if(query_l >= mid + 1){
        return array_segment_tree_query(array_segment_t, right_tree_index, mid + 1, r, query_l, query_r, ret, merge_t);
    } else if(query_r <= mid){
        return array_segment_tree_query(array_segment_t, left_tree_index, l, mid, query_l, query_r, ret, merge_t);
    }

    void *left_result = array_segment_tree_query(array_segment_t, left_tree_index, l, mid, query_l, mid, ret, merge_t);
    void *right_result = array_segment_tree_query(array_segment_t, right_tree_index, mid + 1, query_r, query_l, mid, ret, merge_t);

    (*merge_t)(left_result, right_result, ret);
    return ret;

}


// 返回区间[query_l, query_r]的值，即表示元素中的索引query_l/query_r
Status array_segment_tree_query_r(array_segment_tree_t *array_segment_t, int data_length, int query_l, int query_r, void *ret, merge_s merge_t)
{

    if(query_l < 0 || query_r >= data_length || query_r < 0 || query_r >= data_length || query_l > query_r){
        exit(OVERFLOW);
    }
    array_segment_tree_query(array_segment_t, 0, 0, data_length - 1, query_l, query_r, ret, merge_t);

    return OK;
}


// tree_index是线段树中根的索引 | [l, r]表示该节点所表示的区间端点,对应到数组中的索引为l/r | index表示需要修改的值在数组中的索引
// 后序遍历的思想(更新完叶子节点之后，还需要对每个受影响的非叶子节点进行更新(重新merge该节点的左右子树))
Status array_segment_tree_set(array_segment_tree_t *array_segment_t, int tree_index, int l, int r, int index, void *e, merge_s merge_t)
{
    // 找到数组index位置对应到线段树中的叶子节点
    if(l == r){
        array_segment_tree_array_set(array_segment_t, tree_index, e);
        return OK;
    }

    // 计算区间的中间点
    int mid = l + (r - l) / 2;
    int left_tree_index = array_segment_tree_left_child(tree_index);
    int right_tree_index = array_segment_tree_right_child(tree_index);

    if(index >= mid + 1){
        array_segment_tree_set(array_segment_t, right_tree_index, mid + 1, r, index, e, merge_t);
    } else { // index <= mid
        array_segment_tree_set(array_segment_t, left_tree_index, l, mid, index, e, merge_t);
    }

    // 在对每一个叶子节点进行更新的时候，对叶子节点的父节点，叶子节点的父节点的父节点等等，都要进行更新
    // 即在递归返回的时候将每个节点(除了叶子节点)的左右子树重新merge一下
    void *merge_e = (char *)malloc(array_segment_t->dynamic_a->element_size);
    (*merge_t)(array_segment_tree_get(array_segment_t, left_tree_index, NULL), array_segment_tree_get(array_segment_t, right_tree_index, NULL), merge_e);
    array_segment_tree_array_set(array_segment_t, tree_index, merge_e);
    free(merge_e);

    return OK;

}

// 将数组index位置的值，更新为e
Status array_segment_tree_set_r(dynamic_array_t *arr, array_segment_tree_t *array_segment_t, int index, void *e, merge_s merge_t)
{
    if(index < 0 || index >= arr->size){
        exit(OVERFLOW);
    }

    array_set(arr, index, e);

    array_segment_tree_set(array_segment_t, 0, 0, arr->size - 1, index, e, merge_t);

    return OK;
}


// 查看线段树
void array_segment_tree_show(array_segment_tree_t *array_segment_t, to_string_s to_string_t)
{
    if(array_segment_t == NULL){
        exit(OVERFLOW);
    }

    void *ret = (char *)malloc(array_segment_t->dynamic_a->element_size);
    if(!ret)  // 存储分配失败
        exit(OVERFLOW);

    printf("[");

    for(int i = 0; i < array_segment_t->dynamic_a->size; i++)
    {
        // TODO: 解决类型转换后接收字符串的数组buffer容量大小固定问题
        char buffer[200];
        array_get(array_segment_t->dynamic_a, i, ret);
        int ok = (*to_string_t)(ret, buffer);
        if(ok != OK){
            free(ret);
            exit(ERROR);
        }
        if(i != array_segment_t->dynamic_a->size -1){
            printf("%s, ", buffer);
        } else {
            printf("%s", buffer);
        }
    }

    printf("]\n");

    free(ret);
}
