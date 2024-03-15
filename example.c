#include "priority_queue.h"

int main(void)
{
    int xs[] = {12, 10, 11, 100};
    priority_queue_heapsort(xs, 4);
    // cr_assert_eq(xs[0], 100);
    // cr_assert_eq(xs[1], 12);
    // cr_assert_eq(xs[2], 11);
    // cr_assert_eq(xs[3], 10);

    return 0;
}
