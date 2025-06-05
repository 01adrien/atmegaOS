#include <assert.h>
#include <stdio.h>
#include "kernel/timer.h"

static int callback_called = 0;
void test_callback(void *arg)
{
    callback_called++;
}

// Fake version de systick_increment
void simulate_ticks(int ms)
{
    for (int i = 0; i < ms; i++)
    {
        timer_tick();
        timer_poll(); // simulate main loop
    }
}

void one_timer_test()
{

    // test timer one shot
    Timer *t1 = timer_alloc();
    timer_start(t1, 5, TIMER_ONESHOT, test_callback, NULL);
    simulate_ticks(5);
    assert(callback_called == 1);
    assert(t1->state == TIMER_IDLE);
    printf("✅ Test 1 OK\n");

    // test timer périodique
    Timer *t2 = timer_alloc();
    callback_called = 0;
    timer_start(t2, 3, TIMER_PERIODIC, test_callback, NULL);
    simulate_ticks(10);           // simulate 10 ms
    assert(callback_called == 3); // 3ms, 6ms, 9ms
    printf("✅ Test 2 OK\n");
}

int main(void)
{
    one_timer_test();
    return 0;
}