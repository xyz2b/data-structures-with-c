//
// Created by 焦宏宇 on 2020/2/20.
//

#ifndef DATA_STRUCTURES_UNION_FIND_1_H
#define DATA_STRUCTURES_UNION_FIND_1_H
#include <stdbool.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define OVERFLOW -1
typedef int Status;

typedef struct union_find_1_s{
    int elem_size;
    int size;
    void *id;
}union_find_1_t;

union_find_1_t *union_find_1(int size, int elem_size);
int union_find_1_size(union_find_1_t *union_f);
void *union_find_1_find(union_find_1_t *union_f, int p, void *id);
bool union_find_1_is_connected(union_find_1_t *union_f, int p, int q);
Status union_find_1_union(union_find_1_t *union_f, int p, int q);

#endif //DATA_STRUCTURES_UNION_FIND_1_H
