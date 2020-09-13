//
// Created by 焦宏宇 on 2020/2/20.
//

#ifndef DATA_STRUCTURES_UNION_FIND_2_H
#define DATA_STRUCTURES_UNION_FIND_2_H
#include <stdbool.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define OVERFLOW -1
typedef int Status;

typedef struct union_find_2_s{
    int elem_size;
    int size;
    void *parent;
}union_find_2_t;

union_find_2_t *union_find_2(int size);
int union_find_2_size(union_find_2_t *union_f);
int union_find_2_find(union_find_2_t *union_f, int p);
bool union_find_2_is_connected(union_find_2_t *union_f, int p, int q);
Status union_find_2_union(union_find_2_t *union_f, int p, int q);
#endif //DATA_STRUCTURES_UNION_FIND_2_H
