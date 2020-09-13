//
// Created by 焦宏宇 on 2020/2/19.
//

#include "map_trie.h"
#include <stdlib.h>

// 初始化节点 with is_word
map_trie_node_t *map_trie_node_w(bool is_word)
{
    map_trie_node_t *map_t = malloc(sizeof(map_trie_node_t));
    if(!map_t){
        exit(OVERFLOW);
    }
    bst_map_t *bst_m = bst_map(sizeof(char), sizeof(map_trie_node_t));

    map_t->next = bst_m;
    map_t->is_word = is_word;

    return map_t;
}

// 初始化节点
map_trie_node_t *map_trie_node()
{
    map_trie_node_t *map_t = malloc(sizeof(map_trie_node_t));
    if(!map_t){
        exit(OVERFLOW);
    }
    bst_map_t *bst_m = bst_map(sizeof(char), sizeof(map_trie_node_t));

    map_t->next = bst_m;
    map_t->is_word = false;

    return map_t;
}

// 销毁节点
Status map_trie_node_destroy(map_trie_node_t **map_trie_n)
{
    bst_map_destroy(&((*map_trie_n)->next));

    free(*map_trie_n);
    *map_trie_n = NULL;

    return OK;
}

// 初始化字典树
map_trie_t *map_trie()
{
    map_trie_t *map_t = malloc(sizeof(map_trie_t));
    if(!map_t){
        exit(OVERFLOW);
    }
    map_trie_node_t *trie_n = map_trie_node();

    map_t->size = 0;
    map_t->root = trie_n;

    return map_t;
}

// 获取字典树的大小，即单词的数量
int map_trie_size(map_trie_t *map_t)
{
    return map_t->size;
}

// 向以node为根的树中添加字符串e，递归算法
Status map_trie_add(map_trie_node_t *map_trie_n, map_trie_t *map_t, char *e, compare_s compare_t)
{
    // 字符串匹配到最后，即表示字符串中所有字符在trie中已经存在
    if((*e) == '\0'){
        if(!map_trie_n->is_word){
            map_trie_n->is_word = true;
            map_t->size++;
            return OK;
        }
    }
    // 对应的字符映射不存在，即字符节点不存在，就新建
    if(bst_map_get_r(map_trie_n->next, e, NULL, compare_t) == NULL){
        map_trie_node_t *map_node_new = map_trie_node();
        bst_map_add_r(map_trie_n->next, e, map_node_new, compare_t);
        map_t->size++;
        return OK;
    }

    map_trie_node_t *map_node_e = bst_map_get_r(map_trie_n->next, e, NULL, compare_t);
    return map_trie_add(map_node_e, map_t, e + 1, compare_t);
}

// 向树中添加字符串e
Status map_trie_add_r(map_trie_t *map_t, char *e, compare_s compare_t)
{
    map_trie_add(map_t->root, map_t, e, compare_t);

    return OK;
}

// 向树中添加字符串e，非递归算法
Status map_trie_add_nr(map_trie_t *map_t, char *e, compare_s compare_t)
{
    map_trie_node_t *cur_node = map_t->root;
    while ((*e) != '\0'){
        if(bst_map_get_r(cur_node->next, e, NULL, compare_t) == NULL){
            map_trie_node_t *map_node_new = map_trie_node();
            bst_map_add_r(cur_node->next, e, map_node_new, compare_t);
            return OK;
        }
        cur_node = bst_map_get_r(cur_node->next, e, NULL, compare_t);
        e++;
    }
    if(!cur_node->is_word){
        cur_node->is_word = true;
        map_t->size ++;
    }
    return OK;
}

// 判断以node为根的树中是否存在字符串e，递归算法
bool map_trie_contain(map_trie_node_t *map_trie_n, char *e, compare_s compare_t)
{
    // 字符串匹配到最后，即表示字符串中所有字符在trie中已经存在
    if((*e) == '\0'){
        return map_trie_n->is_word;
    }
    // 对应的字符映射不存在，即字符节点不存在
    if(bst_map_get_r(map_trie_n->next, e, NULL, compare_t) == NULL){
        return false;
    }

    map_trie_node_t *map_node_e = bst_map_get_r(map_trie_n->next, e, NULL, compare_t);
    return map_trie_contain(map_node_e, e + 1, compare_t);
}

// 判断树中是否存在字符串e
bool map_trie_contain_r(map_trie_t *map_t, char *e, compare_s compare_t)
{
    return map_trie_contain(map_t->root, e, compare_t);
}

// 判断以node为根的树中是否存在字符串e，支持.通配符，递归算法
bool map_trie_search(map_trie_node_t *map_trie_n, char *e, compare_s compare_t)
{
    // 字符串匹配到最后，即表示字符串中所有字符在trie中已经存在
    if((*e) == '\0'){
        return map_trie_n->is_word;
    }

    // 考虑字符串中e包含.的情况
    if((*e) != '.'){
        // 对应的字符映射不存在，即字符节点不存在
        if(bst_map_get_r(map_trie_n->next, e, NULL, compare_t) == NULL){
            return false;
        }

        map_trie_node_t *map_node_e = bst_map_get_r(map_trie_n->next, e, NULL, compare_t);
        return map_trie_search(map_node_e, e + 1, compare_t);
    } else { // (*e) == '.'，即需要遍历该节点对应next的映射的所有key，对于每个key，都找到其所在的节点，然后以每个key所在的节点作为根继续向下搜索字符串e剩下的字符
        bst_set_t *bst_s = bst_set(sizeof(char));
        bst_map_key_set_r(map_trie_n->next, bst_s, compare_t);
        for(int i = 0;i < bst_set_size(bst_s); i++){
            if(bst_set_is_empty(bst_s))
                break;
            char next_e;
            bst_set_remove_maximum(bst_s, &next_e);
            map_trie_node_t *next_n = bst_map_get_r(map_trie_n->next, &next_e, NULL, compare_t);
            if(map_trie_search(next_n, e + 1, compare_t))
                return true;
        }
        return false;
    }
}

// 判断树中是否存在字符串e，支持.通配符
bool map_trie_search_r(map_trie_t *map_t, char *e, compare_s compare_t)
{
    return map_trie_search(map_t->root, e, compare_t);
}

// 判断树中是否存在字符串e，非递归算法
Status map_trie_contain_nr(map_trie_t *map_t, char *e, compare_s compare_t)
{
    map_trie_node_t *cur_node = map_t->root;
    while ((*e) != '\0'){
        if(bst_map_get_r(cur_node->next, e, NULL, compare_t) == NULL){
            return false;
        }
        cur_node = bst_map_get_r(cur_node->next, e, NULL, compare_t);
        e++;
    }
    return cur_node->is_word;
}

// 判断以node为根的树中是否存在以字符串e为前缀的word，递归算法
int map_trie_is_prefix(map_trie_node_t *map_trie_n, char *e, compare_s compare_t)
{
    // 字符串匹配到最后，即表示字符串中所有字符在trie中已经存在
    if((*e) == '\0'){
        return true;
    }
    // 对应的字符映射不存在，即字符节点不存在，就新建
    if(bst_map_get_r(map_trie_n->next, e, NULL, compare_t) == NULL){
        return false;
    }

    map_trie_node_t *map_node_e = bst_map_get_r(map_trie_n->next, e, NULL, compare_t);
    return map_trie_contain(map_node_e, e + 1, compare_t);
}

// 判断树中是否存在以字符串e为前缀的word
int map_trie_is_prefix_r(map_trie_t *map_t, char *e, compare_s compare_t)
{
    return map_trie_is_prefix(map_t->root, e, compare_t);
}

// 判断树中是否存在字符串e，非递归算法
Status map_trie_is_prefix_nr(map_trie_t *map_t, char *e, compare_s compare_t)
{
    map_trie_node_t *cur_node = map_t->root;
    while ((*e) != '\0'){
        if(bst_map_get_r(cur_node->next, e, NULL, compare_t) == NULL){
            return false;
        }
        cur_node = bst_map_get_r(cur_node->next, e, NULL, compare_t);
        e++;
    }
    return true;
}

// 删除以node为根中的字符串e，返回删除后的根节点。递归算法
// 后序遍历
map_trie_node_t *map_trie_delete(map_trie_node_t *map_trie_n, char *e, compare_s compare_t)
{
    // 字符串匹配到最后，即表示字符串中所有字符在trie中已经存在
    if((*e) == '\0'){
        // 匹配到字符串
        if(map_trie_n->is_word){
            if(bst_map_size(map_trie_n->next) == 0){
                // 当前节点的next为空，直接删除
                map_trie_node_destroy(&map_trie_n);
                return NULL;
            } else {
                // 当前节点的next不为空，将is_word改为false即可
                map_trie_n->is_word = false;
                return map_trie_n;
            }
        }
        // 不匹配字符串
        return map_trie_n;
    }
    // 对应的字符映射不存在，即字符节点不存在，不匹配字符串
    if(bst_map_get_r(map_trie_n->next, e, NULL, compare_t) == NULL){
        return map_trie_n;
    }

    map_trie_node_t *map_trie_next_node_e = bst_map_get_r(map_trie_n->next, e, NULL, compare_t);
    // 继续在当前节点的next节点中，删除e+1之后的字符串
    map_trie_node_t *delete_node = map_trie_delete(map_trie_next_node_e, e + 1, compare_t);

    // 如果当前节点的next节点已被删除
    if(delete_node == NULL) {
        // 删除当前节点map中关于字符e的映射
        bst_map_remove_r(map_trie_n->next, e, NULL, compare_t);
        // 如果当前节点map中为空，即没有next节点，即可以直接被删除
        if(bst_map_size(map_trie_n->next) == 0){
            map_trie_node_destroy(&map_trie_n);
        }
    }

    return map_trie_n;

}

// 删除字符串e
Status map_trie_delete_r(map_trie_t *map_t, char *e, compare_s compare_t)
{
    map_t->root = map_trie_delete(map_t->root, e, compare_t);
    return OK;
}

void map_trie_clear(map_trie_node_t *map_trie_n, compare_s compare_t) {
    if (bst_map_size(map_trie_n->next) == 0) {
        map_trie_node_destroy(&map_trie_n);
        return;
    }

    bst_set_t *bst_s = bst_set(sizeof(char));
    bst_map_key_set_r(map_trie_n->next, bst_s, compare_t);
    for (int i = 0; i < bst_set_size(bst_s); i++) {
        char next_e;
        bst_set_remove_maximum(bst_s, &next_e);
        map_trie_node_t *next_n = bst_map_get_r(map_trie_n->next, &next_e, NULL, compare_t);
        map_trie_clear(next_n, compare_t);
    }

    map_trie_node_destroy(&map_trie_n);

}

// 清空trie
Status map_trie_clear_r(map_trie_t *map_t, compare_s compare_t)
{
    map_trie_clear(map_t->root, compare_t);

    map_trie_node_t *trie_n = map_trie_node();
    map_t->size = 0;
    map_t->root = trie_n;

    return OK;
}

// 销毁trie
Status map_trie_destroy_r(map_trie_t **map_t, compare_s compare_t)
{
    map_trie_clear((*map_t)->root, compare_t);
    free(*map_t);
    *map_t = NULL;

    return OK;
}

