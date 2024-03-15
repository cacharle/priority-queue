#include "priority_queue.h"

static void *xmalloc(size_t size)
{
    void *ret = malloc(size);
    if (ret == NULL)
        abort();
    return ret;
}

priority_queue *priority_queue_new(size_t capacity)
{
    priority_queue *queue = xmalloc(sizeof(priority_queue));
    queue->capacity = capacity;
    queue->length = 0;
    queue->data = xmalloc(sizeof(int) * capacity);
    return queue;
}

void priority_queue_destroy(priority_queue *queue)
{
    free(queue->data);
    free(queue);
}

void priority_queue_push(priority_queue *queue, int datum)
{
    if (queue->length >= queue->capacity)
        abort();
    queue->data[queue->length] = datum;
    size_t current_index = queue->length;
    queue->length++;
    while (current_index >= 0)
    {
        size_t parent_index = (current_index - (current_index % 2 == 0 ? 2 : 1)) / 2;
        int    parent = queue->data[parent_index];
        int    current = queue->data[current_index];
        if (parent >= current)
            break;
        queue->data[parent_index] = current;
        queue->data[current_index] = parent;
    }
}

int priority_queue_replace(priority_queue *queue, int datum)
{
    int max = queue->data[0];
    queue->data[0] = datum;
    int current_index = 0;
    while (current_index < queue->length)
    {
        size_t left_child_index = current_index * 2 + 1;
        size_t right_child_index = current_index * 2 + 2;
        int    left_child = queue->data[left_child_index];
        int    right_child = queue->data[right_child_index];
        int    current = queue->data[current_index];
        if (left_child > right_child && left_child > current)
        {
            queue->data[left_child_index] = current;
            queue->data[current_index] = left_child;
            current_index = left_child_index;
        }
        else if (right_child > left_child && right_child > current)
        {
            queue->data[right_child_index] = current;
            queue->data[current_index] = right_child;
            current_index = right_child_index;
        }
        else
            break;
    }
    return max;
}

int priority_queue_pop(priority_queue *queue)
{
    if (queue->length == 0)
        abort();
    int last = queue->data[queue->length - 1];
    queue->length--;
    return priority_queue_replace(queue, last);
}

void priority_queue_print(priority_queue *queue)
{
    printf("length=%zu [", queue->length);
    for (size_t i = 0; i < queue->length; i++)
    {
        printf("%d", queue->data[i]);
        if (i < queue->length - 1)
            fputs(", ", stdout);
    }
    fputs("]\n", stdout);
}
