//
// Created by 焦宏宇 on 2020/2/4.
//

#include "dynamic_array.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>


// 初始化数组 with capacity
dynamic_array_t *array_c(int capacity, int element_size)
{
    dynamic_array_t *dynamic_array = (dynamic_array_t *)malloc(sizeof(dynamic_array_t));
    void *arr = (char *)basic_array_c(capacity, element_size);

    if(!dynamic_array || !arr){
        // 存储分配失败
        free(dynamic_array);
        basic_array_destroy(&arr);
        return NULL;
    }

    dynamic_array->capacity = capacity;
    dynamic_array->size = 0;
    dynamic_array->element_size = element_size;
    dynamic_array->data = arr;

    return dynamic_array;
}

// 初始化数组，默认capacity
dynamic_array_t *array(int element_size)
{
    dynamic_array_t *dynamic_array = (dynamic_array_t *)malloc(sizeof(dynamic_array_t));
    void *arr = (char *)basic_array_c(DEFAULTCAPACITY, element_size);
    if(!dynamic_array || !arr){
        // 存储分配失败
        free(dynamic_array);
        basic_array_destroy(&arr);
        return NULL;
    }

    dynamic_array->capacity = DEFAULTCAPACITY;
    dynamic_array->size = 0;
    dynamic_array->element_size = element_size;
    dynamic_array->data = arr;

    return dynamic_array;
}

// 将一个普通数组转换成动态数组
dynamic_array_t *array_basic_arr_to_dynamic_arr(void *arr, int arr_length, int element_size)
{
    dynamic_array_t* dynamic_a = array_c(arr_length, element_size);

    basic_array_arr_copy(arr, dynamic_a->data, 0, arr_length - 1, element_size);

    dynamic_a->size = arr_length;

    return dynamic_a;

}

// 获取数组的元素个数
int array_size(dynamic_array_t *dynamic_array)
{
    if(dynamic_array == NULL){
        exit(OVERFLOW);
    }

    return dynamic_array->size;
}

// 获取数组的容量
int array_capacity(dynamic_array_t *dynamic_array)
{
    if(dynamic_array == NULL){
        exit(OVERFLOW);
    }

    return dynamic_array->capacity;
}

// 数组是否为空
bool array_is_empty(dynamic_array_t *dynamic_array)
{
    if(dynamic_array == NULL){
        exit(OVERFLOW);
    }

    return dynamic_array->size == 0;
}

// 调整数组capacity
Status array_resize(dynamic_array_t *dynamic_array, int new_capacity)
{
    void *arr = (char *)basic_array_c(new_capacity, dynamic_array->element_size);
    if(!arr)  // 存储分配失败
        return ERROR;

    basic_array_arr_copy(dynamic_array->data, arr, 0, dynamic_array->size - 1, dynamic_array->element_size);

    basic_array_destroy(&(dynamic_array->data));
    dynamic_array->data = NULL;

    dynamic_array->data = arr;
    dynamic_array->capacity = new_capacity;

    return OK;
}

// 在数组index位置插入一个新元素e
Status array_insert(dynamic_array_t *dynamic_array, int index, void *e)
{
    if(dynamic_array == NULL){
        // 数组不存在
        exit(OVERFLOW);
    }

    if(index < 0 || index > dynamic_array->size)
        // index索引非法，插入时，需要0<=index<=size
        exit(OVERFLOW);

    if(dynamic_array->size == dynamic_array->capacity)
        // 数组已满，扩容
        array_resize(dynamic_array, 2 * dynamic_array->capacity);

//    for(int i = dynamic_array->size - 1; i >= index; i--){
//
//        basic_array_index_copy(dynamic_array->data, dynamic_array->element_size, i, i + 1);
//    }

    basic_array_segment_copy(dynamic_array->data, dynamic_array->element_size, index, index + 1, dynamic_array->size - index);

    basic_array_elem_copy(dynamic_array->data, dynamic_array->element_size, index, e);

    dynamic_array->size ++;

    return OK;
}

// 向数组末尾插入元素
Status array_insert_last(dynamic_array_t *dynamic_array, void *e)
{
    int status = array_insert(dynamic_array, dynamic_array->size, e);
    if(status == OK)
        return OK;
    else
        return ERROR;
}

// 向数组头部插入元素
Status array_insert_first(dynamic_array_t *dynamic_array, void *e)
{
    int status = array_insert(dynamic_array, 0, e);
    if(status == OK)
        return OK;
    else
        return ERROR;
}

// 获取index索引位置的元素，存放在ret中
void *array_get(dynamic_array_t *dynamic_array, int index, void *ret)
{
    if(dynamic_array == NULL){
        exit(OVERFLOW);
    }

    if(index < 0 || index >= dynamic_array->size)
        // index索引非法，获取时，需要0<=index<size
        exit(OVERFLOW);

    void *elem = basic_array_get_elem(dynamic_array->data, dynamic_array->element_size, index, ret);

    return elem;
}

// 获取数组尾元素，存放在ret中
Status array_get_last(dynamic_array_t *dynamic_array, void *ret)
{
    void *r = array_get(dynamic_array, dynamic_array->size-1 ,ret);
    if(r == NULL)
        return ERROR;

    return OK;
}

// 获取数组首元素，存放在ret中
Status array_get_first(dynamic_array_t *dynamic_array, void *ret)
{
    void *r = array_get(dynamic_array, 0 ,ret);
    if(r == NULL)
        return ERROR;

    return OK;
}

// 修改数组index索引位置的元素为e
Status array_set(dynamic_array_t *dynamic_array, int index, void *e)
{
    if(dynamic_array == NULL){
        exit(OVERFLOW);
    }

    if(index < 0 || index >= dynamic_array->size)
        // index索引非法，需要0<=index<=size
        exit(OVERFLOW);

    basic_array_elem_copy(dynamic_array->data, dynamic_array->element_size, index, e);

    return OK;
}

// 查找数组中是否有元素e
bool array_contain(dynamic_array_t *dynamic_array, void *e)
{
    if(dynamic_array == NULL){
        exit(OVERFLOW);
    }

    for(int i = 0;i < dynamic_array->size; i++)
        if(basic_array_elem_cmp(dynamic_array->data, dynamic_array->element_size, i, e))
            return true;
    return false;
}

// 查找数组中元素e所在的索引，如果不存在元素e，则返回-1
int array_find(dynamic_array_t *dynamic_array, void *e)
{
    if(dynamic_array == NULL){
        exit(OVERFLOW);
    }

    for(int i = 0;i < dynamic_array->size; i++)
        if(basic_array_elem_cmp(dynamic_array->data, dynamic_array->element_size, i, e))
            return i;

    return -1;
}

// 删除数组中index位置的元素，并将删除的元素存在ret中
Status array_remove(dynamic_array_t *dynamic_array, int index, void *ret)
{
    if(dynamic_array == NULL){
        exit(OVERFLOW);
    }

    if(index < 0 || index > dynamic_array->size)
        // index索引非法，需要0<=index<=size
        exit(OVERFLOW);

    if(ret != NULL){
        void *elem = basic_array_get_elem(dynamic_array->data, dynamic_array->element_size, index, NULL);
        memcpy(ret, elem, dynamic_array->element_size);
    }

//    for(int i = index + 1; i < dynamic_array->size; i ++)
//    {
//        basic_array_index_copy(dynamic_array->data, dynamic_array->element_size, i, i - 1);
//    }

    basic_array_segment_copy(dynamic_array->data, dynamic_array->element_size, index + 1, index, dynamic_array->size - (index + 1));

    dynamic_array->size --;

    if(dynamic_array->size == dynamic_array->capacity/4 && dynamic_array->capacity/2 != 0)
        // 数组使用量等于capacity/4，缩容1/2(防止复杂度震荡)
        array_resize(dynamic_array, dynamic_array->capacity/2);

    return OK;
}

// 删除数组中末尾的元素，并将删除的元素存在ret中
Status array_remove_last(dynamic_array_t *dynamic_array, void *ret)
{
    array_remove(dynamic_array, dynamic_array->size-1, ret);

    return OK;
}

// 删除数组中开头的元素，并将删除的元素存在ret中
Status array_remove_first(dynamic_array_t *dynamic_array, void *ret)
{
    array_remove(dynamic_array, 0, ret);

    return OK;
}

// 删除数组中元素e
Status array_remove_elem(dynamic_array_t *dynamic_array, void *e)
{
    int index = array_find(dynamic_array, e);

    if(index != -1)
    {
        array_remove(dynamic_array, index, NULL);
        return OK;
    }

    return ERROR;
}

// 交换数组中i和j索引的元素
void array_swap(dynamic_array_t *dynamic_array, int i, int j)
{
    if(i < 0 || i > dynamic_array->size || j < 0 || j >dynamic_array->size){
        exit(OVERFLOW);
    }

    basic_array_elem_swap(dynamic_array->data, i, j, dynamic_array->element_size);
}



// 查看数组信息，需要传入调用方定义的将调用方自定义的类型转换成数组的函数to_string
void array_show(dynamic_array_t *dynamic_array, to_string_s to_string_t)
{
    if(dynamic_array == NULL){
        exit(OVERFLOW);
    }

    void *ret = (char *)malloc(dynamic_array->element_size);
    if(!ret)  // 存储分配失败
        exit(OVERFLOW);

    printf("Array: size = %d, capacity = %d, elem_size = %d\n", dynamic_array->size, dynamic_array->capacity, dynamic_array->element_size);
    printf("[");

    for(int i = 0; i < dynamic_array->size; i++)
    {
        // TODO: 解决类型转换后接收字符串的数组buffer容量大小固定问题
        char buffer[200];
        array_get(dynamic_array, i, ret);
        int ok = (*to_string_t)(ret, buffer);
        if(ok != OK){
            free(ret);
            exit(ERROR);
        }
        if(i != dynamic_array->size -1){
            printf("%s, ", buffer);
        } else {
            printf("%s", buffer);
        }
    }

    printf("]\n");

    free(ret);
}

// 清空数组
Status array_clear(dynamic_array_t *dynamic_array)
{
    if(dynamic_array == NULL){
        exit(OVERFLOW);
    }

    dynamic_array->size = 0;
    return OK;
}

// 销毁数组
Status array_destroy(dynamic_array_t **dynamic_array)
{
    if(*dynamic_array == NULL){
        exit(OVERFLOW);
    }

    basic_array_destroy(&(*dynamic_array)->data);

    (*dynamic_array)->data = NULL;
    (*dynamic_array)->size = 0;
    (*dynamic_array)->capacity = 0;

    free(*dynamic_array);

    *dynamic_array = NULL;

    return OK;
}