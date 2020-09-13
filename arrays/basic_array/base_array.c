//
// Created by 焦宏宇 on 2020/2/8.
//

#include "base_array.h"
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


// 初始化数组 with capacity
void *basic_array_c(int capacity, int element_size)
{
    void *arr = (char *)malloc(capacity * element_size);

    if(!arr)
        return NULL;

    return arr;
}

// 初始化数组，默认capacity
void *basic_array(int element_size)
{
    void *arr = (char *)malloc(DEFAULTCAPACITY * element_size);
    if(!arr)
        return NULL;

    return arr;
}

// 将数组中索引从a开始连续n个位置的值赋值给数组中索引从c开始的位置
Status basic_array_segment_copy(void *arr, int elem_size, int src_index, int dst_index, size_t n)
{
    if(arr == NULL){
        exit(OVERFLOW);
    }

    void *src = (char*)arr + src_index * elem_size;
    void *dst = (char*)arr + dst_index * elem_size;

    memmove(dst, src, n * elem_size);

    return OK;
}

// 将数组中索引a的值赋值给索引b
Status basic_array_index_copy(void *arr, int elem_size, int src_index, int dst_index)
{
    if(arr == NULL){
        exit(OVERFLOW);
    }

    void *src = (char*)arr + src_index * elem_size;
    void *dst = (char*)arr + dst_index * elem_size;

    // TODO: 如果元素类型中包含指针，memcpy只会拷贝指针，使得两个指针指向同一个地址，而不会拷贝指针所指向的内容，即浅拷贝。还需要实现深拷贝
    memcpy(dst, src, elem_size);

    return OK;
}

// 将元素e赋值给数组索引index处的元素
Status basic_array_elem_copy(void *arr, int elem_size, int index, void *e)
{
    if(arr == NULL || e == NULL){
        exit(OVERFLOW);
    }

    void *src = e;
    void *dst = arr + index * elem_size;

    memcpy(dst, src, elem_size);

    return OK;
}

// 数组索引index处的元素赋值给元素e
Status basic_array_elem_copy_e(void *arr, int elem_size, int index, void *e)
{
    if(arr == NULL || e == NULL){
        exit(OVERFLOW);
    }

    void *dst = e;
    void *src = (char*)arr + index * elem_size;

    memcpy(dst, src, elem_size);

    return OK;
}

// 获取数组index处的元素
void *basic_array_get_elem(void *arr, int elem_size, int index, void *ret)
{
    if(arr == NULL){
        exit(OVERFLOW);
    }

    void *elem = (char*)arr + elem_size * index;
    // TODO: 调用该方法的需要改成新申请一块内存ret来接收获取到的元素值
    if(ret != NULL){
        memcpy(ret, elem, elem_size);
        return ret;
    }

    return elem;
}

// 判断数组index处的元素是否等于元素e
bool basic_array_elem_cmp(void *arr, int elem_size, int index, void *e)
{
    if(arr == NULL){
        exit(OVERFLOW);
    }

    void *elem_addr = (char*)arr + index * elem_size;

    return memcmp(e, elem_addr, elem_size) == 0;
}

// 将a数组的某个元素拷贝到b数组中
Status basic_array_copy(void *src_arr, void *dst_arr, int src_index, int dst_index, int elem_size)
{
    if(src_arr == NULL||dst_arr == NULL){
        exit(OVERFLOW);
    }

    void *src_elem = basic_array_get_elem(src_arr, elem_size, src_index, NULL);
    basic_array_elem_copy(dst_arr, elem_size, dst_index, src_elem);

    return OK;

}

// 将a数组的元素拷贝到b数组中
Status basic_array_arr_copy(void *src_arr, void *dst_arr, int begin_index, int end_index, int elem_size)
{
    void *src = (char*)src_arr + begin_index * elem_size;
    void *dst = (char*)dst_arr + begin_index * elem_size;

    // TODO: 如果元素类型中包含指针，memcpy只会拷贝指针，使得两个指针指向同一个地址，而不会拷贝指针所指向的内容，即浅拷贝。还需要实现深拷贝
    memcpy(dst, src, (end_index - begin_index + 1) * elem_size);

    return OK;
}

// 交换数组中的两个索引的元素
Status basic_array_elem_swap(void *arr, int i, int j, int elem_size)
{
    void *temp = (char *)malloc(elem_size);
    if(!temp)
        exit(OVERFLOW);

    // temp = arr[index]
    basic_array_elem_copy_e(arr, elem_size, i, temp);

    // arr[i] = arr[j]
    basic_array_index_copy(arr, elem_size, j, i);

    // arr[j] = temp
    basic_array_elem_copy(arr, elem_size, j, temp);

    free(temp);

    return OK;
}

// 销毁数组
Status basic_array_destroy(void **arr)
{
    if(*arr == NULL){
        exit(OVERFLOW);
    }

    free(*arr);

    *arr = NULL;

    return OK;
}