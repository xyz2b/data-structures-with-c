//
// Created by 焦宏宇 on 2020/2/23.
//

#include "rb_tree.h"
#include <stdlib.h>
#include <string.h>

// 创建节点
rb_tree_node_t *rb_tree_node(void *key, int key_data_size, void *value, int value_data_size)
{
    rb_tree_node_t *n = (rb_tree_node_t *)malloc(sizeof(rb_tree_node_t));
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
    n->color = red;

    return n;
}

// 判断一个节点是黑色还是红色
bool rb_tree_node_is_red(rb_tree_node_t *rb_tree_n)
{
    // 空节点为黑节点，红色节点表示的是和它的父亲节点合在一起是原来2-3树中对应的3节点，对于空节点来说肯定谈不上什么融合，所以把它定义为黑节点
    if(rb_tree_n == NULL)
        return black;
    return rb_tree_n->color;
}

// 将一个节点拷贝给另一个节点
Status rb_tree_node_copy(rb_tree_node_t *src, rb_tree_node_t *dst, int key_data_size, int value_data_size)
{
    dst->right = src->right;
    dst->left = src->left;

    memcpy(dst->key, src->key, key_data_size);
    memcpy(dst->value, src->value, value_data_size);

    return OK;
}

// 销毁节点
Status rb_tree_node_destroy(rb_tree_node_t **rb_n){
    free((*rb_n)->key);
    free((*rb_n)->value);
    (*rb_n)->key = NULL;
    (*rb_n)->value = NULL;

    (*rb_n)->left = NULL;
    (*rb_n)->right = NULL;
    free(*rb_n);
    *rb_n = NULL;

    return OK;
}

// 创建红黑树
rb_tree_t *rb_tree(int key_data_size, int value_data_size)
{
    rb_tree_t *rb_tree_tree = (rb_tree_t *)malloc(sizeof(rb_tree_t));

    if(!rb_tree_tree){
        // 存储分配失败
        exit(OVERFLOW);
    }

    rb_tree_tree->root = NULL;
    rb_tree_tree->key_data_size = key_data_size;
    rb_tree_tree->value_data_size = value_data_size;
    rb_tree_tree->size = 0;

    return rb_tree_tree;
}

// 红黑树的大小
int rb_tree_size(rb_tree_t *rb_tree_tree)
{
    if(rb_tree_tree == NULL){
        return OVERFLOW;
    }
    return rb_tree_tree->size;
}

// 判断红黑树是否为空
bool rb_tree_is_empty(rb_tree_t *rb_tree_tree)
{
    if(rb_tree_tree == NULL){
        return OVERFLOW;
    }
    return rb_tree_tree->size == 0;
}

// 颜色翻转
void rb_tree_flip_colors(rb_tree_node_t *node)
{
    node->color = red;
    node->left = black;
    node->right = black;
}

// 对于node进行左旋转
rb_tree_node_t *rb_tree_left_rotate(rb_tree_node_t *node)
{
    rb_tree_node_t *x = node->right;

    // 左旋转
    node->right = x->left;
    x->left = node;

    // 维护节点颜色
    x->color = node->color;
    node->color = red;

    return x;
}

// 对于node进行右旋转
rb_tree_node_t *rb_tree_right_rotate(rb_tree_node_t *node)
{
    rb_tree_node_t *x = node->left;

    // 右旋转
    node->left = x->right;
    x->right = node;

    // 维护节点颜色
    x->color = node->color;
    node->color = red;

    return x;
}

// 向以node为根的红黑树中插入元素e，递归算法
// 返回插入新节点后红黑树的根
rb_tree_node_t *rb_tree_add(rb_tree_t *rb_tree_tree, rb_tree_node_t *n, void *key, void *value, compare_s compare_t)
{
    if(n == NULL){
        // 默认插入红色节点
        rb_tree_node_t *new = rb_tree_node(key, rb_tree_tree->key_data_size, value, rb_tree_tree->value_data_size);
        rb_tree_tree->size ++;
        return new;
    }

    // 在递归之前是进行当前节点的处理，一般用于父亲到孩子方向的递归处理

    if((*compare_t)(key, n->key) < 0)
        n->left = rb_tree_add(rb_tree_tree, n->left, key, value, compare_t);
    else if((*compare_t)(key, n->key) > 0)
        n->right = rb_tree_add(rb_tree_tree, n->right, key, value, compare_t);
    else // if((*compare_t)(key, n->key) == 0)
        memcpy(n->value, value, rb_tree_tree->value_data_size);

    // 在递归之后是在处理完当前节点的孩子节点并返回之后，再对当前节点进行处理，一般用于从孩子到父亲方向的递归处理


    if(rb_tree_node_is_red(n->right) && !rb_tree_node_is_red(n->left))
        n = rb_tree_left_rotate(n);

    if(rb_tree_node_is_red(n->left) && rb_tree_node_is_red(n->left->left))
        n = rb_tree_right_rotate(n);

    if(rb_tree_node_is_red(n->left) && rb_tree_node_is_red(n->right))
        rb_tree_flip_colors(n);



    return n;
}

// 向红黑树树中添加元素
Status rb_tree_add_r(rb_tree_t *rb_tree_tree, void *key, void *value, compare_s compare_t)
{
    if(rb_tree_tree == NULL)
        return OVERFLOW;

    rb_tree_tree->root = rb_tree_add(rb_tree_tree, rb_tree_tree->root, key, value, compare_t);

    // 最终红黑树的根节点为黑色
    rb_tree_tree->root->color = black;

    return OK;
}

// 获取key所在的节点， 递归算法
rb_tree_node_t *rb_tree_get_node(rb_tree_t *rb_tree_tree, rb_tree_node_t *n, void *key, rb_tree_node_t *ret_node, compare_s compare_t)
{
    if(n == NULL){
        return NULL;
    }

    if((*compare_t)(key, n->key) == 0){
        // 将源链表中的节点复制一份新的，避免节点被销毁之后，指针指向不对，用于获取源链表中数据
        if(ret_node != NULL){
            memcpy(ret_node, n, sizeof(rb_tree_node_t));
            return ret_node;
        }
        // 获取源链表中的节点，节点销毁，数据即不存在，用于修改源链表中数据
        return n;
    }
    else if((*compare_t)(key, n->key) < 0)
        return rb_tree_get_node(rb_tree_tree, n->left, key, ret_node, compare_t);
    else // (*compare_t)(e, n->data) > 0
        return rb_tree_get_node(rb_tree_tree, n->right, key, ret_node, compare_t);
}

// 是否包含key
bool rb_tree_contain_r(rb_tree_t *rb_tree_tree, void *key, compare_s compare_t)
{
    if(rb_tree_tree == NULL)
        return OVERFLOW;

    return rb_tree_get_node(rb_tree_tree, rb_tree_tree->root, key, NULL, compare_t) != NULL;
}

// 获取key对应的value
void *rb_tree_get_r(rb_tree_t *rb_tree_tree, void *key, void *ret_value, compare_s compare_t)
{
    rb_tree_node_t *rb_tree_n = rb_tree_node(key, rb_tree_tree->key_data_size, NULL, rb_tree_tree->value_data_size);
    // 单独赋值给一个指针的原因是，如果返回了NULL，直接赋值给上面创建的节点的指针，会导致上面创建的节点无法销毁
    rb_tree_node_t *ret = rb_tree_get_node(rb_tree_tree, rb_tree_tree->root, key, rb_tree_n, compare_t);

    if(ret != NULL){
        memcpy(ret_value, ret->value, rb_tree_tree->value_data_size);
        rb_tree_node_destroy(&rb_tree_n);
        return ret_value;
    }

    rb_tree_node_destroy(&rb_tree_n);

    return ret;
}

// 修改key的value
Status rb_tree_set(rb_tree_t *rb_tree_tree, void *key, void *value, compare_s compare_t)
{
    rb_tree_node_t *rb_tree_n = rb_tree_get_node(rb_tree_tree, rb_tree_tree->root, key, NULL, compare_t);

    if(rb_tree_n == NULL){
        exit(OVERFLOW);
    }

    memcpy(rb_tree_n->value, value, rb_tree_tree->value_data_size);

    return OK;
}

// 返回以node为根的二分搜索树的最小值所在的节点， 递归算法
rb_tree_node_t *rb_tree_minimum(rb_tree_node_t *n, rb_tree_node_t *minimum_n, int key_data_size, int value_data_size)
{
    if(n->left == NULL){
        // n是指向节点的指针，所以不能直接返回该指针，需要用一块内存来接收它所指向的那块内存
        // 但是直接将n的整个内存拷贝走，会把n->data数据区域的指针也拷贝走，导致改变了接收方的数据域的data指针
        // 所以应该使用一对一赋值的方式将n的left/right/tree_size这些非自己申请内存的变量赋值给接收方，然后对于数据区域data这种自主管理内存的数据，使用memcpy进行内存赋值
        // n->data是指向数据的指针，所以不能直接返回该指针，需要用一块内存来接收它所指向的那块内存
        rb_tree_node_copy(n, minimum_n, key_data_size, value_data_size);

        return minimum_n;
    }

    return rb_tree_minimum(n->left, minimum_n, key_data_size, value_data_size);

}

// 删除以node为根的二分搜索树的最小节点
// 返回删除最小节点之后新的二分搜索树的根
rb_tree_node_t *rb_tree_remove_minimum(rb_tree_t *rb_tree_tree, rb_tree_node_t *n)
{
    if(n->left == NULL){
        rb_tree_node_t *right_node = n->right;
        n->right = NULL;
        rb_tree_node_destroy(&n);
        rb_tree_tree->size --;
        return right_node;
    }

    n->left = rb_tree_remove_minimum(rb_tree_tree, n->left);

    return n;
}

// 删除以node为根的二分搜索树中的元素key，递归算法
// 返回删除节点后新的二分搜索树的根
rb_tree_node_t *rb_tree_remove(rb_tree_t *rb_tree_tree, rb_tree_node_t *n, void *key, compare_s compare_t)
{
    if(n == NULL)
        return NULL;

    if ((*compare_t)(key, n->key) < 0) {
        n->left = rb_tree_remove(rb_tree_tree, n->left, key, compare_t);
        return n;
    } else if((*compare_t)(key, n->key) > 0){
        n->right = rb_tree_remove(rb_tree_tree, n->right, key, compare_t);
        return n;
    } else{ // e = n->data
        // 待删除节点左子树为空的情况
        if(n->left == NULL){
            rb_tree_node_t *right_node = n->right;
            n->right = NULL;
            rb_tree_node_destroy(&n);
            rb_tree_tree->size --;
            return right_node;
        }

        // 待删除节点右子树为空的情况
        if(n->right == NULL){
            rb_tree_node_t *left_node = n->left;
            n->left = NULL;
            rb_tree_node_destroy(&n);
            rb_tree_tree->size --;
            return left_node;
        }

        // 待删除节点左右子树都不为空的情况
        // 找到比待删除节点大的最小节点，即待删除节点右子树的最小节点
        // 用这个节点代替待删除节点的位置
        rb_tree_node_t *successor =  rb_tree_node(NULL, rb_tree_tree->key_data_size, NULL, rb_tree_tree->value_data_size);
        rb_tree_minimum(n->right, successor, rb_tree_tree->key_data_size, rb_tree_tree->value_data_size);
        successor->right = rb_tree_remove_minimum(rb_tree_tree, n->right);
        successor->left = n->left;

        rb_tree_node_destroy(&n);

        return successor;
    }
}

// 删除二分搜索数中key的元素
void *rb_tree_remove_r(rb_tree_t *rb_tree_tree, void *key, void *ret_value, compare_s compare_t)
{
    if(rb_tree_is_empty(rb_tree_tree))
        exit(OVERFLOW);

    rb_tree_node_t *rb_tree_n = rb_tree_node(key, rb_tree_tree->key_data_size, NULL, rb_tree_tree->value_data_size);
    // 单独赋值给一个指针的原因是，如果返回了NULL，直接赋值给上面创建的节点的指针，会导致上面创建的节点无法销毁
    rb_tree_node_t *ret = rb_tree_get_node(rb_tree_tree, rb_tree_tree->root, key, rb_tree_n, compare_t);

    if(ret != NULL){
        memcpy(ret_value, ret->value, rb_tree_tree->value_data_size);
        rb_tree_tree->root = rb_tree_remove(rb_tree_tree, rb_tree_tree->root, key, compare_t);
        return ret_value;
    }

    rb_tree_node_destroy(&rb_tree_n);

    return NULL;
}


// 返回以node为根的二分搜索树中的key的集合
bst_set_t *rb_tree_key_set(rb_tree_node_t *n, bst_set_t *set, compare_s compare_t)
{
    if(n == NULL){
        return NULL;
    }

    bst_set_add(set, n->key, compare_t);
    rb_tree_key_set(n->left, set, compare_t);
    rb_tree_key_set(n->right, set, compare_t);

    return set;
}

// 返回key的集合
bst_set_t *rb_tree_key_set_r(rb_tree_t *rb_tree_tree, bst_set_t *set, compare_s compare_t)
{
    return rb_tree_key_set(rb_tree_tree->root, set, compare_t);
}

// 清空以node为根的二分搜索树
void rb_tree_clear(rb_tree_node_t **n)
{
    if(*n == NULL){
        return;
    }

    rb_tree_clear(&((*n)->left));
    rb_tree_clear(&((*n)->right));

    rb_tree_node_destroy(n);

}

// 清空二分搜索树
Status rb_tree_clear_r(rb_tree_t *rb_tree_tree)
{
    rb_tree_clear(&(rb_tree_tree->root));
    rb_tree_tree->size = 0;

    return OK;
}


// 销毁二分搜索树
Status rb_tree_destroy(rb_tree_t **rb_tree_tree)
{
    rb_tree_clear_r(*rb_tree_tree);
    *rb_tree_tree = NULL;

    return OK;
}
