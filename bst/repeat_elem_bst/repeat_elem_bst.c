//
// Created by 焦宏宇 on 2020/2/12.
//

#include "repeat_elem_bst.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// 创建节点
repeat_elem_bst_node_t *repeat_elem_bst_node(int data_size, void *e)
{
    repeat_elem_bst_node_t *n = (repeat_elem_bst_node_t *)malloc(sizeof(repeat_elem_bst_node_t));
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
    n->tree_size = 1;
    n->depth = 0;
    n->count = 1;
    n->left = NULL;
    n->right = NULL;

    return n;
}

// 将一个节点拷贝给另一个节点
Status repeat_elem_bst_node_copy(repeat_elem_bst_node_t *src, repeat_elem_bst_node_t *dst, int data_size)
{
    dst->tree_size = src->tree_size;
    dst->right = src->right;
    dst->left = src->left;
    dst->depth = src->depth;
    dst->count = src->count;

    memcpy(dst->data, src->data, data_size);

    return OK;
}

// 销毁节点
Status repeat_elem_bst_node_destroy(repeat_elem_bst_node_t **bst_n){
    free((*bst_n)->data);
    (*bst_n)->data = NULL;

    (*bst_n)->left = NULL;
    (*bst_n)->right = NULL;
    free(*bst_n);
    *bst_n = NULL;

    return OK;
}

// 创建二分搜索树
repeat_elem_bst_t *repeat_elem_bst(int data_size)
{
    repeat_elem_bst_t *bst_tree = (repeat_elem_bst_t *)malloc(sizeof(repeat_elem_bst_t));

    if(!bst_tree){
        // 存储分配失败
        return NULL;
    }

    bst_tree->root = NULL;
    bst_tree->data_size = data_size;

    return bst_tree;
}

// 查看二分搜索树的大小
int repeat_elem_bst_size(repeat_elem_bst_t *bst_tree)
{
    if(bst_tree == NULL){
        return OVERFLOW;
    }
    if(bst_tree->root == NULL)
        return 0;
    return bst_tree->root->tree_size;
}

// 判断二分搜索树是否为空
bool repeat_elem_bst_is_empty(repeat_elem_bst_t *bst_tree)
{
    if(bst_tree == NULL){
        return OVERFLOW;
    }

    return bst_tree->root == NULL;
}

// 向以node为根的二分搜索树中插入元素e，递归算法
// 返回插入新节点后二分搜索树的根
repeat_elem_bst_node_t *repeat_elem_bst_add(repeat_elem_bst_t *bst_tree, repeat_elem_bst_node_t *n, void *e, int depth, compare_s compare_t)
{
    if(n == NULL){
        repeat_elem_bst_node_t *new = repeat_elem_bst_node(bst_tree->data_size, e);
        new->depth = depth;
        return new;
    }

    if((*compare_t)(e, n->data) < 0){
        n->left = repeat_elem_bst_add(bst_tree, n->left, e, depth + 1, compare_t);
    } else if((*compare_t)(e, n->data) > 0){
        n->right = repeat_elem_bst_add(bst_tree, n->right, e, depth + 1, compare_t);
    } else{
        n->count ++;
    }

    n->tree_size ++;
    return n;
}

// 向二分搜索树中添加元素
Status repeat_elem_bst_add_r(repeat_elem_bst_t *bst_tree, void *e, compare_s compare_t)
{
    if(bst_tree == NULL)
        return OVERFLOW;

    bst_tree->root = repeat_elem_bst_add(bst_tree, bst_tree->root, e, 0, compare_t);

    return OK;
}

// 看以node为根的二分搜索树中是否包含e， 递归算法
bool repeat_elem_bst_contain(repeat_elem_bst_t *bst_tree, repeat_elem_bst_node_t *n, void *e, compare_s compare_t)
{
    if(n == NULL){
        return false;
    }

    if((*compare_t)(e, n->data) == 0)
        return true;
    else if((*compare_t)(e, n->data) < 0)
        return repeat_elem_bst_contain(bst_tree, n->left, e, compare_t);
    else // (*compare_t)(e, n->data) < 0
        return repeat_elem_bst_contain(bst_tree, n->right, e, compare_t);


}

// 看二分搜索树中是否包含元素e
bool repeat_elem_bst_contain_r(repeat_elem_bst_t *bst_tree, void *e, compare_s compare_t)
{
    if(bst_tree == NULL)
        return OVERFLOW;

    return repeat_elem_bst_contain(bst_tree, bst_tree->root, e, compare_t);
}


// 计算以node为根的树中，某个元素的重复次数
// 返回重复的次数
int repeat_elem_bst_elem_count(repeat_elem_bst_node_t *n, void *e, compare_s compare_t)
{
    if(n == NULL){
        return -1;
    }

    if((*compare_t)(e, n->data) == 0)
        return n->count;
    else if((*compare_t)(e, n->data) < 0)
        return repeat_elem_bst_elem_count(n->left, e, compare_t);
    else // (*compare_t)(e, n->data) < 0
        return repeat_elem_bst_elem_count(n->right, e, compare_t);


}

// 计算某个元素在树中的重复次数
int repeat_elem_bst_elem_count_r(repeat_elem_bst_t *bst_tree, void *e, compare_s compare_t)
{
    return repeat_elem_bst_elem_count(bst_tree->root, e, compare_t);
}



// 生产深度表示字符串
void repeat_elem_bst_generate_depth_string(int depth)
{
    for(int i = 0; i < depth; i++)
        printf("%s", "--");
}

// 以node为根进行前序遍历， 递归算法
void repeat_elem_bst_pre_order(repeat_elem_bst_node_t *n, int depth, to_string_s to_string_t)
{
    if(n == NULL){
        repeat_elem_bst_generate_depth_string(depth);
        printf("%s", "null\n");
        return;

    }

    repeat_elem_bst_generate_depth_string(depth);
    char buffer[200];
    (*to_string_t)(n->data, buffer);
    printf("%s\n", buffer);

    repeat_elem_bst_pre_order(n->left, depth + 1, to_string_t);

    repeat_elem_bst_pre_order(n->right, depth + 1, to_string_t);
}

// 二分搜索树的前序遍历
void repeat_elem_bst_pre_order_r(repeat_elem_bst_t *bst_tree, to_string_s to_string_t)
{
    repeat_elem_bst_pre_order(bst_tree->root, 0, to_string_t);
}

// 二分搜索树的前序遍历，非递归实现
void repeat_elem_bst_pre_order_nr(repeat_elem_bst_t *bst_tree, to_string_s to_string_t)
{
    linked_list_stack_t *stack = linked_list_stack(sizeof(repeat_elem_bst_node_t));

    linked_list_stack_push(stack, bst_tree->root);
    while (!linked_list_stack_is_empty(stack)){
        repeat_elem_bst_node_t *cur = repeat_elem_bst_node(bst_tree->data_size, NULL);
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
void repeat_elem_bst_in_order(repeat_elem_bst_node_t *n, int depth, to_string_s to_string_t)
{
    if(n == NULL){
        repeat_elem_bst_generate_depth_string(depth);
        printf("%s", "null\n");
        return;
    }

    repeat_elem_bst_in_order(n->left, depth + 1, to_string_t);

    repeat_elem_bst_generate_depth_string(depth);
    char buffer[200];
    (*to_string_t)(n->data, buffer);
    printf("%s\n", buffer);

    repeat_elem_bst_in_order(n->right, depth + 1, to_string_t);
}

// 二分搜索树的中序遍历
void repeat_elem_bst_in_order_r(repeat_elem_bst_t *bst_tree, to_string_s to_string_t)
{
    repeat_elem_bst_in_order(bst_tree->root, 0, to_string_t);
}

// 以node为根进行后序遍历， 递归算法
void repeat_elem_bst_post_order(repeat_elem_bst_node_t *n, int depth, to_string_s to_string_t)
{
    if(n == NULL){
        repeat_elem_bst_generate_depth_string(depth);
        printf("%s", "null\n");
        return;

    }

    repeat_elem_bst_post_order(n->left, depth + 1, to_string_t);

    repeat_elem_bst_post_order(n->right, depth + 1, to_string_t);

    repeat_elem_bst_generate_depth_string(depth);
    char buffer[200];
    (*to_string_t)(n->data, buffer);
    printf("%s\n", buffer);
}

// 二分搜索树的后序遍历
void repeat_elem_bst_post_order_r(repeat_elem_bst_t *bst_tree, to_string_s to_string_t)
{
    repeat_elem_bst_post_order(bst_tree->root, 0, to_string_t);
}


// 二分搜索树的层序遍历，非递归实现
void repeat_elem_bst_level_order_nr(repeat_elem_bst_t *bst_tree, to_string_s to_string_t)
{
    linked_list_queue_t *q = linked_list_queue(sizeof(repeat_elem_bst_node_t));

    linked_list_queue_enqueue(q, bst_tree->root);
    while (!linked_list_queue_is_empty(q)){
        repeat_elem_bst_node_t *cur = repeat_elem_bst_node(bst_tree->data_size, NULL);
        linked_list_queue_dequeue(q, cur);
        char buffer[200];
        (*to_string_t)(cur->data, buffer);
        printf("%s, size: %d, depth: %d, count: %d\n", buffer, cur->tree_size, cur->depth, cur->count);

        if(cur->left != NULL){
            linked_list_queue_enqueue(q, cur->left);
        }

        if(cur->right != NULL){
            linked_list_queue_enqueue(q, cur->right);
        }
    }
}

// 返回以node为根的二分搜索树的最小值所在的节点， 递归算法
Status repeat_elem_bst_minimum(repeat_elem_bst_node_t *n, repeat_elem_bst_node_t *minimum_n, int data_size)
{
    if(n->left == NULL){
        // n是指向节点的指针，所以不能直接返回该指针，需要用一块内存来接收它所指向的那块内存
        // 但是直接将n的整个内存拷贝走，会把n->data数据区域的指针也拷贝走，导致改变了接收方的数据域的data指针
        // 所以应该使用一对一赋值的方式将n的left/right/tree_size这些非自己申请内存的变量赋值给接收方，然后对于数据区域data这种自主管理内存的数据，使用memcpy进行内存赋值
        // n->data是指向数据的指针，所以不能直接返回该指针，需要用一块内存来接收它所指向的那块内存
        repeat_elem_bst_node_copy(n, minimum_n, data_size);

        return OK;
    }

    return repeat_elem_bst_minimum(n->left, minimum_n, data_size);

}

// 寻找二分搜索树的最小元素
Status repeat_elem_bst_minimum_r(repeat_elem_bst_t *bst_tree, void *ret)
{
    if(repeat_elem_bst_is_empty(bst_tree))
        exit(OVERFLOW);

    repeat_elem_bst_node_t *minimum_n = repeat_elem_bst_node(bst_tree->data_size, NULL);
    repeat_elem_bst_minimum(bst_tree->root, minimum_n, bst_tree->data_size);
    void *elem = minimum_n->data;
    memcpy(ret, elem, bst_tree->data_size);

    repeat_elem_bst_node_destroy(&minimum_n);

    return OK;
}

// 找寻以node为根的树中的最大元素， 递归算法
Status repeat_elem_bst_maximum(repeat_elem_bst_node_t *n, repeat_elem_bst_node_t *maximum_n, int data_size)
{
    if(n->right == NULL){
        repeat_elem_bst_node_copy(n, maximum_n, data_size);
        return OK;
    }

    return repeat_elem_bst_maximum(n->right, maximum_n, data_size);

}

// 寻找二分搜索树的最大元素
Status repeat_elem_bst_maximum_r(repeat_elem_bst_t *bst_tree, void *ret)
{
    if(repeat_elem_bst_is_empty(bst_tree))
        exit(OVERFLOW);

    repeat_elem_bst_node_t *maximum_n = repeat_elem_bst_node(bst_tree->data_size, NULL);
    repeat_elem_bst_maximum(bst_tree->root, maximum_n, bst_tree->data_size);
    void *elem = maximum_n->data;
    memcpy(ret, elem, bst_tree->data_size);
    repeat_elem_bst_node_destroy(&maximum_n);

    return OK;
}

// 将以node为根节点的树上的每个节点depth减一
// 返回每个节点depth都减一后的根，还是node
repeat_elem_bst_node_t *repeat_elem_bst_depth_reduce_one(repeat_elem_bst_node_t *n)
{
    if(n == NULL)
        return NULL;

    n->depth --;
    repeat_elem_bst_depth_reduce_one(n->left);
    repeat_elem_bst_depth_reduce_one(n->right);

    return n;
}

// 删除以node为根的二分搜索树的最小节点
// 返回删除最小节点之后新的二分搜索树的根
repeat_elem_bst_node_t *repeat_elem_bst_remove_minimum(repeat_elem_bst_t *bst_tree, repeat_elem_bst_node_t *n)
{
    if(n->left == NULL){
        if(--n->count > 0){
            n->tree_size --;
            return n;
        }
        repeat_elem_bst_node_t *right_node = n->right;
        n->right = NULL;
        repeat_elem_bst_node_destroy(&n);
        return repeat_elem_bst_depth_reduce_one(right_node);
    }

    n->left = repeat_elem_bst_remove_minimum(bst_tree, n->left);

    n->tree_size --;

    return n;
}

// 删除二分搜索树中最小的元素
Status repeat_elem_bst_remove_minimum_r(repeat_elem_bst_t *bst_tree, void *ret)
{
    if(repeat_elem_bst_is_empty(bst_tree))
        exit(OVERFLOW);

    repeat_elem_bst_minimum_r(bst_tree, ret);

    bst_tree->root = repeat_elem_bst_remove_minimum(bst_tree, bst_tree->root);

    return OK;
}

// 删除以node为根的二分搜索树的最大节点
// 返回删除最大节点之后新的二分搜索树的根
repeat_elem_bst_node_t *repeat_elem_bst_remove_maximum(repeat_elem_bst_t *bst_tree, repeat_elem_bst_node_t *n)
{
    if(n->right == NULL){
        if(--n->count > 0){
            n->tree_size --;
            return n;
        }
        repeat_elem_bst_node_t *left_node = n->left;
        n->left = NULL;
        repeat_elem_bst_node_destroy(&n);
        return repeat_elem_bst_depth_reduce_one(left_node);
    }

    n->right = repeat_elem_bst_remove_maximum(bst_tree, n->right);

    n->tree_size --;
    return n;
}

// 删除二分搜索树中最大的元素
Status repeat_elem_bst_remove_maximum_r(repeat_elem_bst_t *bst_tree, void *ret)
{
    if(repeat_elem_bst_is_empty(bst_tree))
        exit(OVERFLOW);

    repeat_elem_bst_maximum_r(bst_tree, ret);

    bst_tree->root = repeat_elem_bst_remove_maximum(bst_tree, bst_tree->root);

    return OK;
}

// 删除以node为根的二分搜索树中的元素e，递归算法
// 返回删除节点后新的二分搜索树的根
repeat_elem_bst_node_t *repeat_elem_bst_remove(repeat_elem_bst_t *bst_tree, repeat_elem_bst_node_t *n, void *e, compare_s compare_t)
{
    if(n == NULL)
        return NULL;

    if ((*compare_t)(e, n->data) < 0) {
        n->left = repeat_elem_bst_remove(bst_tree, n->left, e, compare_t);
        n->tree_size --;
        return n;
    } else if((*compare_t)(e, n->data) > 0){
        n->right = repeat_elem_bst_remove(bst_tree, n->right, e, compare_t);
        n->tree_size --;
        return n;
    } else{ // e = n->data

        if(--n->count > 0){
            n->tree_size --;
            return n;
        }

        // 待删除节点左子树为空的情况
        if(n->left == NULL){
            repeat_elem_bst_node_t *right_node = n->right;
            n->right = NULL;
            repeat_elem_bst_node_destroy(&n);

            return repeat_elem_bst_depth_reduce_one(right_node);
        }

        // 待删除节点右子树为空的情况
        if(n->right == NULL){
            repeat_elem_bst_node_t *left_node = n->left;
            n->left = NULL;
            repeat_elem_bst_node_destroy(&n);

            return repeat_elem_bst_depth_reduce_one(left_node);
        }

        // 待删除节点左右子树都不为空的情况
        // 找到比待删除节点大的最小节点，即待删除节点右子树的最小节点
        // 用这个节点代替待删除节点的位置
        repeat_elem_bst_node_t *successor = repeat_elem_bst_node(bst_tree->data_size, NULL);
        repeat_elem_bst_minimum(n->right, successor, bst_tree->data_size);

        int minimum_elem_count = repeat_elem_bst_elem_count_r(bst_tree, successor->data, compare_t);

        for(int i = 0; i < minimum_elem_count; i++){
            successor->right = repeat_elem_bst_remove_minimum(bst_tree, n->right);
        }
        successor->left = n->left;
        successor->tree_size = n->tree_size - 1;
        successor->depth = n->depth;

        repeat_elem_bst_node_destroy(&n);

        return successor;
    }
}

// 删除二分搜索数中为e的元素
Status repeat_elem_bst_remove_r(repeat_elem_bst_t *bst_tree, void *e, compare_s compare_t)
{
    if(repeat_elem_bst_is_empty(bst_tree))
        exit(OVERFLOW);

    bst_tree->root = repeat_elem_bst_remove(bst_tree, bst_tree->root, e, compare_t);

    return OK;
}

// 在二分搜索树中找寻最接近元素e且小于等于元素e的节点，递归算法
/*
 * 如果元素e和node相等：则node本身就是元素e的floor节点
 * 如果元素e比node小：则要寻找的floor节点一定在node的左子树中
 * 如果元素e比node大：则node有可能是元素e的floor节点, 也有可能不是(因为node的右子树中可能存在比node大但是小于元素e的其余节点)，需要尝试向node的右子树寻找一下
*/
// 返回找到的节点
repeat_elem_bst_node_t *repeat_elem_bst_floor(repeat_elem_bst_node_t *n, repeat_elem_bst_node_t *floor_n, int data_size, void *e, compare_s compare_t)
{
    if(n == NULL)
        return NULL;

    if((*compare_t)(e, n->data) == 0){
        repeat_elem_bst_node_copy(n, floor_n, data_size);
        return floor_n;
    }

    else if((*compare_t)(e, n->data) < 0)
        return repeat_elem_bst_floor(n->left, floor_n, data_size, e, compare_t);
    else{ //如果e比node大，可能是，也能是不是
        repeat_elem_bst_node_t *right_node =  repeat_elem_bst_floor(n->right, floor_n, data_size, e, compare_t);
        if(right_node != NULL){
            repeat_elem_bst_node_copy(right_node, floor_n, data_size);
            return floor_n;
        }

        repeat_elem_bst_node_copy(n, floor_n, data_size);
        return floor_n;
    }
}

// 在二分搜索树中找寻最接近元素e且小于等于元素e的节点
Status repeat_elem_bst_floor_r(repeat_elem_bst_t *bst_tree, void *e, void *ret, compare_s compare_t)
{
    repeat_elem_bst_node_t *floor_n = repeat_elem_bst_node(bst_tree->data_size, NULL);
    floor_n = repeat_elem_bst_floor(bst_tree->root, floor_n, bst_tree->data_size, e, compare_t);

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
repeat_elem_bst_node_t *repeat_elem_bst_ceil(repeat_elem_bst_node_t *n, repeat_elem_bst_node_t *ceil_n, int data_size, void *e, compare_s compare_t)
{
    if(n == NULL)
        return NULL;

    if((*compare_t)(e, n->data) == 0){
        repeat_elem_bst_node_copy(n, ceil_n, data_size);
        return ceil_n;
    }
    else if((*compare_t)(e, n->data) > 0)
        return repeat_elem_bst_ceil(n->right, ceil_n, data_size, e, compare_t);
    else{
        repeat_elem_bst_node_t *left_node =  repeat_elem_bst_ceil(n->left, ceil_n, data_size, e, compare_t);
        if(left_node != NULL){
            repeat_elem_bst_node_copy(n, ceil_n, data_size);
            return ceil_n;
        }

        repeat_elem_bst_node_copy(n, ceil_n, data_size);
        return ceil_n;
    }
}

// 在二分搜索树中找寻最接近元素e且大于等于元素e的节点
Status repeat_elem_bst_ceil_r(repeat_elem_bst_t *bst_tree, void *e, void *ret, compare_s compare_t)
{
    repeat_elem_bst_node_t *ceil_n = repeat_elem_bst_node(bst_tree->data_size, NULL);
    ceil_n = repeat_elem_bst_ceil(bst_tree->root, ceil_n, bst_tree->data_size, e, compare_t);

    void *elem = ceil_n->data;
    memcpy(ret, elem, bst_tree->data_size);

    return OK;
}




// 返回以node为根的树中，e元素的排名
int repeat_elem_bst_rank(repeat_elem_bst_node_t *n, void *e, compare_s compare_t)
{
    if(n == NULL)
        return -1;

    if((*compare_t)(e, n->data) == 0){
        if(n->right == NULL)
            return n->tree_size;
        return n->tree_size - n->right->tree_size;
    } else if((*compare_t)(e, n->data) < 0){
        return repeat_elem_bst_rank(n->left, e, compare_t);
    } else {
        return n->tree_size - n->right->tree_size + repeat_elem_bst_rank(n->right, e, compare_t);
    }
}

// 返回元素e在二分搜索树中的排名
int repeat_elem_bst_rank_r(repeat_elem_bst_t *bst_tree, void *e, compare_s compare_t)
{
    return repeat_elem_bst_rank(bst_tree->root, e, compare_t);
}

// 查询排名第index位置的节点
/*
 * 排名index小于左子数的节点数tree_size，就在左边找
 * 左子数的节点数等于index的话，那index位置的节点就是根节点
 * 如果index大于左子数的节点数，那就需要在右子树中去查找。此时要在以该节点的右子树为根的树中查找，原本的索引对应到以该节点右子树为根的树中的索引，就是源索引 - 该节点左子树的size - 该节点本身的size(因为有重复，节点本身的size等于节点本身的重复次数)
 *
 */
// 返回以node为根的树中排名第index位置的节点
repeat_elem_bst_node_t *repeat_elem_bst_select(repeat_elem_bst_node_t *n, repeat_elem_bst_node_t *index_n, int index, int data_size, compare_s compare_t)
{
    if(n == NULL)
        return NULL;

    // 如果node->left为空，类似于链表，进行如下操作

    // 如果索引为0，需要的就是链表头元素
    // 如果索引大于0，即要在以node->right为根的树中继续索引，此时索引值需要减去该节点的size(即该节点的重复次数)
    if(n->left == NULL){
        if(index >= 0 && index <= n->count - 1){
            repeat_elem_bst_node_copy(n, index_n, data_size);
            return index_n;
        }

        return repeat_elem_bst_select(n->right, index_n, index - n->count, data_size, compare_t);
    }

    // 如果node->left不为空，进行如下操作

    // 因为每个节点都可能重复，如果index在某个节点的重复次数内，那么索引到的就是该节点
    // 在没有重复的情况下，index等于该节点左子树的size，即索引到的就是该节点
    // 在有重复的情况下，索引到的是本节点的范围要变大，即index大于等于左子树的size，小于等于左子树size + 该节点size(该节点重复次数) - 1
    if(index >= n->left->tree_size && index <= n->left->tree_size + n->count - 1){
        repeat_elem_bst_node_copy(n, index_n, data_size);
        return index_n;
    } else if(index < n->left->tree_size){
        return repeat_elem_bst_select(n->left, index_n, index, data_size, compare_t);
    } else {
        return repeat_elem_bst_select(n->right, index_n, index - n->left->tree_size - n->count, data_size, compare_t);
    }
}

// 查询排名第index位置的节点
Status repeat_elem_bst_select_r(repeat_elem_bst_t *bst_tree, int index, void *ret, compare_s compare_t)
{


    repeat_elem_bst_node_t *index_n = repeat_elem_bst_node(bst_tree->data_size, NULL);
    index_n = repeat_elem_bst_select(bst_tree->root, index_n, index, bst_tree->data_size, compare_t);

    void *elem = index_n->data;
    memcpy(ret, elem, bst_tree->data_size);

    return OK;
}


// 清空以node为根的二分搜索树
void repeat_elem_bst_clear(repeat_elem_bst_node_t **n)
{
    if(*n == NULL){
        return;
    }

    repeat_elem_bst_clear(&((*n)->left));
    repeat_elem_bst_clear(&((*n)->right));

    repeat_elem_bst_node_destroy(n);

}

// 清空二分搜索树
Status repeat_elem_bst_clear_r(repeat_elem_bst_t *bst_tree)
{
    repeat_elem_bst_clear(&(bst_tree->root));

    return OK;
}


// 销毁二分搜索树
Status repeat_elem_bst_destroy(repeat_elem_bst_t **bst_tree)
{
    repeat_elem_bst_clear_r(*bst_tree);
    *bst_tree = NULL;

    return OK;
}


