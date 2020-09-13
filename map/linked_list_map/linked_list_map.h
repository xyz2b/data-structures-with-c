//
// Created by 焦宏宇 on 2020/2/15.
//

#ifndef DATA_STRUCTURES_LINKED_LIST_MAP_H
#define DATA_STRUCTURES_LINKED_LIST_MAP_H
#include <stdbool.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define OVERFLOW -1
typedef int Status;



typedef struct linked_list_map_node_s
{
    void *key;
    void *value;
    int key_data_size;
    int value_data_size;
    struct linked_list_map_node_s *next; /*指针域*/
} linked_list_map_node_s;

typedef struct linked_list_map_s
{
    int size;
    int key_data_size;
    int value_data_size;
    linked_list_map_node_s *dummy_head;
}linked_list_map_t;

typedef Status (*to_string_s)(void *value, char *string);
typedef int (*compare_s)(void *value1, void *value2);


linked_list_map_t *linked_list_map(int key_data_size, int value_data_size);
int linked_list_map_size(linked_list_map_t *linked_list_mp);
bool linked_list_map_is_empty(linked_list_map_t *linked_list_mp);
bool linked_list_map_contain(linked_list_map_t *linked_list_mp, void *key);
linked_list_map_node_s *linked_list_map_get_node(linked_list_map_t *linked_list_mp, linked_list_map_node_s *ret_node, void *key, compare_s compare_t);
void *linked_list_map_get(linked_list_map_t *linked_list_mp, void *key, void *ret_value, compare_s compare_t);
Status linked_list_map_add(linked_list_map_t *linked_list_mp, void *key, void *value, compare_s compare_t);
Status linked_list_map_set(linked_list_map_t *linked_list_mp, void *key, void *value, compare_s compare_t);
void *linked_list_map_remove(linked_list_map_t *linked_list_mp, void *key, void *ret_value, compare_s compare_t);
Status linked_list_map_show(linked_list_map_t *linked_list_mp, to_string_s to_string_t);
Status linked_list_map_clear(linked_list_map_t *linked_list_mp);
Status linked_list_map_destroy(linked_list_map_t **linked_list_mp);

#endif //DATA_STRUCTURES_LINKED_LIST_MAP_H
