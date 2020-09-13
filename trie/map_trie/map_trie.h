//
// Created by 焦宏宇 on 2020/2/19.
//

#ifndef DATA_STRUCTURES_MAP_TRIE_H
#define DATA_STRUCTURES_MAP_TRIE_H

#include "../../map/bst_map/bst_map.h"

// is_word标识该字符是否是单词的结尾
// next指针指向一个映射，映射中包含字符到node映射，即该节点的下一个节点的字符和下一个节点之间的映射
typedef struct map_trie_node_s {
    bool is_word;
    bst_map_t *next;
} map_trie_node_t;

// size表示单词的数量
typedef struct map_trie_s {
    int size;
    map_trie_node_t *root;
} map_trie_t;

map_trie_t *map_trie();
int map_trie_size(map_trie_t *map_t);
Status map_trie_add_r(map_trie_t *map_t, char *e, compare_s compare_t);
Status map_trie_add_nr(map_trie_t *map_t, char *e, compare_s compare_t);
bool map_trie_contain_r(map_trie_t *map_t, char *e, compare_s compare_t);
bool map_trie_search_r(map_trie_t *map_t, char *e, compare_s compare_t);
Status map_trie_contain_nr(map_trie_t *map_t, char *e, compare_s compare_t);
int map_trie_is_prefix_r(map_trie_t *map_t, char *e, compare_s compare_t);
Status map_trie_is_prefix_nr(map_trie_t *map_t, char *e, compare_s compare_t);
Status map_trie_delete_r(map_trie_t *map_t, char *e, compare_s compare_t);
Status map_trie_clear_r(map_trie_t *map_t, compare_s compare_t);
Status map_trie_destroy_r(map_trie_t **map_t, compare_s compare_t);


#endif //DATA_STRUCTURES_MAP_TRIE_H
