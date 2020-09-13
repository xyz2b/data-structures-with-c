//
// Created by 焦宏宇 on 2020/2/12.
//

#include "basic_bst.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// 创建节点
basic_bst_node_t *basic_bst_node(int data_size, void *e)
{
    basic_bst_node_t *n = (basic_bst_node_t *)malloc(sizeof(basic_bst_node_t));
    void *elem = (char *)malloc(data_size);

    if(!n || !elem){
        // 存储分配失败
        free(n);
        free(elem);
        return NULL;
    }

    if(e != NULL)
        memcpy(elem, e, data_size);

    n->data = elem;
    n->left = NULL;
    n->right = NULL;

    return n;
}

// 将一个节点拷贝给另一个节点
Status basic_bst_node_copy(basic_bst_node_t *src, basic_bst_node_t *dst, int data_size)
{
    dst->right = src->right;
    dst->left = src->left;

    memcpy(dst->data, src->data, data_size);

    return OK;
}

// 销毁节点
Status basic_bst_node_destroy(basic_bst_node_t **bst_n){
    free((*bst_n)->data);
    (*bst_n)->data = NULL;

    (*bst_n)->left = NULL;
    (*bst_n)->right = NULL;
    free(*bst_n);
    *bst_n = NULL;

    return OK;
}

// 创建二分搜索树
basic_bst_t *basic_bst(int data_size)
{
    basic_bst_t *bst_tree = (basic_bst_t *)malloc(sizeof(basic_bst_t));

    if(!bst_tree){
        // 存储分配失败
        return NULL;
    }

    bst_tree->root = NULL;
    bst_tree->data_size = data_size;
    bst_tree->size = 0;

    return bst_tree;
}

// 树的大小
int basic_bst_size(basic_bst_t *bst_tree)
{
    if(bst_tree == NULL){
        return OVERFLOW;
    }
    return bst_tree->size;
}

// 判断二分搜索树是否为空
bool basic_bst_is_empty(basic_bst_t *bst_tree)
{
    if(bst_tree == NULL){
        return OVERFLOW;
    }
    return bst_tree->size == 0;
}

// 向以node为根的二分搜索树中插入元素e，递归算法
// 返回插入新节点后二分搜索树的根
basic_bst_node_t *basic_bst_add(basic_bst_t *bst_tree, basic_bst_node_t *n, void *e, compare_s compare_t)
{
    if(n == NULL){
        basic_bst_node_t *new = basic_bst_node(bst_tree->data_size, e);
        bst_tree->size ++;
        return new;
    }

    if((*compare_t)(e, n->data) < 0)
        n->left = basic_bst_add(bst_tree, n->left, e, compare_t);
    else if((*compare_t)(e, n->data) > 0)
        n->right = basic_bst_add(bst_tree, n->right, e, compare_t);

    return n;
}

// 向二分搜索树中添加元素
Status basic_bst_add_r(basic_bst_t *bst_tree, void *e, compare_s compare_t)
{
    if(bst_tree == NULL)
        return OVERFLOW;

    bst_tree->root = basic_bst_add(bst_tree, bst_tree->root, e, compare_t);

    return OK;
}

// 看以node为根的二分搜索树中是否包含e， 递归算法
bool basic_bst_contain(basic_bst_t *bst_tree, basic_bst_node_t *n, void *e, compare_s compare_t)
{
    if(n == NULL){
        return false;
    }

    if((*compare_t)(e, n->data) == 0)
        return true;
    else if((*compare_t)(e, n->data) < 0)
        return basic_bst_contain(bst_tree, n->left, e, compare_t);
    else // (*compare_t)(e, n->data) > 0
        return basic_bst_contain(bst_tree, n->right, e, compare_t);
}

// 看二分搜索树中是否包含元素e
bool basic_bst_contain_r(basic_bst_t *bst_tree, void *e, compare_s compare_t)
{
    if(bst_tree == NULL)
        return OVERFLOW;

    return basic_bst_contain(bst_tree, bst_tree->root, e, compare_t);
}


// 生产深度表示字符串
void basic_bst_generate_depth_string(int depth)
{
    for(int i = 0; i < depth; i++)
        printf("%s", "--");
}

// 以node为根进行前序遍历， 递归算法
void basic_bst_pre_order(basic_bst_node_t *n, int depth, to_string_s to_string_t)
{
    if(n == NULL){
        basic_bst_generate_depth_string(depth);
        printf("%s", "null\n");
        return;

    }

    basic_bst_generate_depth_string(depth);
    char buffer[200];
    (*to_string_t)(n->data, buffer);
    printf("%s\n", buffer);

    basic_bst_pre_order(n->left, depth + 1, to_string_t);

    basic_bst_pre_order(n->right, depth + 1, to_string_t);
}

// 二分搜索树的前序遍历
void basic_bst_pre_order_r(basic_bst_t *bst_tree, to_string_s to_string_t)
{
    basic_bst_pre_order(bst_tree->root, 0, to_string_t);
}

// 二分搜索树的前序遍历，非递归实现
void basic_bst_pre_order_nr(basic_bst_t *bst_tree, to_string_s to_string_t)
{
    linked_list_stack_t *stack = linked_list_stack(sizeof(basic_bst_node_t));

    linked_list_stack_push(stack, bst_tree->root);
    while (!linked_list_stack_is_empty(stack)){
        basic_bst_node_t *cur = basic_bst_node(bst_tree->data_size, NULL);
        linked_list_stack_pop(stack, cur);
        char buffer[200];
        (*to_string_t)(cur->data, buffer);
        printf("%s\n", buffer);

        if(cur->right != NULL){
            linked_list_stack_push(stack, cur->right);
        }

        if(cur->left != NULL){
            linked_list_stack_push(stack, cur->left);
        }
    }
}


// 以node为根进行中序遍历， 递归算法
void basic_bst_in_order(basic_bst_node_t *n, int depth, to_string_s to_string_t)
{
    if(n == NULL){
        basic_bst_generate_depth_string(depth);
        printf("%s", "null\n");
        return;
    }

    basic_bst_in_order(n->left, depth + 1, to_string_t);

    basic_bst_generate_depth_string(depth);
    char buffer[200];
    (*to_string_t)(n->data, buffer);
    printf("%s\n", buffer);

    basic_bst_in_order(n->right, depth + 1, to_string_t);
}

// 二分搜索树的中序遍历
void basic_bst_in_order_r(basic_bst_t *bst_tree, to_string_s to_string_t)
{
    basic_bst_in_order(bst_tree->root, 0, to_string_t);
}

// 以node为根进行后序遍历， 递归算法
void basic_bst_post_order(basic_bst_node_t *n, int depth, to_string_s to_string_t)
{
    if(n == NULL){
        basic_bst_generate_depth_string(depth);
        printf("%s", "null\n");
        return;

    }

    basic_bst_post_order(n->left, depth + 1, to_string_t);

    basic_bst_post_order(n->right, depth + 1, to_string_t);

    basic_bst_generate_depth_string(depth);
    char buffer[200];
    (*to_string_t)(n->data, buffer);
    printf("%s\n", buffer);
}

// 二分搜索树的后序遍历
void basic_bst_post_order_r(basic_bst_t *bst_tree, to_string_s to_string_t)
{
    basic_bst_post_order(bst_tree->root, 0, to_string_t);
}


// 二分搜索树的层序遍历，非递归实现
void basic_bst_level_order_nr(basic_bst_t *bst_tree, to_string_s to_string_t)
{
    linked_list_queue_t *q = linked_list_queue(sizeof(basic_bst_node_t));

    linked_list_queue_enqueue(q, bst_tree->root);
    while (!linked_list_queue_is_empty(q)){
        basic_bst_node_t *cur = basic_bst_node(bst_tree->data_size, NULL);
        linked_list_queue_dequeue(q, cur);
        char buffer[200];
        (*to_string_t)(cur->data, buffer);
        printf("%s\n", buffer);

        if(cur->left != NULL){
            linked_list_queue_enqueue(q, cur->left);
        }

        if(cur->right != NULL){
            linked_list_queue_enqueue(q, cur->right);
        }
    }
}

// 返回以node为根的二分搜索树的最小值所在的节点， 递归算法
Status basic_bst_minimum(basic_bst_node_t *n, basic_bst_node_t *minimum_n, int data_size)
{
    if(n->left == NULL){
        // n是指向节点的指针，所以不能直接返回该指针，需要用一块内存来接收它所指向的那块内存
        // 但是直接将n的整个内存拷贝走，会把n->data数据区域的指针也拷贝走，导致改变了接收方的数据域的data指针
        // 所以应该使用一对一赋值的方式将n的left/right/tree_size这些非自己申请内存的变量赋值给接收方，然后对于数据区域data这种自主管理内存的数据，使用memcpy进行内存赋值
        // n->data是指向数据的指针，所以不能直接返回该指针，需要用一块内存来接收它所指向的那块内存
        basic_bst_node_copy(n, minimum_n, data_size);

        return OK;
    }

    return basic_bst_minimum(n->left, minimum_n, data_size);

}

// 寻找二分搜索树的最小元素
Status basic_bst_minimum_r(basic_bst_t *bst_tree, void *ret)
{
    if(basic_bst_is_empty(bst_tree))
        exit(OVERFLOW);

    basic_bst_node_t *minimum_n = basic_bst_node(bst_tree->data_size, NULL);
    basic_bst_minimum(bst_tree->root, minimum_n, bst_tree->data_size);
    void *elem = minimum_n->data;
    memcpy(ret, elem, bst_tree->data_size);

    basic_bst_node_destroy(&minimum_n);

    return OK;
}

// 找寻以node为根的树中的最大元素， 递归算法
Status basic_bst_maximum(basic_bst_node_t *n, basic_bst_node_t *maximum_n, int data_size)
{
    if(n->right == NULL){
        basic_bst_node_copy(n, maximum_n, data_size);
        return OK;
    }

    return basic_bst_maximum(n->right, maximum_n, data_size);

}

// 寻找二分搜索树的最大元素
Status basic_bst_maximum_r(basic_bst_t *bst_tree, void *ret)
{
    if(basic_bst_is_empty(bst_tree))
        exit(OVERFLOW);

    basic_bst_node_t *maximum_n = basic_bst_node(bst_tree->data_size, NULL);
    basic_bst_maximum(bst_tree->root, maximum_n, bst_tree->data_size);
    void *elem = maximum_n->data;
    memcpy(ret, elem, bst_tree->data_size);
    basic_bst_node_destroy(&maximum_n);

    return OK;
}


// 删除以node为根的二分搜索树的最小节点
// 返回删除最小节点之后新的二分搜索树的根
basic_bst_node_t *basic_bst_remove_minimum(basic_bst_t *bst_tree, basic_bst_node_t *n)
{
    if(n->left == NULL){
        basic_bst_node_t *right_node = n->right;
        n->right = NULL;
        basic_bst_node_destroy(&n);
        bst_tree->size --;
        return right_node;
    }

    n->left = basic_bst_remove_minimum(bst_tree, n->left);

    return n;
}

// 删除二分搜索树中最小的元素
Status basic_bst_remove_minimum_r(basic_bst_t *bst_tree, void *ret)
{
    if(basic_bst_is_empty(bst_tree))
        exit(OVERFLOW);

    basic_bst_minimum_r(bst_tree, ret);

    bst_tree->root = basic_bst_remove_minimum(bst_tree, bst_tree->root);

    return OK;
}

// 删除以node为根的二分搜索树的最大节点
// 返回删除最大节点之后新的二分搜索树的根
basic_bst_node_t *basic_bst_remove_maximum(basic_bst_t *bst_tree, basic_bst_node_t *n)
{
    if(n->right == NULL){
        basic_bst_node_t *left_node = n->left;
        n->left = NULL;
        basic_bst_node_destroy(&n);
        bst_tree->size --;
        return left_node;
    }

    n->right = basic_bst_remove_maximum(bst_tree, n->right);
    return n;
}

// 删除二分搜索树中最大的元素
Status basic_bst_remove_maximum_r(basic_bst_t *bst_tree, void *ret)
{
    if(basic_bst_is_empty(bst_tree))
        exit(OVERFLOW);

    basic_bst_maximum_r(bst_tree, ret);

    bst_tree->root = basic_bst_remove_maximum(bst_tree, bst_tree->root);

    return OK;
}

// 删除以node为根的二分搜索树中的元素e，递归算法
// 返回删除节点后新的二分搜索树的根
basic_bst_node_t *basic_bst_remove(basic_bst_t *bst_tree, basic_bst_node_t *n, void *e, compare_s compare_t)
{
    if(n == NULL)
        return NULL;

    if ((*compare_t)(e, n->data) < 0) {
        n->left = basic_bst_remove(bst_tree, n->left, e, compare_t);
        return n;
    } else if((*compare_t)(e, n->data) > 0){
        n->right = basic_bst_remove(bst_tree, n->right, e, compare_t);
        return n;
    } else{ // e = n->data
        // 待删除节点左子树为空的情况
        if(n->left == NULL){
            basic_bst_node_t *right_node = n->right;
            n->right = NULL;
            basic_bst_node_destroy(&n);
            bst_tree->size --;
            return right_node;
        }

        // 待删除节点右子树为空的情况
        if(n->right == NULL){
            basic_bst_node_t *left_node = n->left;
            n->left = NULL;
            basic_bst_node_destroy(&n);
            bst_tree->size --;
            return left_node;
        }

        // 待删除节点左右子树都不为空的情况
        // 找到比待删除节点大的最小节点，即待删除节点右子树的最小节点
        // 用这个节点代替待删除节点的位置
        basic_bst_node_t *successor = basic_bst_node(bst_tree->data_size, NULL);
        basic_bst_minimum(n->right, successor, bst_tree->data_size);
        successor->right = basic_bst_remove_minimum(bst_tree, n->right);
        successor->left = n->left;

        basic_bst_node_destroy(&n);

        return successor;
    }
}

// 删除二分搜索数中为e的元素
Status basic_bst_remove_r(basic_bst_t *bst_tree, void *e, compare_s compare_t)
{
    if(basic_bst_is_empty(bst_tree))
        exit(OVERFLOW);

    bst_tree->root = basic_bst_remove(bst_tree, bst_tree->root, e, compare_t);

    return OK;
}

// 在二分搜索树中找寻最接近元素e且小于等于元素e的节点，递归算法
/*
 * 如果元素e和node相等：则node本身就是元素e的floor节点
 * 如果元素e比node小：则要寻找的floor节点一定在node的左子树中
 * 如果元素e比node大：则node有可能是元素e的floor节点, 也有可能不是(因为node的右子树中可能存在比node大但是小于元素e的其余节点)，需要尝试向node的右子树寻找一下
*/
// 返回找到的节点
basic_bst_node_t *basic_bst_floor(basic_bst_node_t *n, basic_bst_node_t *floor_n, int data_size, void *e, compare_s compare_t)
{
    if(n == NULL)
        return NULL;

    if((*compare_t)(e, n->data) == 0){
        basic_bst_node_copy(n, floor_n, data_size);
        return floor_n;
    }

    else if((*compare_t)(e, n->data) < 0)
        return basic_bst_floor(n->left, floor_n, data_size, e, compare_t);
    else{ //如果e比node大，可能是，也能是不是
        basic_bst_node_t *right_node =  basic_bst_floor(n->right, floor_n, data_size, e, compare_t);
        if(right_node != NULL){
            basic_bst_node_copy(right_node, floor_n, data_size);
            return floor_n;
        }

        basic_bst_node_copy(n, floor_n, data_size);
        return floor_n;
    }
}

// 在二分搜索树中找寻最接近元素e且小于等于元素e的节点
Status basic_bst_floor_r(basic_bst_t *bst_tree, void *e, void *ret, compare_s compare_t)
{
    basic_bst_node_t *floor_n = basic_bst_node(bst_tree->data_size, NULL);
    floor_n = basic_bst_floor(bst_tree->root, floor_n, bst_tree->data_size, e, compare_t);

    void *elem = floor_n->data;
    memcpy(ret, elem, bst_tree->data_size);

    return OK;
}

// 在二分搜索树中找寻最接近元素e且大于等于元素e的节点，递归算法
/*
 * 如果元素e和node相等：则node本身就是元素e的ceil节点
 * 如果元素e比node大：则要寻找的ceil节点一定在node的右子树中
 * 如果元素e比node小：则node有可能是元素e的floor节点, 也有可能不是(因为node的左子树中可能存在比node小但是大于元素e的其余节点)，需要尝试向node的左子树寻找一下
*/
// 返回找到的节点
basic_bst_node_t *basic_bst_ceil(basic_bst_node_t *n, basic_bst_node_t *ceil_n, int data_size, void *e, compare_s compare_t)
{
    if(n == NULL)
        return NULL;

    if((*compare_t)(e, n->data) == 0){
        basic_bst_node_copy(n, ceil_n, data_size);
        return ceil_n;
    }
    else if((*compare_t)(e, n->data) > 0)
        return basic_bst_ceil(n->right, ceil_n, data_size, e, compare_t);
    else{
        basic_bst_node_t *left_node =  basic_bst_ceil(n->left, ceil_n, data_size, e, compare_t);
        if(left_node != NULL){
            basic_bst_node_copy(n, ceil_n, data_size);
            return ceil_n;
        }

        basic_bst_node_copy(n, ceil_n, data_size);
        return ceil_n;
    }
}

// 在二分搜索树中找寻最接近元素e且大于等于元素e的节点
Status basic_bst_ceil_r(basic_bst_t *bst_tree, void *e, void *ret, compare_s compare_t)
{
    basic_bst_node_t *ceil_n = basic_bst_node(bst_tree->data_size, NULL);
    ceil_n = basic_bst_ceil(bst_tree->root, ceil_n, bst_tree->data_size, e, compare_t);

    void *elem = ceil_n->data;
    memcpy(ret, elem, bst_tree->data_size);

    return OK;
}

// 清空以node为根的二分搜索树
void basic_bst_clear(basic_bst_node_t **n)
{
    if(*n == NULL){
        return;
    }

    basic_bst_clear(&((*n)->left));
    basic_bst_clear(&((*n)->right));

    basic_bst_node_destroy(n);

}

// 清空二分搜索树
Status basic_bst_clear_r(basic_bst_t *bst_tree)
{
    basic_bst_clear(&(bst_tree->root));
    bst_tree->size = 0;

    return OK;
}


// 销毁二分搜索树
Status basic_bst_destroy(basic_bst_t **bst_tree)
{
    basic_bst_clear_r(*bst_tree);
    *bst_tree = NULL;

    return OK;
}


