//
// Created by 焦宏宇 on 2020/2/8.
//

#ifndef DATASTRUCTURES_BASE_LINKED_LIST_H
#define DATASTRUCTURES_BASE_LINKED_LIST_H
#include <stdbool.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define OVERFLOW -1
typedef int Status;



typedef struct node_s
{
    void *data;  /*数据域*/
    int data_size; /*数据域元数的大小*/
    struct node_s *next; /*指针域*/
} node_s;

typedef struct linked_list_s
{
    int size;
    int data_size; /*数据域元数的大小*/
    node_s *dummy_head;
}linked_list_t;

typedef Status (*to_string_s)(void *value, char *string);
typedef int (*compare_s)(void *value1, void *value2);

Status node_show(node_s *n, to_string_s to_string_t);
node_s *node_n(node_s *next, int data_size, void *e);
node_s *node_e(int data_size, void *e);
Status node_destroy(node_s **n);

linked_list_t *linked_list(int data_size);
int linked_list_size(linked_list_t *linked_l);
bool linked_list_is_empty(linked_list_t *linked_l);
Status linked_list_insert(linked_list_t *linked_l, int index, void *e);
Status linked_list_insert_first(linked_list_t *linked_l, void *e);
Status linked_list_insert_last(linked_list_t *linked_l, void *e);
Status linked_list_get(linked_list_t *linked_l, int index, void *ret);
Status linked_list_get_first(linked_list_t *linked_l, void *ret);
Status linked_list_get_last(linked_list_t *linked_l, void *ret);
Status linked_list_set(linked_list_t *linked_l, int index, void *e);
bool linked_list_contain(linked_list_t *linked_l, void *e);
Status linked_list_show(linked_list_t *linked_l, to_string_s to_string_t);
Status linked_list_remove(linked_list_t *linked_l, int index, void *ret);
Status linked_list_remove_first(linked_list_t *linked_l, void *ret);
Status linked_list_remove_last(linked_list_t *linked_l, void *ret);
Status linked_list_clear(linked_list_t *linked_l);
Status linked_list_destroy(linked_list_t **linked_l);
Status linked_list_remove_elem(linked_list_t *linked_l, void *e, compare_s compare_t);
int linked_list_elem_index(linked_list_t *linked_l, void *e, compare_s compare_t);

#endif //DATASTRUCTURES_BASE_LINKED_LIST_H
