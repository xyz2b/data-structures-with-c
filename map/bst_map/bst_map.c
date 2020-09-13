//
// Created by 焦宏宇 on 2020/2/15.
//

#include "bst_map.h"
#include <stdlib.h>
#include <string.h>

// 创建节点
bst_map_node_t *bst_map_node(void *key, int key_data_size, void *value, int value_data_size)
{
    bst_map_node_t *n = (bst_map_node_t *)malloc(sizeof(bst_map_node_t));
    void *k = (char *)malloc(key_data_size);
    void *v = (char *)malloc(value_data_size);

    if(!n || !k || !v){
        // 存储分配失败
        free(n);
        free(k);
        free(v);
        return NULL;
    }

    if(key != NULL)
        memcpy(k, key, key_data_size);
    if(value != NULL)
        memcpy(v, value, value_data_size);


    n->key = k;
    n->value = v;
    n->left = NULL;
    n->right = NULL;

    return n;
}

// 将一个节点拷贝给另一个节点
Status bst_map_node_copy(bst_map_node_t *src, bst_map_node_t *dst, int key_data_size, int value_data_size)
{
    dst->right = src->right;
    dst->left = src->left;

    memcpy(dst->key, src->key, key_data_size);
    memcpy(dst->value, src->value, value_data_size);

    return OK;
}

// 销毁节点
Status bst_map_node_destroy(bst_map_node_t **bst_n){
    free((*bst_n)->key);
    free((*bst_n)->value);
    (*bst_n)->key = NULL;
    (*bst_n)->value = NULL;

    (*bst_n)->left = NULL;
    (*bst_n)->right = NULL;
    free(*bst_n);
    *bst_n = NULL;

    return OK;
}

// 创建映射
bst_map_t *bst_map(int key_data_size, int value_data_size)
{
    bst_map_t *bst_map_tree = (bst_map_t *)malloc(sizeof(bst_map_t));

    if(!bst_map_tree){
        // 存储分配失败
        exit(OVERFLOW);
    }

    bst_map_tree->root = NULL;
    bst_map_tree->key_data_size = key_data_size;
    bst_map_tree->value_data_size = value_data_size;
    bst_map_tree->size = 0;

    return bst_map_tree;
}

// 映射的大小
int bst_map_size(bst_map_t *bst_map_tree)
{
    if(bst_map_tree == NULL){
        return OVERFLOW;
    }
    return bst_map_tree->size;
}

// 判断映射是否为空
bool bst_map_is_empty(bst_map_t *bst_map_tree)
{
    if(bst_map_tree == NULL){
        return OVERFLOW;
    }
    return bst_map_tree->size == 0;
}

// 向以node为根的二分搜索树中插入元素e，递归算法
// 返回插入新节点后二分搜索树的根
bst_map_node_t *bst_map_add(bst_map_t *bst_map_tree, bst_map_node_t *n, void *key, void *value, compare_s compare_t)
{
    if(n == NULL){
        bst_map_node_t *new = bst_map_node(key, bst_map_tree->key_data_size, value, bst_map_tree->value_data_size);
        bst_map_tree->size ++;
        return new;
    }

    if((*compare_t)(key, n->key) < 0)
        n->left = bst_map_add(bst_map_tree, n->left, key, value, compare_t);
    else if((*compare_t)(key, n->key) > 0)
        n->right = bst_map_add(bst_map_tree, n->right, key, value, compare_t);
    else // if((*compare_t)(key, n->key) == 0)
        memcpy(n->value, value, bst_map_tree->value_data_size);

    return n;
}

// 向二分搜索树中添加元素
Status bst_map_add_r(bst_map_t *bst_map_tree, void *key, void *value, compare_s compare_t)
{
    if(bst_map_tree == NULL)
        return OVERFLOW;

    bst_map_tree->root = bst_map_add(bst_map_tree, bst_map_tree->root, key, value, compare_t);

    return OK;
}

// 获取key所在的节点， 递归算法
bst_map_node_t *bst_map_get_node(bst_map_t *bst_map_tree, bst_map_node_t *n, void *key, bst_map_node_t *ret_node, compare_s compare_t)
{
    if(n == NULL){
        return NULL;
    }

    if((*compare_t)(key, n->key) == 0){
        // 将源链表中的节点复制一份新的，避免节点被销毁之后，指针指向不对，用于获取源链表中数据
        if(ret_node != NULL){
            memcpy(ret_node, n, sizeof(bst_map_node_t));
            return ret_node;
        }
        // 获取源链表中的节点，节点销毁，数据即不存在，用于修改源链表中数据
        return n;
    }
    else if((*compare_t)(key, n->key) < 0)
        return bst_map_get_node(bst_map_tree, n->left, key, ret_node, compare_t);
    else // (*compare_t)(e, n->data) > 0
        return bst_map_get_node(bst_map_tree, n->right, key, ret_node, compare_t);
}

// 是否包含key
bool bst_map_contain_r(bst_map_t *bst_map_tree, void *key, compare_s compare_t)
{
    if(bst_map_tree == NULL)
        return OVERFLOW;

    return bst_map_get_node(bst_map_tree, bst_map_tree->root, key, NULL, compare_t) != NULL;
}

// 获取key对应的value
void *bst_map_get_r(bst_map_t *bst_map_tree, void *key, void *ret_value, compare_s compare_t)
{
    bst_map_node_t *bst_map_n = bst_map_node(key, bst_map_tree->key_data_size, NULL, bst_map_tree->value_data_size);
    // 单独赋值给一个指针的原因是，如果返回了NULL，直接赋值给上面创建的节点的指针，会导致上面创建的节点无法销毁
    bst_map_node_t *ret = bst_map_get_node(bst_map_tree, bst_map_tree->root, key, bst_map_n, compare_t);

    if(ret != NULL){
        memcpy(ret_value, ret->value, bst_map_tree->value_data_size);
        bst_map_node_destroy(&bst_map_n);
        return ret_value;
    }

    bst_map_node_destroy(&bst_map_n);

    return ret;
}

// 修改key的value
Status bst_map_set(bst_map_t *bst_map_tree, void *key, void *value, compare_s compare_t)
{
    bst_map_node_t *bst_map_n = bst_map_get_node(bst_map_tree, bst_map_tree->root, key, NULL, compare_t);

    if(bst_map_n == NULL){
        exit(OVERFLOW);
    }

    memcpy(bst_map_n->value, value, bst_map_tree->value_data_size);

    return OK;
}

// 返回以node为根的二分搜索树的最小值所在的节点， 递归算法
bst_map_node_t *bst_map_minimum(bst_map_node_t *n, bst_map_node_t *minimum_n, int key_data_size, int value_data_size)
{
    if(n->left == NULL){
        // n是指向节点的指针，所以不能直接返回该指针，需要用一块内存来接收它所指向的那块内存
        // 但是直接将n的整个内存拷贝走，会把n->data数据区域的指针也拷贝走，导致改变了接收方的数据域的data指针
        // 所以应该使用一对一赋值的方式将n的left/right/tree_size这些非自己申请内存的变量赋值给接收方，然后对于数据区域data这种自主管理内存的数据，使用memcpy进行内存赋值
        // n->data是指向数据的指针，所以不能直接返回该指针，需要用一块内存来接收它所指向的那块内存
        bst_map_node_copy(n, minimum_n, key_data_size, value_data_size);

        return minimum_n;
    }

    return bst_map_minimum(n->left, minimum_n, key_data_size, value_data_size);

}

// 删除以node为根的二分搜索树的最小节点
// 返回删除最小节点之后新的二分搜索树的根
bst_map_node_t *bst_map_remove_minimum(bst_map_t *bst_map_tree, bst_map_node_t *n)
{
    if(n->left == NULL){
        bst_map_node_t *right_node = n->right;
        n->right = NULL;
        bst_map_node_destroy(&n);
        bst_map_tree->size --;
        return right_node;
    }

    n->left = bst_map_remove_minimum(bst_map_tree, n->left);

    return n;
}

// 删除以node为根的二分搜索树中的元素key，递归算法
// 返回删除节点后新的二分搜索树的根
bst_map_node_t *bst_map_remove(bst_map_t *bst_map_tree, bst_map_node_t *n, void *key, compare_s compare_t)
{
    if(n == NULL)
        return NULL;

    if ((*compare_t)(key, n->key) < 0) {
        n->left = bst_map_remove(bst_map_tree, n->left, key, compare_t);
        return n;
    } else if((*compare_t)(key, n->key) > 0){
        n->right = bst_map_remove(bst_map_tree, n->right, key, compare_t);
        return n;
    } else{ // e = n->data
        // 待删除节点左子树为空的情况
        if(n->left == NULL){
            bst_map_node_t *right_node = n->right;
            n->right = NULL;
            bst_map_node_destroy(&n);
            bst_map_tree->size --;
            return right_node;
        }

        // 待删除节点右子树为空的情况
        if(n->right == NULL){
            bst_map_node_t *left_node = n->left;
            n->left = NULL;
            bst_map_node_destroy(&n);
            bst_map_tree->size --;
            return left_node;
        }

        // 待删除节点左右子树都不为空的情况
        // 找到比待删除节点大的最小节点，即待删除节点右子树的最小节点
        // 用这个节点代替待删除节点的位置
        bst_map_node_t *successor =  bst_map_node(NULL, bst_map_tree->key_data_size, NULL, bst_map_tree->value_data_size);
        bst_map_minimum(n->right, successor, bst_map_tree->key_data_size, bst_map_tree->value_data_size);
        successor->right = bst_map_remove_minimum(bst_map_tree, n->right);
        successor->left = n->left;

        bst_map_node_destroy(&n);

        return successor;
    }
}

// 删除二分搜索数中key的元素
void *bst_map_remove_r(bst_map_t *bst_map_tree, void *key, void *ret_value, compare_s compare_t)
{
    if(bst_map_is_empty(bst_map_tree))
        exit(OVERFLOW);

    bst_map_node_t *bst_map_n = bst_map_node(key, bst_map_tree->key_data_size, NULL, bst_map_tree->value_data_size);
    // 单独赋值给一个指针的原因是，如果返回了NULL，直接赋值给上面创建的节点的指针，会导致上面创建的节点无法销毁
    bst_map_node_t *ret = bst_map_get_node(bst_map_tree, bst_map_tree->root, key, bst_map_n, compare_t);

    if(ret != NULL){
        memcpy(ret_value, ret->value, bst_map_tree->value_data_size);
        bst_map_tree->root = bst_map_remove(bst_map_tree, bst_map_tree->root, key, compare_t);
        return ret_value;
    }

    bst_map_node_destroy(&bst_map_n);

    return NULL;
}


// 返回以node为根的二分搜索树中的key的集合
bst_set_t *bst_map_key_set(bst_map_node_t *n, bst_set_t *set, compare_s compare_t)
{
    if(n == NULL){
        return NULL;
    }

    bst_set_add(set, n->key, compare_t);
    bst_map_key_set(n->left, set, compare_t);
    bst_map_key_set(n->right, set, compare_t);

    return set;
}

// 返回key的集合
bst_set_t *bst_map_key_set_r(bst_map_t *bst_map_tree, bst_set_t *set, compare_s compare_t)
{
    return bst_map_key_set(bst_map_tree->root, set, compare_t);
}

// 清空以node为根的二分搜索树
void bst_map_clear(bst_map_node_t **n)
{
    if(*n == NULL){
        return;
    }

    bst_map_clear(&((*n)->left));
    bst_map_clear(&((*n)->right));

    bst_map_node_destroy(n);

}

// 清空二分搜索树
Status bst_map_clear_r(bst_map_t *bst_map_tree)
{
    bst_map_clear(&(bst_map_tree->root));
    bst_map_tree->size = 0;

    return OK;
}


// 销毁二分搜索树
Status bst_map_destroy(bst_map_t **bst_map_tree)
{
    bst_map_clear_r(*bst_map_tree);
    *bst_map_tree = NULL;

    return OK;
}

