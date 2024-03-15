#include "priority_queue.h"
#include <criterion/criterion.h>

Test(priority_queue, new)
{
    priority_queue *queue = priority_queue_new(10);
    cr_assert_not_null(queue);
    cr_assert_not_null(queue->data);
    cr_assert_eq(queue->capacity, 10);
    cr_assert_eq(queue->length, 0);
}

Test(priority_queue, destroy)
{
    priority_queue *queue = priority_queue_new(10);
    priority_queue_destroy(queue);
}
