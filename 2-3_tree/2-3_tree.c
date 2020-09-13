//
// Created by 焦宏宇 on 2020/2/23.
//

#include "2-3_tree.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// 创建2节点
two_three_tree_node_t *two_three_tree_node_2(int data_size, void *e, two_three_tree_node_t *left, two_three_tree_node_t *right)
{
    two_three_tree_node_t *n = (two_three_tree_node_t *)malloc(sizeof(two_three_tree_node_t));
    void *right_d = (char *)malloc(data_size);
    void *left_d = (char *)malloc(data_size);

    if(!n || !right_d|| !left_d){
        // 存储分配失败
        free(n);
        free(right_d);
        free(left_d);
        return NULL;
    }

    // 2节点的left_data等于right_data
    if(e != NULL)
        memcpy(right_d, e, data_size);
    if(e != NULL)
        memcpy(left_d, e, data_size);

    n->left_data = left_d;
    n->right_data = right_d;
    n->left = left;
    n->middle = NULL;
    n->right = right;
    n->three = false;

    return n;
}

// 创建3节点
two_three_tree_node_t *two_three_tree_node_3(int data_size, void *right_data, void *left_data, two_three_tree_node_t *left, two_three_tree_node_t *middle, two_three_tree_node_t *right)
{
    two_three_tree_node_t *n = (two_three_tree_node_t *)malloc(sizeof(two_three_tree_node_t));
    void *right_d = (char *)malloc(data_size);
    void *left_d = (char *)malloc(data_size);

    if(!n || !right_d|| !left_d){
        // 存储分配失败
        free(n);
        free(right_d);
        free(left_d);
        return NULL;
    }

    if(right_data != NULL)
        memcpy(right_d, right_data, data_size);
    if(left_data != NULL)
        memcpy(left_d, left_data, data_size);

    n->left_data = left_d;
    n->right_data = right_d;
    n->left = left;
    n->middle = middle;
    n->right = right;
    n->three = true;

    return n;
}


// 将一个节点拷贝给另一个节点
Status two_three_tree_node_copy(two_three_tree_node_t *src, two_three_tree_node_t *dst, int data_size)
{
    dst->right = src->right;
    dst->middle = src->middle;
    dst->left = src->left;
    dst->three = src->three;

    memcpy(dst->left_data, src->left_data, data_size);
    memcpy(dst->right_data, src->right_data, data_size);

    return OK;
}

// 判断一个节点是否为3节点
bool two_three_tree_node_is_three(two_three_tree_node_t *two_three_tree_n)
{
    return two_three_tree_n->three;
}

// 销毁节点
Status two_three_tree_node_destroy(two_three_tree_node_t **two_three_tree_n){
    free((*two_three_tree_n)->right_data);
    free((*two_three_tree_n)->left_data);
    (*two_three_tree_n)->right_data = NULL;
    (*two_three_tree_n)->left_data = NULL;

    (*two_three_tree_n)->left = NULL;
    (*two_three_tree_n)->middle = NULL;
    (*two_three_tree_n)->right = NULL;
    free(*two_three_tree_n);
    *two_three_tree_n = NULL;

    return OK;
}

// 创建二分搜索树
two_three_tree_t *two_three_tree(int data_size)
{
    two_three_tree_t *two_three_t = (two_three_tree_t *)malloc(sizeof(two_three_tree_t));

    if(!two_three_t){
        // 存储分配失败
        return NULL;
    }

    two_three_t->root = NULL;
    two_three_t->data_size = data_size;
    two_three_t->size = 0;

    return two_three_t;
}

// 树的大小
int two_three_tree_size(two_three_tree_t *two_three_t)
{
    if(two_three_t == NULL){
        return OVERFLOW;
    }
    return two_three_t->size;
}

// 判断二分搜索树是否为空
bool two_three_tree_is_empty(two_three_tree_t *two_three_t)
{
    if(two_three_t == NULL){
        return OVERFLOW;
    }
    return two_three_t->size == 0;
}

// 向以node为根的二分搜索树中插入元素e，递归算法
// 返回插入新节点后二分搜索树的根
two_three_tree_node_t *two_three_tree_add(two_three_tree_t *two_three_t, two_three_tree_node_t *n, void *e, compare_s compare_t)
{
    // 空树
    if(n == NULL){
        return two_three_tree_node_2(two_three_t->data_size, e, NULL, NULL);
    }

    // 叶子节点，非叶子结点left/right都不为NULL
    if(n->left == NULL){
        // 如果插入的叶子节点是2节点，返回插入后的树新的根
        if(!two_three_tree_node_is_three(n)){
            // 融合
            if((*compare_t)(e, n->left_data) < 0){
                memcpy(n->left_data, e, two_three_t->data_size);
            }
            if((*compare_t)(e, n->right_data) > 0){
                memcpy(n->right_data, e, two_three_t->data_size);
            }
            return n;
        } else{// 如果插入的叶子节点是3节点，返回插入后的树新的根
            // 融合-->分裂为3个2节点的子树
            if((*compare_t)(e, n->left_data) < 0){
                // 分裂后树根的左右子树
                two_three_tree_node_t *left = two_three_tree_node_2(two_three_t->data_size, e, NULL, NULL);
                two_three_tree_node_t *right = two_three_tree_node_2(two_three_t->data_size, n->right_data, NULL, NULL);

                // 分裂后的树根
                memcpy(n->right_data, n->left_data, two_three_t->data_size);
                n->left = left;
                n->right = right;

                return n;
            }else if((*compare_t)(e, n->left_data) > 0 && (*compare_t)(e, n->right_data) < 0){
                // 分裂后树根的左右子树
                two_three_tree_node_t *left = two_three_tree_node_2(two_three_t->data_size, n->left_data, NULL, NULL);
                two_three_tree_node_t *right = two_three_tree_node_2(two_three_t->data_size, n->right_data, NULL, NULL);

                // 分裂后的树根
                memcpy(n->right_data, e, two_three_t->data_size);
                memcpy(n->left_data, e, two_three_t->data_size);
                n->left = left;
                n->right = right;

                return n;
            }else if((*compare_t)(e, n->right_data) > 0){
                // 分裂后树根的左右子树
                two_three_tree_node_t *left = two_three_tree_node_2(two_three_t->data_size, n->left_data, NULL, NULL);
                two_three_tree_node_t *right = two_three_tree_node_2(two_three_t->data_size, e, NULL, NULL);

                // 分裂后的树根
                memcpy(n->left_data, n->right_data, two_three_t->data_size);
                n->left = left;
                n->right = right;

                return n;
            }
        }
        return n;
    }


    if((*compare_t)(e, n->left_data) < 0){
        bool n_left_is_tree = two_three_tree_node_is_three(n->left);
        n->left = two_three_tree_add(two_three_t, n->left, e, compare_t);
        // 插入的是3节点的叶子节点，分裂之后新树的树根需要和其父亲节点进行融合
        if(n_left_is_tree){
            // 如果父亲节点是2节点
            if(!two_three_tree_node_is_three(n)){
                // 融合
                memcpy(n->left_data, n->left->left_data, two_three_t->data_size);
                two_three_tree_node_t *n_left = n->left;
                n->left = n->left->left;
                n->middle = n->left->right;

                two_three_tree_node_destroy(&(n_left));

                return n;
            } else{// 如果父亲节点是3节点
                // 融合-->分裂为3个2节点的子树
                // 分裂后树根的左右子树
                two_three_tree_node_t *right = two_three_tree_node_2(two_three_t->data_size, n->right_data, n->middle,
                                                                     n->right);

                // 分裂后的树根
                memcpy(n->right_data, n->left_data, two_three_t->data_size);
                n->right = right;

                return n;
            }
        }

    }
    else if((*compare_t)(e, n->left_data) > 0 && (*compare_t)(e, n->right_data) < 0){
        bool n_middle_is_tree = two_three_tree_node_is_three(n->middle);
        n->middle = two_three_tree_add(two_three_t, n->middle, e, compare_t);
        // 插入的是3节点的叶子节点，分裂之后新树的树根需要和其父亲节点进行融合
        if(n_middle_is_tree){
            // 父亲节点一定是3节点
            // 融合-->分裂为3个2节点的子树
            // 分裂后树根的左右子树
            two_three_tree_node_t *left_right = two_three_tree_node_2(two_three_t->data_size, n->left_data, NULL,
                                                                 NULL);
            two_three_tree_node_t *right_left = two_three_tree_node_2(two_three_t->data_size, n->right_data, NULL,
                                                                 NULL);

            two_three_tree_node_t *root = n->middle;
            root->left->left = n->left;
            root->right->right = n->right;
            root->left->right = left_right;
            root->right->left = right_left;

            two_three_tree_node_destroy(&n);

            return root;
        }
    }

    else if ((*compare_t)(e, n->right_data) > 0){
        bool n_right_is_tree = two_three_tree_node_is_three(n->right);
        n->right = two_three_tree_add(two_three_t, n->right, e, compare_t);
        // 插入的是3节点的叶子节点，分裂之后新树的树根需要和其父亲节点进行融合
        if(n_right_is_tree){
            // 如果父亲节点是2节点
            if(!two_three_tree_node_is_three(n)){
                // 融合
                memcpy(n->right_data, n->right->left_data, two_three_t->data_size);
                two_three_tree_node_t *n_left = n->right;
                n->right = n->right->right;
                n->middle = n->right->left;

                two_three_tree_node_destroy(&(n->right));

                return n;
            } else{// 如果父亲节点是3节点
                // 融合-->分裂为3个2节点的子树
                // 分裂后树根的左右子树
                two_three_tree_node_t *left = two_three_tree_node_2(two_three_t->data_size, n->left_data, n->left,
                                                                     n->middle);

                // 分裂后的树根
                memcpy(n->left_data, n->right_data, two_three_t->data_size);
                n->left = left;

                return n;
            }
        }
    }

    return n;
}

// 向二分搜索树中添加元素
Status two_three_tree_add_r(two_three_tree_t *two_three_t, void *e, compare_s compare_t)
{
    if(two_three_t == NULL)
        return OVERFLOW;

    two_three_t->root = two_three_tree_add(two_three_t, two_three_t->root, e, compare_t);

    return OK;
}

// 看以node为根的二分搜索树中是否包含e， 递归算法
bool two_three_tree_contain(two_three_tree_t *two_three_t, two_three_tree_node_t *n, void *e, compare_s compare_t)
{
    if(n == NULL){
        return false;
    }

    if((*compare_t)(e, n->left_data) == 0)
        return true;
    else if((*compare_t)(e, n->left_data) < 0)
        return two_three_tree_contain(two_three_t, n->left, e, compare_t);
    else if((*compare_t)(e, n->left_data) > 0 && (*compare_t)(e, n->right_data) < 0)
        return two_three_tree_contain(two_three_t, n->middle, e, compare_t);
    else// (*compare_t)(e, n->right_data) > 0
        return two_three_tree_contain(two_three_t, n->right, e, compare_t);
}

// 看二分搜索树中是否包含元素e
bool two_three_tree_contain_r(two_three_tree_t *two_three_t, void *e, compare_s compare_t)
{
    if(two_three_t == NULL)
        return OVERFLOW;

    return two_three_tree_contain(two_three_t, two_three_t->root, e, compare_t);
}


// 生产深度表示字符串
void two_three_tree_generate_depth_string(int depth)
{
    for(int i = 0; i < depth; i++)
        printf("%s", "--");
}

// 以node为根进行前序遍历， 递归算法
void two_three_tree_pre_order(two_three_tree_node_t *n, int depth, to_string_s to_string_t)
{
    if(n == NULL){
        two_three_tree_generate_depth_string(depth);
        printf("%s", "null\n");
        return;

    }

    two_three_tree_generate_depth_string(depth);
    char buffer[200];
    (*to_string_t)(n->left_data, buffer);
    printf("%s\n", buffer);

    (*to_string_t)(n->right_data, buffer);
    printf("%s\n", buffer);

    two_three_tree_pre_order(n->left, depth + 1, to_string_t);

    two_three_tree_pre_order(n->right, depth + 1, to_string_t);
}

// 二分搜索树的前序遍历
void two_three_tree_pre_order_r(two_three_tree_t *two_three_t, to_string_s to_string_t)
{
    two_three_tree_pre_order(two_three_t->root, 0, to_string_t);
}



// 以node为根进行中序遍历， 递归算法
void two_three_tree_in_order(two_three_tree_node_t *n, int depth, to_string_s to_string_t)
{
    if(n == NULL){
        two_three_tree_generate_depth_string(depth);
        printf("%s", "null\n");
        return;
    }

    two_three_tree_in_order(n->left, depth + 1, to_string_t);

    two_three_tree_generate_depth_string(depth);
    char buffer[200];
    (*to_string_t)(n->left_data, buffer);
    printf("%s\n", buffer);

    (*to_string_t)(n->right_data, buffer);
    printf("%s\n", buffer);

    two_three_tree_in_order(n->right, depth + 1, to_string_t);
}

// 二分搜索树的中序遍历
void two_three_tree_in_order_r(two_three_tree_t *two_three_t, to_string_s to_string_t)
{
    two_three_tree_in_order(two_three_t->root, 0, to_string_t);
}

// 以node为根进行后序遍历， 递归算法
void two_three_tree_post_order(two_three_tree_node_t *n, int depth, to_string_s to_string_t)
{
    if(n == NULL){
        two_three_tree_generate_depth_string(depth);
        printf("%s", "null\n");
        return;

    }

    two_three_tree_post_order(n->left, depth + 1, to_string_t);

    two_three_tree_post_order(n->right, depth + 1, to_string_t);

    two_three_tree_generate_depth_string(depth);
    char buffer[200];
    (*to_string_t)(n->left_data, buffer);
    printf("%s\n", buffer);

    (*to_string_t)(n->right_data, buffer);
    printf("%s\n", buffer);
}

// 二分搜索树的后序遍历
void two_three_tree_post_order_r(two_three_tree_t *two_three_t, to_string_s to_string_t)
{
    two_three_tree_post_order(two_three_t->root, 0, to_string_t);
}


// 二分搜索树的层序遍历，非递归实现
void two_three_tree_level_order_nr(two_three_tree_t *two_three_t, to_string_s to_string_t)
{
    linked_list_queue_t *q = linked_list_queue(sizeof(two_three_tree_node_t));

    linked_list_queue_enqueue(q, two_three_t->root);
    while (!linked_list_queue_is_empty(q)){
        two_three_tree_node_t *cur = two_three_tree_node_2(two_three_t->data_size, NULL, NULL, NULL);
        linked_list_queue_dequeue(q, cur);
        char buffer[200];
        (*to_string_t)(cur->left_data, buffer);
        printf("%s\n", buffer);

        (*to_string_t)(cur->right_data, buffer);
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
Status two_three_tree_minimum(two_three_tree_node_t *n, two_three_tree_node_t *minimum_n, int data_size)
{
    if(n->left == NULL){
        // n是指向节点的指针，所以不能直接返回该指针，需要用一块内存来接收它所指向的那块内存
        // 但是直接将n的整个内存拷贝走，会把n->data数据区域的指针也拷贝走，导致改变了接收方的数据域的data指针
        // 所以应该使用一对一赋值的方式将n的left/right/tree_size这些非自己申请内存的变量赋值给接收方，然后对于数据区域data这种自主管理内存的数据，使用memcpy进行内存赋值
        // n->data是指向数据的指针，所以不能直接返回该指针，需要用一块内存来接收它所指向的那块内存
        two_three_tree_node_copy(n, minimum_n, data_size);

        return OK;
    }

    return two_three_tree_minimum(n->left, minimum_n, data_size);

}

// 寻找二分搜索树的最小元素
Status two_three_tree_minimum_r(two_three_tree_t *two_three_t, void *ret)
{
    if(two_three_tree_is_empty(two_three_t))
        exit(OVERFLOW);

    two_three_tree_node_t *minimum_n = two_three_tree_node_2(two_three_t->data_size, NULL, NULL, NULL);
    two_three_tree_minimum(two_three_t->root, minimum_n, two_three_t->data_size);
    void *elem = minimum_n->left_data;
    memcpy(ret, elem, two_three_t->data_size);

    two_three_tree_node_destroy(&minimum_n);

    return OK;
}

// 找寻以node为根的树中的最大元素， 递归算法
Status two_three_tree_maximum(two_three_tree_node_t *n, two_three_tree_node_t *maximum_n, int data_size)
{
    if(n->right == NULL){
        two_three_tree_node_copy(n, maximum_n, data_size);
        return OK;
    }

    return two_three_tree_maximum(n->right, maximum_n, data_size);

}

// 寻找二分搜索树的最大元素
Status two_three_tree_maximum_r(two_three_tree_t *two_three_t, void *ret)
{
    if(two_three_tree_is_empty(two_three_t))
        exit(OVERFLOW);

    two_three_tree_node_t *maximum_n = two_three_tree_node_2(two_three_t->data_size, NULL, NULL, NULL);
    two_three_tree_maximum(two_three_t->root, maximum_n, two_three_t->data_size);
    void *elem = maximum_n->right_data;
    memcpy(ret, elem, two_three_t->data_size);
    two_three_tree_node_destroy(&maximum_n);

    return OK;
}


// 删除以node为根的二分搜索树的最小节点
// 返回删除最小节点之后新的二分搜索树的根
two_three_tree_node_t *two_three_tree_remove_minimum(two_three_tree_t *two_three_t, two_three_tree_node_t *n)
{
    if(n->left == NULL){
        two_three_tree_node_t *right_node = n->right;
        n->right = NULL;
        two_three_tree_node_destroy(&n);
        two_three_t->size --;
        return right_node;
    }

    n->left = two_three_tree_remove_minimum(two_three_t, n->left);

    return n;
}

// 删除二分搜索树中最小的元素
Status two_three_tree_remove_minimum_r(two_three_tree_t *two_three_t, void *ret)
{
    if(two_three_tree_is_empty(two_three_t))
        exit(OVERFLOW);

    two_three_tree_minimum_r(two_three_t, ret);

    two_three_t->root = two_three_tree_remove_minimum(two_three_t, two_three_t->root);

    return OK;
}

// 删除以node为根的二分搜索树的最大节点
// 返回删除最大节点之后新的二分搜索树的根
two_three_tree_node_t *two_three_tree_remove_maximum(two_three_tree_t *two_three_t, two_three_tree_node_t *n)
{
    if(n->right == NULL){
        two_three_tree_node_t *left_node = n->left;
        n->left = NULL;
        two_three_tree_node_destroy(&n);
        two_three_t->size --;
        return left_node;
    }

    n->right = two_three_tree_remove_maximum(two_three_t, n->right);
    return n;
}

// 删除二分搜索树中最大的元素
Status two_three_tree_remove_maximum_r(two_three_tree_t *two_three_t, void *ret)
{
    if(two_three_tree_is_empty(two_three_t))
        exit(OVERFLOW);

    two_three_tree_maximum_r(two_three_t, ret);

    two_three_t->root = two_three_tree_remove_maximum(two_three_t, two_three_t->root);

    return OK;
}

// 删除以node为根的二分搜索树中的元素e，递归算法
// 返回删除节点后新的二分搜索树的根
two_three_tree_node_t *two_three_tree_remove(two_three_tree_t *two_three_t, two_three_tree_node_t *n, void *e, compare_s compare_t)
{
    if(n == NULL)
        return NULL;

    if ((*compare_t)(e, n->left_data) < 0) {
        n->left = two_three_tree_remove(two_three_t, n->left, e, compare_t);
        return n;
    } else if((*compare_t)(e, n->left_data) > 0 && (*compare_t)(e, n->right_data) < 0){
        n->middle = two_three_tree_remove(two_three_t, n->middle, e, compare_t);
        return n;
    }else if((*compare_t)(e, n->right_data) > 0){
        n->right = two_three_tree_remove(two_three_t, n->right, e, compare_t);
        return n;
    } else{ // e = n->data
        // 待删除节点左子树为空的情况
        if(n->left == NULL){
            two_three_tree_node_t *right_node = n->right;
            n->right = NULL;
            two_three_tree_node_destroy(&n);
            two_three_t->size --;
            return right_node;
        }

        // 待删除节点右子树为空的情况
        if(n->right == NULL){
            two_three_tree_node_t *left_node = n->left;
            n->left = NULL;
            two_three_tree_node_destroy(&n);
            two_three_t->size --;
            return left_node;
        }

        // 待删除节点左右子树都不为空的情况
        // 找到比待删除节点大的最小节点，即待删除节点右子树的最小节点
        // 用这个节点代替待删除节点的位置
        two_three_tree_node_t *successor = two_three_tree_node_2(two_three_t->data_size, NULL, NULL, NULL);
        two_three_tree_minimum(n->right, successor, two_three_t->data_size);
        successor->right = two_three_tree_remove_minimum(two_three_t, n->right);
        successor->left = n->left;

        two_three_tree_node_destroy(&n);

        return successor;
    }
}

// 删除二分搜索数中为e的元素
Status two_three_tree_remove_r(two_three_tree_t *two_three_t, void *e, compare_s compare_t)
{
    if(two_three_tree_is_empty(two_three_t))
        exit(OVERFLOW);

    two_three_t->root = two_three_tree_remove(two_three_t, two_three_t->root, e, compare_t);

    return OK;
}


// 清空以node为根的二分搜索树
void two_three_tree_clear(two_three_tree_node_t **n)
{
    if(*n == NULL){
        return;
    }

    two_three_tree_clear(&((*n)->left));
    two_three_tree_clear(&((*n)->right));

    two_three_tree_node_destroy(n);

}

// 清空二分搜索树
Status two_three_tree_clear_r(two_three_tree_t *two_three_t)
{
    two_three_tree_clear(&(two_three_t->root));
    two_three_t->size = 0;

    return OK;
}


// 销毁二分搜索树
Status two_three_tree_destroy(two_three_tree_t **two_three_t)
{
    two_three_tree_clear_r(*two_three_t);
    *two_three_t = NULL;

    return OK;
}

