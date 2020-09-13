//
// Created by 焦宏宇 on 2020/2/20.
//

#ifndef DATA_STRUCTURES_UNION_FIND_6_H
#define DATA_STRUCTURES_UNION_FIND_6_H
#include <stdbool.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define OVERFLOW -1
typedef int Status;

typedef struct union_find_6_s{
    int elem_size;
    int union_find_size;
    void *parent;
    void *rank; // rank[i]表示根节点为i的树的高度
}union_find_6_t;

union_find_6_t *union_find_6(int size);
int union_find_6_size(union_find_6_t *union_f);
int union_find_6_find(union_find_6_t *union_f, int p);
bool union_find_6_is_connected(union_find_6_t *union_f, int p, int q);
Status union_find_6_union(union_find_6_t *union_f, int p, int q);
#endif //DATA_STRUCTURES_UNION_FIND_6_H
