//
// Created by 焦宏宇 on 2020/2/10.
//

#ifndef DATA_STRUCTURES_loop_LINKED_LIST_H
#define DATA_STRUCTURES_loop_LINKED_LIST_H
#include <stdbool.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define OVERFLOW -1
typedef int Status;


typedef struct loop_node_s
{
    void *data;  /*数据域*/
    int data_size; /*数据域元数的大小*/
    struct loop_node_s *next, *prev; /*指针域*/
} loop_node_s;

typedef struct loop_linked_list_s
{
    int size;
    int data_size; /*数据域元数的大小*/
    loop_node_s *dummy_head;
}loop_linked_list_t;

typedef Status (*to_string_s)(void *value, char *string);

loop_linked_list_t *loop_linked_list(int data_size);
int loop_linked_list_size(loop_linked_list_t *loop_linked_l);
bool loop_linked_list_is_empty(loop_linked_list_t *loop_linked_l);
Status loop_linked_list_insert(loop_linked_list_t *loop_linked_l, int index, void *e);
Status loop_linked_list_insert_first(loop_linked_list_t *loop_linked_l, void *e);
Status loop_linked_list_insert_last(loop_linked_list_t *loop_linked_l, void *e);
Status loop_linked_list_get(loop_linked_list_t *loop_linked_l, int index, void *ret);
Status loop_linked_list_get_first(loop_linked_list_t *loop_linked_l, void *ret);
Status loop_linked_list_get_last(loop_linked_list_t *loop_linked_l, void *ret);
Status loop_linked_list_set(loop_linked_list_t *loop_linked_l, int index, void *e);
bool loop_linked_list_contain(loop_linked_list_t *loop_linked_l, void *e);
Status loop_linked_list_show(loop_linked_list_t *loop_linked_l, to_string_s to_string_t);
Status loop_linked_list_remove(loop_linked_list_t *loop_linked_l, int index, void *ret);
Status loop_linked_list_remove_first(loop_linked_list_t *loop_linked_l, void *ret);
Status loop_linked_list_remove_last(loop_linked_list_t *loop_linked_l, void *ret);
Status loop_linked_list_clear(loop_linked_list_t *loop_linked_l);
Status loop_linked_list_destroy(loop_linked_list_t **loop_linked_l);



#endif //DATA_STRUCTURES_loop_LINKED_LIST_H
