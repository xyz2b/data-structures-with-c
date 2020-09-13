//
// Created by 焦宏宇 on 2020/2/8.
//

#ifndef DATASTRUCTURES_ARRAY_QUEUE_H
#define DATASTRUCTURES_ARRAY_QUEUE_H

#include "../../arrays/dynamic_array/dynamic_array.h"

struct array_queue_s
{
    dynamic_array_t *array;
};


#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define OVERFLOW -1
typedef int Status;


typedef struct array_queue_s array_queue_t;

array_queue_t *array_queue_c(int capacity, int element_size);
array_queue_t *array_queue(int element_size);
int array_queue_size(array_queue_t *array_queue);
bool array_queue_is_empty(array_queue_t *array_queue);
int array_queue_capacity(array_queue_t *array_queue);
Status array_queue_enqueue(array_queue_t *array_queue, void *e);
Status array_queue_dequeue(array_queue_t *array_queue, void *ret);
Status array_queue_front(array_queue_t *array_queue, void *ret);
void array_queue_show(array_queue_t *array_queue, to_string_s to_string_t);
Status array_queue_clear(array_queue_t *array_queue);
Status array_queue_destroy(array_queue_t **array_queue);



#endif //DATASTRUCTURES_ARRAY_QUEUE_H
