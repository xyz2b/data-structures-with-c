//
// Created by 焦宏宇 on 2020/2/8.
//

#ifndef DATASTRUCTURES_LOOP_QUEUE_H
#define DATASTRUCTURES_LOOP_QUEUE_H
#include "../../arrays/basic_array/base_array.h"

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define OVERFLOW -1
typedef int Status;

struct loop_queue_s
{
    void *data;
    int element_size;
    int size;
    int capacity;
    int front, tail;
};

typedef struct loop_queue_s loop_queue_t;


typedef Status (*to_string_s)(void *value, char *string);

loop_queue_t *loop_queue_c(int capacity, int element_size);
loop_queue_t *loop_queue(int element_size);
int loop_queue_size(loop_queue_t *loop_q);
int loop_queue_capacity(loop_queue_t *loop_q);
bool loop_queue_is_empty(loop_queue_t *loop_q);
Status loop_queue_resize(loop_queue_t *loop_q, int new_capacity);
Status loop_queue_enqueue(loop_queue_t *loop_q, void *e);
Status loop_queue_dequeue(loop_queue_t *loop_q, void *ret);
Status loop_queue_front(loop_queue_t *loop_q, void *ret);
Status loop_queue_clear(loop_queue_t *loop_q);
Status loop_queue_destroy(loop_queue_t **loop_q);
void loop_queue_show(loop_queue_t *loop_q, to_string_s to_string_t);

#endif //DATASTRUCTURES_LOOP_QUEUE_H
