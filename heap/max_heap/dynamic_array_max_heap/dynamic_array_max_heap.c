//
// Created by 焦宏宇 on 2020/2/16.
//

#include "dynamic_array_max_heap.h"
#include <stdlib.h>
#include <stdio.h>

// 初始化堆 with capacity
dynamic_array_max_heap_t *dynamic_array_max_heap_c(int capacity, int element_size)
{
    dynamic_array_max_heap_t *dynamic_array_max_h = (dynamic_array_max_heap_t *)malloc(sizeof(dynamic_array_max_heap_t));
    dynamic_array_t *dynamic_a = array_c(capacity, element_size);

    if(!dynamic_array_max_h || !dynamic_a){
        // 存储分配失败
        free(dynamic_array_max_h);
        return NULL;
    }

    dynamic_array_max_h->dynamic_a = dynamic_a;

    return dynamic_array_max_h;
}

// 初始化堆，默认capacity
dynamic_array_max_heap_t *dynamic_array_max_heap(int element_size)
{
    dynamic_array_max_heap_t *dynamic_array_max_h = (dynamic_array_max_heap_t *)malloc(sizeof(dynamic_array_max_heap_t));
    dynamic_array_t *dynamic_a = array(element_size);

    if(!dynamic_array_max_h || !dynamic_a){
        // 存储分配失败
        free(dynamic_array_max_h);
        return NULL;
    }

    dynamic_array_max_h->dynamic_a = dynamic_a;

    return dynamic_array_max_h;
}

// 初始化空堆
dynamic_array_max_heap_t *dynamic_array_max_heap_none()
{
    dynamic_array_max_heap_t *dynamic_array_max_h = (dynamic_array_max_heap_t *)malloc(sizeof(dynamic_array_max_heap_t));

    if(!dynamic_array_max_h){
        // 存储分配失败
        free(dynamic_array_max_h);
        return NULL;
    }

    dynamic_array_max_h->dynamic_a = NULL;

    return dynamic_array_max_h;
}

// 获取堆的元素个数
int dynamic_array_max_heap_size(dynamic_array_max_heap_t *dynamic_array_max_h)
{
    if(dynamic_array_max_h == NULL){
        exit(OVERFLOW);
    }

    return dynamic_array_max_h->dynamic_a->size;
}

// 获取堆的容量
int dynamic_array_max_heap_capacity(dynamic_array_max_heap_t *dynamic_array_max_h)
{
    if(dynamic_array_max_h == NULL){
        exit(OVERFLOW);
    }

    return dynamic_array_max_h->dynamic_a->capacity;
}

// 堆是否为空
bool dynamic_array_max_heap_is_empty(dynamic_array_max_heap_t *dynamic_array_max_h)
{
    if(dynamic_array_max_h == NULL){
        exit(OVERFLOW);
    }

    return dynamic_array_max_h->dynamic_a->size == 0;
}

// 获取父节点的索引
int dynamic_array_max_heap_parent(int index)
{
    if(index == 0){
        exit(OVERFLOW);
    }
    return (index - 1) / 2;
}

// 获取左孩子节点的索引
int dynamic_array_max_heap_left_child(int index)
{
    return index * 2 + 1;
}

// 获取右孩子节点的索引
int dynamic_array_max_heap_right_child(int index)
{
    return index * 2 + 2;
}

void dynamic_array_max_heap_sift_up(dynamic_array_max_heap_t *dynamic_array_max_h, int index, compare_s compare_t)
{
    while (index > 0){
        void *index_elem = (char *)malloc(dynamic_array_max_h->dynamic_a->element_size);
        array_get(dynamic_array_max_h->dynamic_a, index, index_elem);

        void *parent_elem = (char *)malloc(dynamic_array_max_h->dynamic_a->element_size);
        int parent_index = dynamic_array_max_heap_parent(index);
        array_get(dynamic_array_max_h->dynamic_a, parent_index, parent_elem);

        if((*compare_t)(index_elem, parent_elem) <= 0){
            break;
        }
        array_swap(dynamic_array_max_h->dynamic_a, index, parent_index);
        index = parent_index;

        free(index_elem);
        free(parent_elem);
    }
}

// 向堆中添加元素
Status dynamic_array_max_heap_add(dynamic_array_max_heap_t *dynamic_array_max_h, void *e, compare_s compare_t)
{
    array_insert_last(dynamic_array_max_h->dynamic_a, e);

    dynamic_array_max_heap_sift_up(dynamic_array_max_h, dynamic_array_max_h->dynamic_a->size - 1, compare_t);

    return OK;
}

// 查看堆顶元素(即最大元素)
void *dynamic_array_max_heap_find_max(dynamic_array_max_heap_t *dynamic_array_max_h, void *ret)
{
    if(dynamic_array_max_heap_is_empty(dynamic_array_max_h) == true)
        exit(OVERFLOW);

    array_get_first(dynamic_array_max_h->dynamic_a, ret);

    return ret;
}

void dynamic_array_max_heap_sift_down(dynamic_array_max_heap_t *dynamic_array_max_h, int index, compare_s compare_t)
{
    // 节点存在左孩子的情况，即左孩子的索引小于数组的大小，否则数组越界，不存在左孩子
    while (dynamic_array_max_heap_left_child(index) < dynamic_array_max_heap_size(dynamic_array_max_h)){

        int j = dynamic_array_max_heap_left_child(index);

        // left_child_index + 1 == right_child_index
        // // 节点存在右孩子的情况，即右孩子的索引小于数组的大小，否则数组越界，不存在右孩子
        if(j + 1 < dynamic_array_max_heap_size(dynamic_array_max_h)) {
            void *right_child_elem = (char *) malloc(dynamic_array_max_h->dynamic_a->element_size);
            array_get(dynamic_array_max_h->dynamic_a, j + 1, right_child_elem);

            void *left_child_elem = (char *) malloc(dynamic_array_max_h->dynamic_a->element_size);
            array_get(dynamic_array_max_h->dynamic_a, j, left_child_elem);

            if ((*compare_t)(right_child_elem, left_child_elem) > 0) {
                j = dynamic_array_max_heap_right_child(index);
            }

            free(right_child_elem);
            free(left_child_elem);
        }

        // data[j] 是 left_child和right_child中的最大值
        void *j_elem = (char *) malloc(dynamic_array_max_h->dynamic_a->element_size);
        array_get(dynamic_array_max_h->dynamic_a, j, j_elem);

        void *index_elem = (char *)malloc(dynamic_array_max_h->dynamic_a->element_size);
        array_get(dynamic_array_max_h->dynamic_a, index, index_elem);

        if((*compare_t)(index_elem, j_elem) >= 0){
            break;
        }

        array_swap(dynamic_array_max_h->dynamic_a, j, index);
        free(j_elem);
        free(index_elem);
        index = j;
    }

}

// 从堆中取出堆顶元素(即最大元素)
void *dynamic_array_max_heap_extract_max(dynamic_array_max_heap_t *dynamic_array_max_h, void *ret, compare_s compare_t)
{
    ret = dynamic_array_max_heap_find_max(dynamic_array_max_h, ret);

    array_swap(dynamic_array_max_h->dynamic_a, 0, dynamic_array_max_heap_size(dynamic_array_max_h) - 1);
    array_remove_last(dynamic_array_max_h->dynamic_a, NULL);

    dynamic_array_max_heap_sift_down(dynamic_array_max_h, 0, compare_t);

    return ret;
}

// replace操作是将堆顶的元素取出，然后再添加一个新的元素
// 实现方法: 先extract max，再add，两次O(logn)的操作
// 实现方法: 将堆顶的元素替换成新的元素，然后再执行shift down，一次O(logn)的操作
void *dynamic_array_max_heap_replace(dynamic_array_max_heap_t *dynamic_array_max_h, void *e, void *ret, compare_s compare_t)
{
    ret = dynamic_array_max_heap_find_max(dynamic_array_max_h, ret);

    array_set(dynamic_array_max_h->dynamic_a, 0 , e);

    dynamic_array_max_heap_sift_down(dynamic_array_max_h, 0, compare_t);

    return ret;
}


// heapify是将任意数组整理成堆的形状
// 可以将数组先看成一个完全二叉树，但是它不满足堆的性质，然后从最后一个非叶子节点开始向前遍历，直到根节点，然后对遍历到的每个非叶子节点进行shift down即可
// 如何定位最后一个非叶子节点的索引，先获取最后一个节点的索引(size - 1)，然后计算其父节点的索引，即最后一个非叶子节点的索引
dynamic_array_max_heap_t *dynamic_array_max_heap_heapify(void *arr, int arr_length, int elem_size, compare_s compare_t)
{
    dynamic_array_max_heap_t *dynamic_array_max_h = dynamic_array_max_heap_none();

    dynamic_array_max_h->dynamic_a = array_basic_arr_to_dynamic_arr(arr, arr_length, elem_size);

    if(dynamic_array_max_h->dynamic_a->size > 1){
        int parent_index = dynamic_array_max_heap_parent(dynamic_array_max_h->dynamic_a->size - 1);

        for(int i = parent_index; i >= 0; i--){
            dynamic_array_max_heap_sift_down(dynamic_array_max_h, i, compare_t);
        }
    }

    return dynamic_array_max_h;
}


// 清空堆
Status dynamic_array_max_heap_clear(dynamic_array_max_heap_t *dynamic_array_max_h)
{
    if(dynamic_array_max_h == NULL){
        exit(OVERFLOW);
    }

    array_clear(dynamic_array_max_h->dynamic_a);
    return OK;
}

// 销毁堆
Status dynamic_array_max_heap_destroy(dynamic_array_max_heap_t **dynamic_array_max_h)
{
    if(*dynamic_array_max_h == NULL){
        exit(OVERFLOW);
    }

    array_destroy(&((*dynamic_array_max_h)->dynamic_a));

    free(*dynamic_array_max_h);

    *dynamic_array_max_h = NULL;

    return OK;
}