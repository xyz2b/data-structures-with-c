//
// Created by 焦宏宇 on 3030/3/30.
//

#ifndef DATA_STRUCTURES_UNION_FIND_3_H
#define DATA_STRUCTURES_UNION_FIND_3_H
#include <stdbool.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define OVERFLOW -1
typedef int Status;

typedef struct union_find_3_s{
    int elem_size;
    int union_find_size;
    void *parent;
    void *size; // size[i]表示以i为根的集合中元素个数
}union_find_3_t;

union_find_3_t *union_find_3(int size);
int union_find_3_size(union_find_3_t *union_f);
int union_find_3_find(union_find_3_t *union_f, int p);
bool union_find_3_is_connected(union_find_3_t *union_f, int p, int q);
Status union_find_3_union(union_find_3_t *union_f, int p, int q);

#endif //DATA_STRUCTURES_UNION_FIND_3_H
