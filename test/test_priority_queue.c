#include "priority_queue.h"
#include <criterion/criterion.h>
#include <criterion/internal/assert.h>
#include <signal.h>

Test(priority_queue, new)
{
    priority_queue *queue = priority_queue_new(10);
    cr_assert_not_null(queue);
    cr_assert_not_null(queue->data);
    cr_assert_eq(queue->capacity, 10);
    cr_assert_eq(queue->length, 0);
}

Test(priority_queue, from_array)
{
    int             xs[] = {12, 10, 11, 100};
    priority_queue *queue = priority_queue_from_array(xs, 4);
    cr_assert_eq(queue->capacity, 4);
    cr_assert_eq(queue->length, 4);
    cr_assert_eq(queue->data[0], 100);
}

Test(priority_queue, heapsort)
{
    int xs[] = {12, 10, 11, 100};
    priority_queue_heapsort(xs, 4);
    cr_assert_eq(xs[0], 100);
    cr_assert_eq(xs[1], 12);
    cr_assert_eq(xs[2], 11);
    cr_assert_eq(xs[3], 10);
}

Test(priority_queue, destroy)
{
    priority_queue *queue = priority_queue_new(10);
    priority_queue_destroy(queue);
}

Test(priority_queue, push_in_order)
{
    priority_queue *queue = priority_queue_new(10);
    priority_queue_push(queue, 42);
    cr_assert_eq(queue->length, 1);
    cr_log_info("data %d", queue->data[0]);
    cr_assert_eq(queue->data[0], 42);
    priority_queue_push(queue, 21);
    cr_assert_eq(queue->length, 2);
    cr_assert_eq(queue->data[1], 21);
    priority_queue_push(queue, 22);
    cr_assert_eq(queue->length, 3);
    cr_assert_eq(queue->data[2], 22);
}

Test(priority_queue, push_out_of_order)
{
    priority_queue *queue = priority_queue_new(10);
    priority_queue_push(queue, 42);
    cr_assert_eq(queue->length, 1);
    cr_log_info("data %d", queue->data[0]);
    cr_assert_eq(queue->data[0], 42);
    priority_queue_push(queue, 100);
    cr_assert_eq(queue->length, 2);
    cr_assert_eq(queue->data[0], 100);
    cr_assert_eq(queue->data[1], 42);
    priority_queue_push(queue, 43);
    cr_assert_eq(queue->length, 3);
    cr_assert_eq(queue->data[0], 100);
    cr_assert_eq(queue->data[1], 42);
    cr_assert_eq(queue->data[2], 43);
    priority_queue_push(queue, 55);
    cr_assert_eq(queue->length, 4);
    cr_assert_eq(queue->data[0], 100);
    cr_assert_eq(queue->data[1], 55);
    cr_assert_eq(queue->data[2], 43);
    cr_assert_eq(queue->data[3], 42);
}

Test(priority_queue, push_full_crash, .signal = SIGABRT)
{
    priority_queue *queue = priority_queue_new(1);
    priority_queue_push(queue, 42);
    priority_queue_push(queue, 43);
}

Test(priority_queue, replace_in_order)
{
    priority_queue *queue = priority_queue_new(10);
    priority_queue_push(queue, 12);
    priority_queue_push(queue, 11);
    priority_queue_push(queue, 10);
    priority_queue_replace(queue, 100);
    cr_assert_eq(queue->length, 3);
    cr_assert_eq(queue->data[0], 100);
    cr_assert_eq(queue->data[1], 11);
    cr_assert_eq(queue->data[2], 10);
}

Test(priority_queue, replace_out_of_order)
{
    priority_queue *queue = priority_queue_new(10);
    priority_queue_push(queue, 12);
    priority_queue_push(queue, 11);
    priority_queue_push(queue, 10);
    priority_queue_replace(queue, 5);
    cr_assert_eq(queue->length, 3);
    cr_assert_eq(queue->data[0], 11);
    cr_assert_eq(queue->data[1], 5);
    cr_assert_eq(queue->data[2], 10);
}

Test(priority_queue, pop)
{
    priority_queue *queue = priority_queue_new(10);
    priority_queue_push(queue, 12);
    priority_queue_push(queue, 13);
    priority_queue_push(queue, 11);
    priority_queue_push(queue, 100);
    cr_assert_eq(priority_queue_pop(queue), 100);
    cr_assert_eq(priority_queue_pop(queue), 13);
    cr_assert_eq(priority_queue_pop(queue), 12);
    cr_assert_eq(priority_queue_pop(queue), 11);
}

Test(priority_queue, pop_empty_crash, .signal = SIGABRT)
{
    priority_queue *queue = priority_queue_new(11);
    priority_queue_pop(queue);
}
