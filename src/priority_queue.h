#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include <stdio.h>
#include <stdlib.h>

// typedef struct {
//     int priority;
//     void *data;
// } priority_queue_elem;

// typedef priority_queue_elem* priority_queue;

typedef struct
{
    size_t length;
    size_t capacity;
    int   *data;
} priority_queue;

priority_queue *priority_queue_new(size_t capacity);
void            priority_queue_destroy(priority_queue *queue);
void            priority_queue_push(priority_queue *queue, int datum);
int             priority_queue_replace(priority_queue *queue, int datum);
int             priority_queue_pop(priority_queue *queue);
void            priority_queue_print(priority_queue *queue);

#endif
