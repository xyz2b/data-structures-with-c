//
// Created by 焦宏宇 on 2020/2/10.
//

#ifndef DATA_STRUCTURES_DOUBLE_LINKED_LIST_H
#define DATA_STRUCTURES_DOUBLE_LINKED_LIST_H
#include <stdbool.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define OVERFLOW -1
typedef int Status;


typedef struct double_node_s
{
    void *data;  /*数据域*/
    int data_size; /*数据域元数的大小*/
    struct double_node_s *next, *prev; /*指针域*/
} double_node_s;

typedef struct double_linked_list_s
{
    int size;
    int data_size; /*数据域元数的大小*/
    double_node_s *dummy_head;
}double_linked_list_t;

typedef Status (*to_string_s)(void *value, char *string);

double_linked_list_t *double_linked_list(int data_size);
int double_linked_list_size(double_linked_list_t *double_linked_l);
bool double_linked_list_is_empty(double_linked_list_t *double_linked_l);
Status double_linked_list_insert(double_linked_list_t *double_linked_l, int index, void *e);
Status double_linked_list_insert_first(double_linked_list_t *double_linked_l, void *e);
Status double_linked_list_insert_last(double_linked_list_t *double_linked_l, void *e);
Status double_linked_list_get(double_linked_list_t *double_linked_l, int index, void *ret);
Status double_linked_list_get_first(double_linked_list_t *double_linked_l, void *ret);
Status double_linked_list_get_last(double_linked_list_t *double_linked_l, void *ret);
Status double_linked_list_set(double_linked_list_t *double_linked_l, int index, void *e);
bool double_linked_list_contain(double_linked_list_t *double_linked_l, void *e);
Status double_linked_list_show(double_linked_list_t *double_linked_l, to_string_s to_string_t);
Status double_linked_list_remove(double_linked_list_t *double_linked_l, int index, void *ret);
Status double_linked_list_remove_first(double_linked_list_t *double_linked_l, void *ret);
Status double_linked_list_remove_last(double_linked_list_t *double_linked_l, void *ret);
Status double_linked_list_clear(double_linked_list_t *double_linked_l);
Status double_linked_list_destroy(double_linked_list_t **double_linked_l);



#endif //DATA_STRUCTURES_DOUBLE_LINKED_LIST_H
