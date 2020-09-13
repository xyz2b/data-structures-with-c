//
// Created by 焦宏宇 on 2020/2/9.
//

#include "linked_list_stack.h"
#include <stdlib.h>
#include <stdio.h>

// 初始化栈
linked_list_stack_t *linked_list_stack(int data_size)
{
    linked_list_t *linked_l = linked_list(data_size);
    if(!linked_l){
        // 存储分配失败
        return NULL;
    }

    linked_list_stack_t *linked_list_s = (linked_list_stack_t *)malloc(sizeof(linked_list_stack_t));
    if(!linked_list_s){
        // 存储分配失败
        linked_list_destroy(&linked_l);
        return NULL;
    }

    linked_list_s->linked_l = linked_l;

    return linked_list_s;
}

// 获取栈的元素个数
int linked_list_stack_size(linked_list_stack_t *linked_list_s)
{
    if(linked_list_s == NULL){
        exit(OVERFLOW);
    }

    return linked_list_s->linked_l->size;
}

// 判断栈是否为空
bool linked_list_stack_is_empty(linked_list_stack_t *linked_list_s)
{
    if(linked_list_s == NULL){
        exit(OVERFLOW);
    }

    return linked_list_s->linked_l->size == 0;
}

// 压栈
Status linked_list_stack_push(linked_list_stack_t *linked_list_s, void *e)
{
    if(linked_list_s == NULL){
        exit(OVERFLOW);
    }

    Status ok = linked_list_insert_first(linked_list_s->linked_l, e);
    if(!ok){
        return ERROR;
    }

    return OK;
}

// 出栈
Status linked_list_stack_pop(linked_list_stack_t *linked_list_s, void *ret)
{
    if(linked_list_s == NULL){
        exit(OVERFLOW);
    }

    Status ok = linked_list_remove_first(linked_list_s->linked_l, ret);
    if(!ok){
        return ERROR;
    }

    return OK;
}

// 查看栈顶的元素
Status linked_list_stack_peek(linked_list_stack_t *linked_list_s, void *ret)
{
    if(linked_list_s == NULL){
        exit(OVERFLOW);
    }

    Status ok = linked_list_get_first(linked_list_s->linked_l, ret);
    if(!ok){
        return ERROR;
    }

    return OK;
}

// 查看栈信息，需要传入调用方定义的将调用方自定义的类型转换成数组的函数to_string
Status linked_list_stack_show(linked_list_stack_t *linked_list_s, to_string_s to_string_t)
{
    if(linked_list_s == NULL){
        exit(OVERFLOW);
    }

    printf("%s", "Stack: top ");
    linked_list_show(linked_list_s->linked_l, to_string_t);

    return OK;
}

// 清空栈
Status linked_list_stack_clear(linked_list_stack_t *linked_list_s)
{
    if(linked_list_s == NULL){
        return OVERFLOW;
    }

    Status ok = linked_list_clear(linked_list_s->linked_l);
    if(ok == OVERFLOW){
        return OVERFLOW;
    }

    return OK;
}

// 销毁栈
Status linked_list_stack_destroy(linked_list_stack_t **linked_list_s)
{
    if(*linked_list_s == NULL){
        exit(OVERFLOW);
    }

    linked_list_destroy(&((*linked_list_s)->linked_l));

    (*linked_list_s)->linked_l = NULL;

    free(*linked_list_s);

    *linked_list_s = NULL;

    return OK;
}

