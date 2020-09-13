#include <stdio.h>
#include "stacks/array_stack/array_stack.h"
#include "queues/array_queue/array_queue.h"
#include "queues/loop_queue/loop_queue.h"
#include "queues/linked_list_queue/linked_list_queue.h"
#include "linked_list/base_linked_list/base_linked_list.h"
#include "stacks/linked_list_stack/linked_list_stack.h"
#include "linked_list/loop_linked_list/loop_linked_list.h"
#include "bst/repeat_elem_bst/repeat_elem_bst.h"
#include "bst/basic_bst/basic_bst.h"
#include "map/bst_map/bst_map.h"
#include "heap/max_heap/dynamic_array_max_heap/dynamic_array_max_heap.h"
#include "priority_queue/max_heap_priority_queue/max_heap_priority_queue.h"
#include "segment_tree/array_segment_tree/array_segment_tree.h"
#include "union_find/union_find_1/union_find_1.h"
#include "union_find/union_find_2/union_find_2.h"
#include "union_find/union_find_3/union_find_3.h"
#include "union_find/union_find_4/union_find_4.h"
#include "union_find/union_find_5/union_find_5.h"
#include "union_find/union_find_6/union_find_6.h"
#include "avl_tree/avl_tree/avl_tree.h"
#include <time.h>
#include <stdlib.h>

typedef int ElemType;

Status to_string(void *value, char *string){
    int count = sprintf(string, "%d", *(int*)value);
    if(count < 0){
        return ERROR;
    }
    return OK;
}

int compare(void *value1, void *value2){
    int v1 = *(int*)value1;
    int v2 = *(int*)value2;

    if(v1 == v2){
        return 0;
    } else if (v1 > v2) {
        return 1;
    } else {
        return -1;
    }
}

void *merge(void *value1, void *value2, void *ret){
    int v1 = *(int*)value1;
    int v2 = *(int*)value2;
    int v = v1 + v2;

    memcpy(ret, &v, sizeof(int));

    return ret;
}

void dynamic_arrays(){
    printf("%s\n", "dynamic array");

    dynamic_array_t *arr1 = array(sizeof(ElemType));
    printf("%p\n", arr1->data);
    printf("%d\n", arr1->capacity);
//    for(ElemType i = 0;i < 9; i++)
//    array_insert_first(arr1, &i);
    int e0 = 0;
    int e1 = 1;
    int e2 = 2;
    int e3 = 3;
    array_insert_first(arr1, &e0);
    array_insert_first(arr1, &e1);
    array_insert_first(arr1, &e2);
    array_insert_first(arr1, &e3);
    array_show(arr1, &to_string);

    array_destroy(&arr1);
    printf("%p\n\n", arr1);


    dynamic_array_t *arr = array_c(10, sizeof(ElemType));

    for(ElemType i = 0;i < 11; i++)
        array_insert_first(arr, &i);
    array_show(arr, &to_string);

    ElemType i = 100;
    array_insert(arr, 1, &i);
    array_show(arr, &to_string);

    ElemType e;
    array_get(arr, 1, &e);
    printf("e: %d\n", e);
    array_show(arr, &to_string);


    ElemType ret;
    array_remove(arr, 2, &ret);
    printf("ret: %d\n", ret);
    array_show(arr, &to_string);

    i = 100;
    int index = array_find(arr, &i);
    printf("%d\n", index);

    i = 100;
    array_remove_elem(arr, &i);
    array_show(arr, &to_string);

    ElemType last;
    array_get_last(arr, &last);
    printf("%d\n", last);

    ElemType first;
    array_get_first(arr, &first);
    printf("%d\n", first);
}

void array_stacks()
{
    printf("%s\n", "array stack");

    array_stack_t *stack1 = array_stack_c(10, sizeof(ElemType));
    array_stack_destroy(&stack1);
    printf("%p\n\n", stack1);


    array_stack_t *stack = array_stack(sizeof(ElemType));
    printf("%d\n", stack->array->capacity);

    int c = array_stack_capacity(stack);
    printf("c: %d\n", c);

    for(ElemType i = 0;i < 11; i++){
        array_stack_push(stack, &i);
    }
    array_stack_show(stack, &to_string);

    ElemType ret;
    array_stack_peek(stack, &ret);
    printf("%d\n", ret);
    array_stack_show(stack, &to_string);

    ElemType ret1;
    array_stack_pop(stack, &ret1);
    printf("%d\n", ret1);
    array_stack_show(stack, &to_string);
}

void array_queues()
{
    printf("%s\n", "array queue");

    array_queue_t *queue1 = array_queue_c(10, sizeof(ElemType));
    array_queue_destroy(&queue1);
    printf("%p\n\n", queue1);


    array_queue_t *queue = array_queue(sizeof(ElemType));
    printf("%d\n", queue->array->capacity);

    int c = array_queue_capacity(queue);
    printf("c: %d\n", c);

    for(ElemType i = 0;i < 11; i++){
        array_queue_enqueue(queue, &i);
    }
    array_queue_show(queue, &to_string);

    ElemType ret;
    array_queue_front(queue, &ret);
    printf("%d\n", ret);
    array_queue_show(queue, &to_string);

    ElemType ret1;
    array_queue_dequeue(queue, &ret1);
    printf("%d\n", ret1);
    array_queue_show(queue, &to_string);
}

void loop_queues()
{
    printf("%s\n", "loop queue");

    loop_queue_t *queue1 = loop_queue_c(10, sizeof(ElemType));
    loop_queue_destroy(&queue1);
    printf("%p\n\n", queue1);


    loop_queue_t *queue = loop_queue(sizeof(ElemType));
    printf("%d\n", queue->capacity);

    int c = loop_queue_capacity(queue);
    printf("c: %d\n", c);

    for(ElemType i = 0;i < 5; i++){
        loop_queue_enqueue(queue, &i);
    }
    loop_queue_show(queue, &to_string);

    ElemType ret;
    loop_queue_front(queue, &ret);
    printf("%d\n", ret);
    loop_queue_show(queue, &to_string);

    ElemType ret1;
    loop_queue_dequeue(queue, &ret1);
    printf("%d\n", ret1);
    loop_queue_show(queue, &to_string);

    ElemType ret2;
    loop_queue_dequeue(queue, &ret2);
    printf("%d\n", ret2);
    loop_queue_show(queue, &to_string);

    for(ElemType i = 0;i < 5; i++){
        loop_queue_enqueue(queue, &i);
    }
    loop_queue_show(queue, &to_string);

    ElemType ret3;
    loop_queue_dequeue(queue, &ret3);
    printf("%d\n", ret3);
    loop_queue_show(queue, &to_string);

    ElemType ret4;
    loop_queue_dequeue(queue, &ret4);
    printf("ret4: %d\n", ret4);
    loop_queue_show(queue, &to_string);

    for(ElemType i = 0;i < 5; i++){
        loop_queue_enqueue(queue, &i);
    }
    loop_queue_show(queue, &to_string);

    ElemType front;
    loop_queue_front(queue, &front);
    printf("front: %d\n", front);
    loop_queue_show(queue, &to_string);

    for(ElemType i = 0; i < 9; i++){
        ElemType ret;
        loop_queue_dequeue(queue, &ret);
        printf("ret4: %d\n", ret);
        loop_queue_show(queue, &to_string);
    }
}

void array_queue_time_test(int op_count)
{
    array_queue_t *array_q = array_queue(sizeof(ElemType));

    clock_t start_time = clock();

    srand((unsigned)time(NULL));  // 初始化随机数

    for(int i = 0; i < op_count; i++){
        int e = rand();
        array_queue_enqueue(array_q, &e);
    }
    for(int i = 0; i < op_count; i++){
        int e;
        array_queue_dequeue(array_q, &e);
    }

    clock_t end_time = clock();

    printf("array queue, time: %lf s\n", (double)(end_time-start_time)/CLOCKS_PER_SEC);
}

void loop_queue_time_test(int op_count)
{
    loop_queue_t *loop_q = loop_queue(sizeof(ElemType));

    clock_t start_time = clock();

    srand((unsigned)time(NULL));  // 初始化随机数

    for(int i = 0; i < op_count; i++){
        int e = rand();
        loop_queue_enqueue(loop_q, &e);
    }
    for(int i = 0; i < op_count; i++){
        int e;
        loop_queue_dequeue(loop_q, &e);
    }

    clock_t end_time = clock();

    printf("loop queue, time: %lf s\n", (double)(end_time-start_time)/CLOCKS_PER_SEC);
}

void linked_list_queue_time_test(int op_count)
{
    linked_list_queue_t *linked_list_q = linked_list_queue(sizeof(ElemType));

    clock_t start_time = clock();

    srand((unsigned)time(NULL));  // 初始化随机数

    for(int i = 0; i < op_count; i++){
        int e = rand();
        linked_list_queue_enqueue(linked_list_q, &e);
    }
    for(int i = 0; i < op_count; i++){
        int e;
        linked_list_queue_dequeue(linked_list_q, &e);
    }

    clock_t end_time = clock();

    printf("linked list queue, time: %lf s\n", (double)(end_time-start_time)/CLOCKS_PER_SEC);
}

void base_linked_list()
{
    printf("%s", "linked list");

    linked_list_t *linked_l = linked_list(sizeof(ElemType));
    printf("%d\n", linked_l->dummy_head->data_size);

    for(ElemType i = 0; i < 5; i++){
        linked_list_insert_first(linked_l, &i);
        linked_list_show(linked_l, &to_string);
    }

    ElemType e = 100;
    linked_list_insert(linked_l, 2, &e);
    linked_list_show(linked_l, &to_string);

    ElemType ret;
    linked_list_get(linked_l, 2, &ret);
    printf("%d\n", ret);

    ElemType s = 1000;
    linked_list_set(linked_l, 2, &s);
    linked_list_show(linked_l, &to_string);

    ElemType i = 4;
    int index = linked_list_contain(linked_l, &i);
    printf("%d\n", index);

    ElemType ret1;
    linked_list_remove_last(linked_l, &ret1);
    printf("%d\n", ret1);
    linked_list_show(linked_l, &to_string);

    linked_list_clear(linked_l);
    printf("%d\n", linked_l->size);
    printf("%p\n", linked_l->dummy_head->next);
    linked_list_show(linked_l, &to_string);

    linked_list_destroy(&linked_l);
    printf("%p\n", linked_l);
}

void linked_list_stack_test()
{
    printf("%s\n", "linked list stack");

    linked_list_stack_t *stack1 = linked_list_stack(sizeof(ElemType));
    linked_list_stack_destroy(&stack1);
    printf("%p\n\n", stack1);


    linked_list_stack_t *stack = linked_list_stack(sizeof(ElemType));
    printf("%d\n", stack->linked_l->size);

    int c = linked_list_stack_size(stack);
    printf("c: %d\n", c);

    for(ElemType i = 0;i < 11; i++){
        linked_list_stack_push(stack, &i);
    }
    linked_list_stack_show(stack, &to_string);

    ElemType ret;
    linked_list_stack_peek(stack, &ret);
    printf("%d\n", ret);
    linked_list_stack_show(stack, &to_string);

    ElemType ret1;
    linked_list_stack_pop(stack, &ret1);
    printf("%d\n", ret1);
    linked_list_stack_show(stack, &to_string);

    ElemType ret2;
    linked_list_stack_pop(stack, &ret2);
    printf("%d\n", ret2);
    linked_list_stack_show(stack, &to_string);

    linked_list_stack_clear(stack);
    linked_list_stack_show(stack, &to_string);

    linked_list_stack_destroy(&stack);
    printf("%p\n", stack);
}

void array_stack_time_test(int op_count)
{
    array_stack_t *array_s = array_stack(sizeof(ElemType));

    clock_t start_time = clock();

    srand((unsigned)time(NULL));  // 初始化随机数

    for(int i = 0; i < op_count; i++){
        int e = rand();
        array_stack_push(array_s, &e);
    }

    for(int i = 0; i < op_count; i++){
        int e;
        array_stack_pop(array_s, &e);
    }

    clock_t end_time = clock();

    printf("array stack, time: %lf s\n", (double)(end_time-start_time)/CLOCKS_PER_SEC);
}

void linked_list_stack_time_test(int op_count)
{
    linked_list_stack_t *linked_list_s = linked_list_stack(sizeof(ElemType));

    clock_t start_time = clock();

    srand((unsigned)time(NULL));  // 初始化随机数

    for(int i = 0; i < op_count; i++){
        int e = rand();
        linked_list_stack_push(linked_list_s, &e);
    }

    for(int i = 0; i < op_count; i++){
        int e;
        linked_list_stack_pop(linked_list_s, &e);
    }

    clock_t end_time = clock();

    printf("linked list stack, time: %lf s\n", (double)(end_time-start_time)/CLOCKS_PER_SEC);
}

void linked_list_queue_test()
{
    printf("%s\n", "linked list queue");

    linked_list_queue_t *queue1 = linked_list_queue(sizeof(ElemType));
    linked_list_queue_destroy(&queue1);
    printf("%p\n\n", queue1);


    linked_list_queue_t *queue = linked_list_queue(sizeof(ElemType));
    printf("%d\n", queue->size);

    int c = linked_list_queue_size(queue);
    printf("c: %d\n", c);

    for(ElemType i = 0;i < 11; i++){
        linked_list_queue_enqueue(queue, &i);
    }
    linked_list_queue_show(queue, &to_string);

    ElemType ret;
    linked_list_queue_front(queue, &ret);
    printf("%d\n", ret);
    linked_list_queue_show(queue, &to_string);

    ElemType ret1;
    linked_list_queue_dequeue(queue, &ret1);
    printf("%d\n", ret1);
    linked_list_queue_show(queue, &to_string);

    ElemType ret2;
    linked_list_queue_dequeue(queue, &ret2);
    printf("%d\n", ret2);
    linked_list_queue_show(queue, &to_string);
    printf("%d\n", queue->size);

    ElemType ret3 = 10;
    linked_list_queue_enqueue(queue, &ret3);
    linked_list_queue_show(queue, &to_string);
    printf("%d\n", queue->size);
}

void loop_linked_list_test()
{
    printf("%s\n", "loop linked list");

    loop_linked_list_t *loop_linked_l = loop_linked_list(sizeof(ElemType));
    printf("%d\n", loop_linked_l->dummy_head->data_size);

//    for(ElemType i = 0; i < 5; i++){
//        loop_linked_list_insert_first(loop_linked_l, &i);
//        loop_linked_list_show(loop_linked_l, &to_string);
//    }

    ElemType e = 100;
    loop_linked_list_insert(loop_linked_l, 0, &e);
    loop_linked_list_show(loop_linked_l, &to_string);

    ElemType e1 = 1000;
    loop_linked_list_insert(loop_linked_l, 0, &e1);
    loop_linked_list_show(loop_linked_l, &to_string);

    ElemType ret;
    loop_linked_list_get(loop_linked_l, 0, &ret);
    printf("ret: %d\n", ret);

    ElemType s = 1000;
    loop_linked_list_set(loop_linked_l, 0, &s);
    loop_linked_list_show(loop_linked_l, &to_string);

    ElemType i = 4;
    int have = loop_linked_list_contain(loop_linked_l, &i);
    printf("have: %d\n", have);

    ElemType ret1;
    loop_linked_list_remove_last(loop_linked_l, &ret1);
    printf("ret1: %d\n", ret1);
    loop_linked_list_show(loop_linked_l, &to_string);

    loop_linked_list_clear(loop_linked_l);
    printf("%d\n", loop_linked_l->size);
    printf("%p\n", loop_linked_l->dummy_head->next);
    printf("%p\n", loop_linked_l->dummy_head->prev);
    printf("%p\n", loop_linked_l->dummy_head);
    loop_linked_list_show(loop_linked_l, &to_string);

    loop_linked_list_destroy(&loop_linked_l);
    printf("%p\n", loop_linked_l);
}

void repeat_elem_bst_test()
{
    printf("repeat elem bst\n");
    repeat_elem_bst_t *repeat_elem_bst_tree = repeat_elem_bst(sizeof(ElemType));

    int num[15] = {41, 41, 41, 22, 58, 15, 33, 50, 63, 13, 37, 42, 53, 53, 53};
    for(int i = 0;i < sizeof(num) / sizeof(int); i++){
        repeat_elem_bst_add_r(repeat_elem_bst_tree, &num[i], &compare);
    }

    repeat_elem_bst_level_order_nr(repeat_elem_bst_tree, &to_string);

//    repeat_elem_bst_pre_order_r(repeat_elem_bst_tree, &to_string);
//
//    printf("\n");
//
//    repeat_elem_bst_pre_order_nr(repeat_elem_bst_tree, &to_string);
//
//    printf("\n");
//
//    repeat_elem_bst_in_order_r(repeat_elem_bst_tree, &to_string);
//
//    printf("\n");
//
//    repeat_elem_bst_post_order_r(repeat_elem_bst_tree, &to_string);
//
//    printf("\n");
//
//    repeat_elem_bst_level_order_nr(repeat_elem_bst_tree, &to_string);

//    ElemType i;
//    repeat_elem_bst_minimum_r(repeat_elem_bst_tree, &i);
//    printf("%d\n", i);
//    repeat_elem_bst_level_order_nr(repeat_elem_bst_tree, &to_string);
//
//    repeat_elem_bst_maximum_r(repeat_elem_bst_tree, &i);
//    printf("%d\n", i);
//
//    repeat_elem_bst_in_order_r(repeat_elem_bst_tree, &to_string);
//
//    printf("\n");
//
//    ElemType ret;
//    repeat_elem_bst_remove_minimum_r(repeat_elem_bst_tree, &ret);
//    repeat_elem_bst_remove_minimum_r(repeat_elem_bst_tree, &ret);
//    repeat_elem_bst_remove_minimum_r(repeat_elem_bst_tree, &ret);
//    repeat_elem_bst_remove_maximum_r(repeat_elem_bst_tree, &ret);
//    repeat_elem_bst_remove_maximum_r(repeat_elem_bst_tree, &ret);
//    printf("%d\n", ret);
//    repeat_elem_bst_level_order_nr(repeat_elem_bst_tree, &to_string);
//    repeat_elem_bst_in_order_r(repeat_elem_bst_tree, &to_string);
//
//    printf("\n");
//
//    repeat_elem_bst_remove_maximum_r(repeat_elem_bst_tree, &ret);
//    printf("%d\n", ret);
//    repeat_elem_bst_level_order_nr(repeat_elem_bst_tree, &to_string);
//    repeat_elem_bst_in_order_r(repeat_elem_bst_tree, &to_string);
//
//    printf("\n");
//
//    ElemType e = 50;
//    repeat_elem_bst_remove_r(repeat_elem_bst_tree, &e, &compare);
//    repeat_elem_bst_level_order_nr(repeat_elem_bst_tree, &to_string);

//    printf("\n");
//
//    repeat_elem_bst_remove_r(repeat_elem_bst_tree, &e, &compare);
//    repeat_elem_bst_level_order_nr(repeat_elem_bst_tree, &to_string);
//
//    printf("\n");
//
//    repeat_elem_bst_remove_r(repeat_elem_bst_tree, &e, &compare);
//    repeat_elem_bst_level_order_nr(repeat_elem_bst_tree, &to_string);

//    printf("\n");

//    e = 50;
//
//    int count = repeat_elem_bst_elem_count_r(repeat_elem_bst_tree, &e, &compare);
//    printf("%d\n", count);

//    printf("\n");

//    ElemType e = 50;
//    repeat_elem_bst_remove_r(repeat_elem_bst_tree, &e, &compare);
//    repeat_elem_bst_level_order_nr(repeat_elem_bst_tree, &to_string);
//    repeat_elem_bst_in_order_r(repeat_elem_bst_tree, &to_string);
//
//    printf("\n");
//
//    repeat_elem_bst_clear_r(bst_tree);
//    printf("%p\n",repeat_elem_bst_tree->root);
//
//    for(i = 0;i < sizeof(num) / sizeof(int); i++){
//        repeat_elem_bst_add_r(repeat_elem_bst_tree, &num[i], &compare);
//    }
//    repeat_elem_bst_in_order_r(repeat_elem_bst_tree, &to_string);
//
//    repeat_elem_bst_destroy(&repeat_elem_bst_tree);
//
//    printf("\n");
//
//    printf("%p\n", bst_tree);

//    ElemType e = 45;
//    ElemType i;
//    repeat_elem_bst_floor_r(repeat_elem_bst_tree, &e, &i, &compare);
//    printf("%d\n", i);
//
//    repeat_elem_bst_ceil_r(repeat_elem_bst_tree, &e, &i, &compare);
//    printf("%d\n", i);

//    ElemType i = 1;
//    int e = repeat_elem_bst_rank_r(repeat_elem_bst_tree, &i, &compare);
//    printf("%d\n", e);

    ElemType e;
    repeat_elem_bst_select_r(repeat_elem_bst_tree, 8, &e, &compare);
    printf("%d\n", e);

}

void basic_bst_test()
{
    printf("basic bst\n");
    basic_bst_t *basic_bst_tree = basic_bst(sizeof(ElemType));

    int num[11] = {41, 22, 58, 15, 33, 50, 63, 13, 37, 42, 53};
    for(int i = 0;i < sizeof(num) / sizeof(int); i++){
        basic_bst_add_r(basic_bst_tree, &num[i], &compare);
    }
    printf("size: %d\n", basic_bst_size(basic_bst_tree));

    basic_bst_level_order_nr(basic_bst_tree, &to_string);

    printf("\n");

    ElemType ret;
    basic_bst_remove_maximum_r(basic_bst_tree, &ret);
    printf("ret: %d\n", ret);
    printf("size: %d\n", basic_bst_size(basic_bst_tree));
    basic_bst_level_order_nr(basic_bst_tree, &to_string);

    printf("\n");

    basic_bst_remove_minimum_r(basic_bst_tree, &ret);
    printf("ret: %d\n", ret);
    printf("size: %d\n", basic_bst_size(basic_bst_tree));
    basic_bst_level_order_nr(basic_bst_tree, &to_string);

    printf("\n");

    ElemType e = 41;
    basic_bst_remove_r(basic_bst_tree, &e, &compare);
    printf("size: %d\n", basic_bst_size(basic_bst_tree));
    basic_bst_level_order_nr(basic_bst_tree, &to_string);
}

void bst_map_test()
{
    printf("bst map\n");
    bst_map_t *bst_map_tree = bst_map(sizeof(ElemType), sizeof(ElemType));

    int num[11] = {41, 22, 58, 15, 33, 50, 63, 13, 37, 42, 53};
    for(int i = 0;i < sizeof(num) / sizeof(int); i++){
        bst_map_add_r(bst_map_tree, &num[i], &num[i], &compare);
    }
    printf("size: %d\n", bst_map_size(bst_map_tree));

    bst_set_t *bst_s = bst_set(sizeof(num) / sizeof(int));
    bst_map_key_set_r(bst_map_tree, bst_s, &compare);
    int size = bst_set_size(bst_s);
    printf("bst_set size: %d\n", size);
    int e = 58;
    bool is = bst_set_contain(bst_s, &e, &compare);
    printf("%d\n", is);

//    printf("\n");
//
//    ElemType e = 41;
//    ElemType ret;
//    bst_map_remove_r(bst_map_tree, &e, &ret, &compare);
//    printf("size: %d\n", bst_map_size(bst_map_tree));
//    printf("ret: %d\n", ret);
//
//    printf("\n");
//
//    e = 53;
//    bst_map_get_r(bst_map_tree, &e, &ret, &compare);
//    printf("size: %d\n", bst_map_size(bst_map_tree));
//    printf("ret: %d\n", ret);
//
//    printf("\n");
//
//    e = 50;
//    ElemType value = 333;
//    bst_map_set(bst_map_tree, &e, &value, &compare);
//    printf("size: %d\n", bst_map_size(bst_map_tree));
//    bst_map_get_r(bst_map_tree, &e, &ret, &compare);
//    printf("size: %d\n", bst_map_size(bst_map_tree));
//    printf("ret: %d\n", ret);
}

void dynamic_array_max_heap_test()
{
    printf("dynamic array max heap\n");
//    dynamic_array_max_heap_t *dynamic_array_max_h = dynamic_array_max_heap_c(10, sizeof(ElemType));

    int num[11] = {41, 22, 58, 15, 33, 50, 63, 13, 37, 42, 53};
//    for(int i = 0;i < sizeof(num) / sizeof(int); i++){
//        dynamic_array_max_heap_add(dynamic_array_max_h, &num[i], &compare);
//    }
    dynamic_array_max_heap_t *dynamic_array_max_h = dynamic_array_max_heap_heapify(num, sizeof(num)/ sizeof(int), sizeof(int), &compare);
    printf("size: %d\n", dynamic_array_max_heap_size(dynamic_array_max_h));

//    int arr[11];
//    for(int i = 0; i < sizeof(arr) / sizeof(int); i++){
//        int ret;
//        dynamic_array_max_heap_extract_max(dynamic_array_max_h, &ret, &compare);
//        arr[i] = ret;
//    }
//
//    for(int i = 1; i < sizeof(arr) / sizeof(int); i++){
//        printf("%d\n", arr[i-1]);
//        if(arr[i-1]<arr[i]){
//            exit(OVERFLOW);
//        }
//    }
//
//    printf("finished heapify");

    ElemType i = 100;
    ElemType ret;
    dynamic_array_max_heap_replace(dynamic_array_max_h, &i, &ret, &compare);
    printf("%d\n", ret);
    dynamic_array_max_heap_extract_max(dynamic_array_max_h, &ret, &compare);
    printf("%d\n", ret);

    int size = dynamic_array_max_heap_size(dynamic_array_max_h);
    printf("size: %d\n", size);
    printf("\n");

    for(i = 0; i < size; i++){
        dynamic_array_max_heap_extract_max(dynamic_array_max_h, &ret, &compare);
        printf("%d\n", ret);
    }
}

void dynamic_array_max_heap_time_test(int op_count)
{
    dynamic_array_max_heap_t *dynamic_array_max_h = dynamic_array_max_heap(sizeof(ElemType));

    clock_t start_time = clock();

    srand((unsigned)time(NULL));  // 初始化随机数

    for(int i = 0; i < op_count; i++){
        int e = rand();
        dynamic_array_max_heap_add(dynamic_array_max_h, &e, &compare);
    }


    int arr[op_count];
    for(int i = 0; i < op_count; i++){
        int ret;
        dynamic_array_max_heap_extract_max(dynamic_array_max_h, &ret, &compare);
        arr[i] = ret;
    }

    for(int i = 1; i < op_count; i++){
        if(arr[i-1]<arr[i]){
            exit(OVERFLOW);
        }
    }

    clock_t end_time = clock();

    printf("dynamic array max heap, time: %lf s\n", (double)(end_time-start_time)/CLOCKS_PER_SEC);
}

void max_heap_priority_queue_test()
{
    printf("%s\n", "max heap priority queue");

    max_heap_priority_queue_t *queue1 = max_heap_priority_queue(sizeof(ElemType));
    max_heap_priority_queue_destroy(&queue1);
    printf("%p\n\n", queue1);


    max_heap_priority_queue_t *queue = max_heap_priority_queue(sizeof(ElemType));
    printf("%d\n", max_heap_priority_queue_size(queue));

    srand((unsigned)time(NULL));  // 初始化随机数

    for(int i = 0; i < 11; i++){
        int e = rand();
        max_heap_priority_queue_enqueue(queue, &e, &compare);
    }

    ElemType ret;
    max_heap_priority_queue_front(queue, &ret);
    printf("%d\n", ret);

    printf("\n");

    for(int i = 0; i < 11; i ++){
        max_heap_priority_queue_dequeue(queue, &ret, &compare);
        printf("%d\n", ret);
    }

    printf("%d\n", max_heap_priority_queue_size(queue));
}

void array_segment_tree_test()
{
    printf("%s\n", "array segment tree");
    int num[11] = {41, 22, 58, 15, 33, 50, 63, 13, 37, 42, 53};
    dynamic_array_t *a = array_segment_tree_array(num, sizeof(num)/ sizeof(int), sizeof(int));

    array_segment_tree_t *array_segment_t = array_segment_tree(sizeof(num)/ sizeof(int), sizeof(int));
    array_segment_tree_build(a, array_segment_t, 0, 0, sizeof(num)/ sizeof(int) - 1, &merge);
    array_segment_tree_show(array_segment_t, &to_string);

    int ret;
    array_segment_tree_query_r(array_segment_t, sizeof(num)/ sizeof(int), 0, 5, &ret, &merge);
    printf("%d\n", ret);

    ElemType e = 300;
    array_segment_tree_set_r(a, array_segment_t, 10, &e, &merge);
    array_get(a, 10, &ret);
    printf("%d\n", ret);
    array_segment_tree_show(array_segment_t, &to_string);

}

void union_find_1_test()
{
    printf("%s\n", "union find 1");

    union_find_1_t *u = union_find_1(10, sizeof(int));
    printf("%d\n", union_find_1_is_connected(u, 0, 9));
    union_find_1_union(u, 0 ,9);
    printf("%d\n", union_find_1_is_connected(u, 0, 9));

}

void union_find_2_test()
{
    printf("%s\n", "union find 2");

    union_find_2_t *u = union_find_2(10);
    printf("%d\n", union_find_2_is_connected(u, 0, 9));
    union_find_2_union(u, 0 ,9);
    printf("%d\n", union_find_2_is_connected(u, 0, 9));

}

void union_find_3_test()
{
    printf("%s\n", "union find 3");

    union_find_3_t *u = union_find_3(10);
    printf("%d\n", union_find_3_is_connected(u, 0, 9));
    union_find_3_union(u, 0 ,9);
    printf("%d\n", union_find_3_is_connected(u, 0, 9));
    union_find_3_union(u, 4 ,9);
    printf("%d\n", union_find_3_is_connected(u, 4, 0));
}

void union_find_4_test()
{
    printf("%s\n", "union find 4");

    union_find_4_t *u = union_find_4(10);
    printf("%d\n", union_find_4_is_connected(u, 0, 9));
    union_find_4_union(u, 0 ,9);
    printf("%d\n", union_find_4_is_connected(u, 0, 9));
    union_find_4_union(u, 4 ,9);
    printf("%d\n", union_find_4_is_connected(u, 4, 0));
    union_find_4_union(u, 2 ,1);
    printf("%d\n", union_find_4_is_connected(u, 2, 1));
    printf("%d\n", union_find_4_is_connected(u, 2, 9));
}

void union_find_5_test()
{
    printf("%s\n", "union find 5");

    union_find_5_t *u = union_find_5(10);
    printf("%d\n", union_find_5_is_connected(u, 0, 9));
    union_find_5_union(u, 0 ,9);
    printf("%d\n", union_find_5_is_connected(u, 0, 9));
    union_find_5_union(u, 5 ,9);
    printf("%d\n", union_find_5_is_connected(u, 5, 0));
    union_find_5_union(u, 2 ,1);
    printf("%d\n", union_find_5_is_connected(u, 2, 1));
    printf("%d\n", union_find_5_is_connected(u, 2, 9));
}

void union_find_6_test()
{
    printf("%s\n", "union find 6");

    union_find_6_t *u = union_find_6(10);
    printf("%d\n", union_find_6_is_connected(u, 0, 9));
    union_find_6_union(u, 0 ,9);
    printf("%d\n", union_find_6_is_connected(u, 0, 9));
    union_find_6_union(u, 6 ,9);
    printf("%d\n", union_find_6_is_connected(u, 6, 0));
    union_find_6_union(u, 2 ,1);
    printf("%d\n", union_find_6_is_connected(u, 2, 1));
    printf("%d\n", union_find_6_is_connected(u, 2, 9));
    union_find_6_union(u, 2 ,0);
    printf("%d\n", union_find_6_is_connected(u, 2, 9));

}

void avl_tree_test()
{
    printf("avl tree\n");
    avl_tree_t *avl_tree_tree = avl_tree(sizeof(ElemType), sizeof(ElemType));

    int num[16] = {41, 22, 58, 15, 66 ,77,88,99,199,33, 50, 63, 13, 37, 42, 53};
    for(int i = 0;i < sizeof(num) / sizeof(int); i++){
        avl_tree_add_r(avl_tree_tree, &num[i], &num[i], &compare);
    }
    printf("size: %d\n", avl_tree_size(avl_tree_tree));
    printf("is bst: %d\n", avl_tree_is_bst(avl_tree_tree, &compare));
    printf("is balance: %d\n", avl_tree_is_balance_r(avl_tree_tree));

    for(int i = 0;i < sizeof(num) / sizeof(int); i++){
        avl_tree_remove_r(avl_tree_tree, &num[i],NULL, &compare);
        printf("%d\n", num[i]);
        printf("size: %d\n", avl_tree_size(avl_tree_tree));
        printf("is bst: %d\n", avl_tree_is_bst(avl_tree_tree, &compare));
        printf("is balance: %d\n", avl_tree_is_balance_r(avl_tree_tree));
        if(!avl_tree_is_bst(avl_tree_tree, &compare) || !avl_tree_is_balance_r(avl_tree_tree))
            exit(OVERFLOW);
    }

    printf("avl tree success");

}

int main() {
//    dynamic_arrays();

//    array_stacks();

//    array_queues();

//    loop_queues();


    int op_count = 1000000;
//    array_queue_time_test(op_count);
//    loop_queue_time_test(op_count);
//    linked_list_queue_time_test(op_count);


//    base_linked_list();

//    linked_list_stack_test();

//    array_stack_time_test(op_count);
//    linked_list_stack_time_test(op_count);

//    linked_list_queue_test();

//    loop_linked_list_test();

//    basic_bst_test();

//    repeat_elem_bst_test();

//    bst_map_test();

//    dynamic_array_max_heap_test();
//    dynamic_array_max_heap_time_test(op_count);

//    max_heap_priority_queue_test();

//    array_segment_tree_test();

//    union_find_1_test();
//    union_find_2_test();
//    union_find_3_test();
//    union_find_6_test();

//    avl_tree_test();

//    long get_long(void);
//    long i = 0;
//    while (i >= 0){
//        i = get_long();
//        printf("%ld\n", i);
//    }


//    struct test {
//        int n;
//        int arr[];  // int arr[]，等价int* arr;
//    };


    int arr[2] = {1, 0};
    printf("%p\n", arr);
    printf("%p\n", &arr);
    return 0;
}

//long get_long(void)
//{
//    long input;
//    char ch;
//    while (scanf("%ld", &input) != 1){
//        while ((ch = getchar()) != '\n')
//            putchar(ch);
//        printf(" is not an integer.\nPlease enter an ");
//        printf("integer value, such as 25, -178, or 3: ");
//    }
//
//    while ((ch = getchar()) != '\n')
//        ;
//
//    return input;
//}


/*
 * 递归语句之前的语句执行顺序是从递归最外层到递归最内层
 * 递归语句之后的语句执行顺序是从递归最内层到递归最外层
 * */