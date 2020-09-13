//
// Created by 焦宏宇 on 2020/2/21.
//

#include "avl_tree.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// 创建节点
avl_tree_node_t *avl_tree_node(void *key, int key_data_size, void *value, int value_data_size)
{
    avl_tree_node_t *n = (avl_tree_node_t *)malloc(sizeof(avl_tree_node_t));
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
    n->height = 1;

    return n;
}

// 获取节点的高度
int avl_tree_node_get_height(avl_tree_node_t *n)
{
    if(n == NULL)
        return 0;
    return n->height;
}

// 获取节点的平衡因子
int avl_tree_node_get_balance_factor(avl_tree_node_t *n)
{
    if(n == NULL)
        return 0;
    return avl_tree_node_get_height(n->left) - avl_tree_node_get_height(n->right);
}

// 将一个节点拷贝给另一个节点
Status avl_tree_node_copy(avl_tree_node_t *src, avl_tree_node_t *dst, int key_data_size, int value_data_size)
{
    dst->right = src->right;
    dst->left = src->left;

    memcpy(dst->key, src->key, key_data_size);
    memcpy(dst->value, src->value, value_data_size);

    return OK;
}

// 销毁节点
Status avl_tree_node_destroy(avl_tree_node_t **avl_tree_n){
    free((*avl_tree_n)->key);
    free((*avl_tree_n)->value);
    (*avl_tree_n)->key = NULL;
    (*avl_tree_n)->value = NULL;

    (*avl_tree_n)->left = NULL;
    (*avl_tree_n)->right = NULL;
    free(*avl_tree_n);
    *avl_tree_n = NULL;

    return OK;
}

// 创建AVL
avl_tree_t *avl_tree(int key_data_size, int value_data_size)
{
    avl_tree_t *avl_tree_tree = (avl_tree_t *)malloc(sizeof(avl_tree_t));

    if(!avl_tree_tree){
        // 存储分配失败
        exit(OVERFLOW);
    }

    avl_tree_tree->root = NULL;
    avl_tree_tree->key_data_size = key_data_size;
    avl_tree_tree->value_data_size = value_data_size;
    avl_tree_tree->size = 0;

    return avl_tree_tree;
}

// AVL的大小
int avl_tree_size(avl_tree_t *avl_tree_tree)
{
    if(avl_tree_tree == NULL){
        return OVERFLOW;
    }
    return avl_tree_tree->size;
}

// 判断AVL是否为空
bool avl_tree_is_empty(avl_tree_t *avl_tree_tree)
{
    if(avl_tree_tree == NULL){
        return OVERFLOW;
    }
    return avl_tree_tree->size == 0;
}

// 返回两个值中的最大值
int max(int x, int y)
{
    if(x > y)
        return x;
    else
        return y;
}

//
void avl_tree_in_order(avl_tree_node_t *avl_tree_n, dynamic_array_t *arr)
{
    if(avl_tree_n == NULL)
        return;

    avl_tree_in_order(avl_tree_n->left, arr);
    array_insert_last(arr, avl_tree_n->key);
    avl_tree_in_order(avl_tree_n->right, arr);

}

// 判断该二叉树是否是一颗二分搜索树
bool avl_tree_is_bst(avl_tree_t *avl_tree, compare_s compare_t)
{
    dynamic_array_t *arr = array(avl_tree->key_data_size);
    avl_tree_in_order(avl_tree->root, arr);

    for(int i  = 1; i < array_size(arr); i ++){
        if((*compare_t)(array_get(arr, i - 1, NULL),array_get(arr, i, NULL)) > 0)
            return false;
    }

    return true;
}

//
bool avl_tree_is_balance(avl_tree_node_t *avl_tree_node)
{
    // 空树左右子树都是空，高度为0，高度差为0，满足平衡二叉树的定义
    if(avl_tree_node == NULL)
        return true;

    // 计算平衡因子
    int balance_factor = avl_tree_node_get_balance_factor(avl_tree_node);
    // 该节点不满足平衡二叉树的性质
    if(abs(balance_factor) > 1)
        return false;

    // 该节点是满足平衡二叉树的性质的，递归的看其左右子树是否满足平衡二叉树的性质
    return avl_tree_is_balance(avl_tree_node->left) && avl_tree_is_balance(avl_tree_node->right);
}


// 判断该二叉树是否是一颗平衡二叉树
bool avl_tree_is_balance_r(avl_tree_t *avl_tree)
{
    return avl_tree_is_balance(avl_tree->root);
}

// 右旋转
avl_tree_node_t *avl_tree_right_rotate(avl_tree_node_t *y)
{
    avl_tree_node_t *x = y->left;
    avl_tree_node_t *T3 = x->right;

    // 向右旋转
    x->right = y;
    y->left = T3;

    // 更新x和y节点的height
    y->height = max(avl_tree_node_get_height(y->left), avl_tree_node_get_height(y->right)) + 1;
    x->height = max(avl_tree_node_get_height(x->left), avl_tree_node_get_height(x->right)) + 1;

    return x;
}

// 左旋转
avl_tree_node_t *avl_tree_left_rotate(avl_tree_node_t *y)
{
    avl_tree_node_t *x = y->right;
    avl_tree_node_t *T3 = x->left;

    // 向左旋转
    x->left = y;
    y->right = T3;

    // 更新x和y节点的height
    y->height = max(avl_tree_node_get_height(y->left), avl_tree_node_get_height(y->right)) + 1;
    x->height = max(avl_tree_node_get_height(x->left), avl_tree_node_get_height(x->right)) + 1;

    return x;
}


// 向以node为根的二分搜索树中插入元素e，递归算法
// 返回插入新节点后二分搜索树的根
avl_tree_node_t *avl_tree_add(avl_tree_t *avl_tree, avl_tree_node_t *n, void *key, void *value, compare_s compare_t)
{
    if(n == NULL){
        avl_tree_node_t *new = avl_tree_node(key, avl_tree->key_data_size, value, avl_tree->value_data_size);
        avl_tree->size ++;
        return new;
    }

    if((*compare_t)(key, n->key) < 0)
        n->left = avl_tree_add(avl_tree, n->left, key, value, compare_t);
    else if((*compare_t)(key, n->key) > 0)
        n->right = avl_tree_add(avl_tree, n->right, key, value, compare_t);
    else // if((*compare_t)(key, n->key) == 0)
        memcpy(n->value, value, avl_tree->value_data_size);

    int n_left_height =  avl_tree_node_get_height(n->left);
    int n_right_height = avl_tree_node_get_height(n->right);

    // 更新height
    n->height = 1 + max(n_left_height, n_right_height);

    // 计算平衡因子
    int balance_factor = avl_tree_node_get_balance_factor(n);

//    if(abs(balance_factor) > 1)
//        printf("balance_factor: %d\n", balance_factor);

    // 平衡维护(前提: 计算节点平衡因子的方法是将左子树的高度减去右子树的高度)
    // 该节点的平衡因子大于1，代表该节点的左子树高于右子树，且高度差不止1
    // 该节点的左子树的平衡因子大于等于0，代表该节点的左子树等于或高于右子树
    // 代表造成该节点不平衡的原因是该节点的左侧的左侧多添加了一个节点
    // LL 右旋转
    if(balance_factor > 1 && avl_tree_node_get_balance_factor(n->left) >= 0){
        return avl_tree_right_rotate(n);
    }

    // RR 左旋转
    if(balance_factor < -1 && avl_tree_node_get_balance_factor(n->right) <= 0){
        return avl_tree_left_rotate(n);
    }

    // LR
    if(balance_factor > 1 && avl_tree_node_get_balance_factor(n->left) < 0){
        n->left = avl_tree_left_rotate(n->left);
        return avl_tree_right_rotate(n);
    }

    // RL
    if(balance_factor < -1 && avl_tree_node_get_balance_factor(n->right) > 0){
        n->right = avl_tree_right_rotate(n->right);
        return avl_tree_left_rotate(n);
    }

    return n;
}

// 向二分搜索树中添加元素
Status avl_tree_add_r(avl_tree_t *avl_tree_tree, void *key, void *value, compare_s compare_t)
{
    if(avl_tree_tree == NULL)
        return OVERFLOW;

    avl_tree_tree->root = avl_tree_add(avl_tree_tree, avl_tree_tree->root, key, value, compare_t);

    return OK;
}

// 获取key所在的节点， 递归算法
avl_tree_node_t *avl_tree_get_node(avl_tree_t *avl_tree_tree, avl_tree_node_t *n, void *key, avl_tree_node_t *ret_node, compare_s compare_t)
{
    if(n == NULL){
        return NULL;
    }

    if((*compare_t)(key, n->key) == 0){
        // 将源链表中的节点复制一份新的，避免节点被销毁之后，指针指向不对，用于获取源链表中数据
        if(ret_node != NULL){
            memcpy(ret_node, n, sizeof(avl_tree_node_t));
            return ret_node;
        }
        // 获取源链表中的节点，节点销毁，数据即不存在，用于修改源链表中数据
        return n;
    }
    else if((*compare_t)(key, n->key) < 0)
        return avl_tree_get_node(avl_tree_tree, n->left, key, ret_node, compare_t);
    else // (*compare_t)(e, n->data) > 0
        return avl_tree_get_node(avl_tree_tree, n->right, key, ret_node, compare_t);
}

// 是否包含key
bool avl_tree_contain_r(avl_tree_t *avl_tree_tree, void *key, compare_s compare_t)
{
    if(avl_tree_tree == NULL)
        return OVERFLOW;

    return avl_tree_get_node(avl_tree_tree, avl_tree_tree->root, key, NULL, compare_t) != NULL;
}

// 获取key对应的value
void *avl_tree_get_r(avl_tree_t *avl_tree_tree, void *key, void *ret_value, compare_s compare_t)
{
    avl_tree_node_t *avl_tree_n = avl_tree_node(key, avl_tree_tree->key_data_size, NULL, avl_tree_tree->value_data_size);
    // 单独赋值给一个指针的原因是，如果返回了NULL，直接赋值给上面创建的节点的指针，会导致上面创建的节点无法销毁
    avl_tree_node_t *ret = avl_tree_get_node(avl_tree_tree, avl_tree_tree->root, key, avl_tree_n, compare_t);

    if(ret != NULL){
        memcpy(ret_value, ret->value, avl_tree_tree->value_data_size);
        avl_tree_node_destroy(&avl_tree_n);
        return ret_value;
    }

    avl_tree_node_destroy(&avl_tree_n);

    return ret;
}

// 修改key的value
Status avl_tree_set(avl_tree_t *avl_tree_tree, void *key, void *value, compare_s compare_t)
{
    avl_tree_node_t *avl_tree_n = avl_tree_get_node(avl_tree_tree, avl_tree_tree->root, key, NULL, compare_t);

    if(avl_tree_n == NULL){
        exit(OVERFLOW);
    }

    memcpy(avl_tree_n->value, value, avl_tree_tree->value_data_size);

    return OK;
}

// 返回以node为根的二分搜索树的最小值所在的节点， 递归算法
avl_tree_node_t *avl_tree_minimum(avl_tree_node_t *n, avl_tree_node_t *minimum_n, int key_data_size, int value_data_size)
{
    if(n->left == NULL){
        // n是指向节点的指针，所以不能直接返回该指针，需要用一块内存来接收它所指向的那块内存
        // 但是直接将n的整个内存拷贝走，会把n->data数据区域的指针也拷贝走，导致改变了接收方的数据域的data指针
        // 所以应该使用一对一赋值的方式将n的left/right/tree_size这些非自己申请内存的变量赋值给接收方，然后对于数据区域data这种自主管理内存的数据，使用memcpy进行内存赋值
        // n->data是指向数据的指针，所以不能直接返回该指针，需要用一块内存来接收它所指向的那块内存
        avl_tree_node_copy(n, minimum_n, key_data_size, value_data_size);

        return minimum_n;
    }

    return avl_tree_minimum(n->left, minimum_n, key_data_size, value_data_size);

}

// 删除以node为根的二分搜索树的最小节点
// 返回删除最小节点之后新的二分搜索树的根
avl_tree_node_t *avl_tree_remove_minimum(avl_tree_t *avl_tree_tree, avl_tree_node_t *n)
{
    if(n->left == NULL){
        avl_tree_node_t *right_node = n->right;
        n->right = NULL;
        avl_tree_node_destroy(&n);
        avl_tree_tree->size --;
        return right_node;
    }

    n->left = avl_tree_remove_minimum(avl_tree_tree, n->left);

    return n;
}

// 删除以node为根的二分搜索树中的元素key，递归算法
// 返回删除节点后新的二分搜索树的根
avl_tree_node_t *avl_tree_remove(avl_tree_t *avl_tree_tree, avl_tree_node_t *n, void *key, compare_s compare_t)
{
    if(n == NULL)
        return NULL;

    avl_tree_node_t *ret_node;
    if ((*compare_t)(key, n->key) < 0) {
        n->left = avl_tree_remove(avl_tree_tree, n->left, key, compare_t);
        ret_node = n;
    } else if((*compare_t)(key, n->key) > 0){
        n->right = avl_tree_remove(avl_tree_tree, n->right, key, compare_t);
        ret_node = n;
    } else{ // e = n->data
        // 待删除节点左子树为空的情况
        if(n->left == NULL){
            avl_tree_node_t *right_node = n->right;
            n->right = NULL;
            avl_tree_node_destroy(&n);
            avl_tree_tree->size --;
            ret_node = right_node;
        }

        // 待删除节点右子树为空的情况
        else if(n->right == NULL){
            avl_tree_node_t *left_node = n->left;
            n->left = NULL;
            avl_tree_node_destroy(&n);
            avl_tree_tree->size --;
            ret_node = left_node;
        }

        else {
            // 待删除节点左右子树都不为空的情况
            // 找到比待删除节点大的最小节点，即待删除节点右子树的最小节点
            // 用这个节点代替待删除节点的位置
            avl_tree_node_t *successor =  avl_tree_node(NULL, avl_tree_tree->key_data_size, NULL, avl_tree_tree->value_data_size);
            avl_tree_minimum(n->right, successor, avl_tree_tree->key_data_size, avl_tree_tree->value_data_size);
            // 由于在remove_minimum的删除过程中并没有进行平衡维护，所以需要对该操作也进行平衡维护
            // 解决方法1: 在remove_minimum操作中加入一样的平衡维护代码
            // 解决方法2: remove_minimum做的操作就是在node->right中删除key最小的节点，可以直接用remove来替代这个操作，remove操作要删除的节点的key就是successor节点的key，remove操作中已经加入了维护平衡的代码
            successor->right = avl_tree_remove(avl_tree_tree, n->right, successor->key, compare_t);
            successor->left = n->left;

            avl_tree_node_destroy(&n);

            ret_node = successor;
        }

    }

    // 在删除节点之后很有可能获得的ret_node是空，比如删除的节点是叶子节点就会产生这种情况
    if(ret_node == NULL)
        return NULL;

    int n_left_height =  avl_tree_node_get_height(ret_node->left);
    int n_right_height = avl_tree_node_get_height(ret_node->right);

    // 更新height
    ret_node->height = 1 + max(n_left_height, n_right_height);

    // 计算平衡因子
    int balance_factor = avl_tree_node_get_balance_factor(ret_node);

    // 平衡维护
    // LL 右旋转
    if(balance_factor > 1 && avl_tree_node_get_balance_factor(ret_node->left) >= 0){
        return avl_tree_right_rotate(ret_node);
    }

    // RR 左旋转
    if(balance_factor < -1 && avl_tree_node_get_balance_factor(ret_node->right) <= 0){
        return avl_tree_left_rotate(ret_node);
    }

    // LR
    if(balance_factor > 1 && avl_tree_node_get_balance_factor(ret_node->left) < 0){
        ret_node->left = avl_tree_left_rotate(ret_node->left);
        return avl_tree_right_rotate(ret_node);
    }

    // RL
    if(balance_factor < -1 && avl_tree_node_get_balance_factor(ret_node->right) > 0){
        ret_node->right = avl_tree_right_rotate(ret_node->right);
        return avl_tree_left_rotate(ret_node);
    }

    return ret_node;
}

// 删除二分搜索数中key的元素
void *avl_tree_remove_r(avl_tree_t *avl_tree_tree, void *key, void *ret_value, compare_s compare_t)
{
    if(avl_tree_is_empty(avl_tree_tree))
        exit(OVERFLOW);

    avl_tree_node_t *avl_tree_n = avl_tree_node(key, avl_tree_tree->key_data_size, NULL, avl_tree_tree->value_data_size);
    // 单独赋值给一个指针的原因是，如果返回了NULL，直接赋值给上面创建的节点的指针，会导致上面创建的节点无法销毁
    avl_tree_node_t *ret = avl_tree_get_node(avl_tree_tree, avl_tree_tree->root, key, avl_tree_n, compare_t);

    if(ret != NULL){
        if(ret_value != NULL)
            memcpy(ret_value, ret->value, avl_tree_tree->value_data_size);
        avl_tree_tree->root = avl_tree_remove(avl_tree_tree, avl_tree_tree->root, key, compare_t);
        return ret_value;
    }

    avl_tree_node_destroy(&avl_tree_n);

    return ret;
}

// 清空以node为根的二分搜索树
void avl_tree_clear(avl_tree_node_t **n)
{
    if(*n == NULL){
        return;
    }

    avl_tree_clear(&((*n)->left));
    avl_tree_clear(&((*n)->right));

    avl_tree_node_destroy(n);

}

// 清空二分搜索树
Status avl_tree_clear_r(avl_tree_t *avl_tree_tree)
{
    avl_tree_clear(&(avl_tree_tree->root));
    avl_tree_tree->size = 0;

    return OK;
}


// 销毁二分搜索树
Status avl_tree_destroy(avl_tree_t **avl_tree_tree)
{
    avl_tree_clear_r(*avl_tree_tree);
    *avl_tree_tree = NULL;

    return OK;
}

