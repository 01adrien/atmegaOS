#include <libatmega/systick.h>
#include <libatmega/gpio.h>
#include <kernel/timer.h>
#include <stddef.h>

#define FCPU (16000000)

#define PIN (2)

#define PORT (PORTA)

void test_interrupt()
{
    gpio_mode_setup(PORT, GPIO_MODE_OUTPUT, PIN);
    uint64_t last = 0;
    uint64_t sec = 0;
    while (1)
    {
        {
            if (get_tick() - last >= 1000)
            {
                gpio_toggle(PORT, PIN);
                last = get_tick();
                sec++;
            }
        }
    }
}

void callback1(void *arg)
{
    uint64_t t = get_tick();
}

void callback2(void *arg)
{
    uint64_t t = get_tick();
}

void callback3(void *arg)
{
    uint64_t t = get_tick();
}

void test_timer()
{
    timer_start(timer_alloc(), 3000, TIMER_PERIODIC, callback1, NULL);
    timer_start(timer_alloc(), 2000, TIMER_PERIODIC, callback2, NULL);
    timer_start(timer_alloc(), 1000, TIMER_PERIODIC, callback3, NULL);

    while (1)
    {
        timer_poll(); // si besoin de gestion non-interruptive
    }
}

int main(void)
{
    systick_init();
    test_interrupt();
    // test_timer();
}
