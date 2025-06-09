#include "libatmega/systick.h"
#include "libatmega/gpio.h"
#include "libatmega/usart.h"
#include "libatmega/interrupt.h"
#include "kernel/timer.h"
#include "kernel/io.h"

#define PIN (2)
#define PORT (PORTA)

void callback1(void *arg)
{
    printf("callback 1\n");
}

void callback2(void *arg)
{
    printf("callback 2\n");
}

void callback3(void *arg)
{
    printf("callback 3\n");
}

void test_timer()
{
    timer_init();
    timer_start(3000, TIMER_ONESHOT, callback1, NULL);
    timer_start(2000, TIMER_ONESHOT, callback2, NULL);
    timer_start(1000, TIMER_ONESHOT, callback3, NULL);

    while (1)
    {
        timer_poll();
    }
}

void usart0_init()
{
    UsartId u = USART0;
    ATOMIC_BLOCK({
        usart_enable_clock(u);
        usart_set_format(u, USART_FORMAT_8N1);
        usart_set_baudrate(u, BAUD_RATE);
        usart_set_mode(u, USART_MODE_ASYNC);
        usart_enable_interrupt(u);
        usart_enable(u);
    });
}

int main(void)
{
    systick_init();
    usart0_init();
    io_init();
    test_timer();
}
