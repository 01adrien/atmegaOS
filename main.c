#include "libatmega/systick.h"
#include "libatmega/gpio.h"
#include "libatmega/usart.h"
#include "libatmega/interrupt.h"
#include "kernel/timer.h"

#define PIN (2)
#define PORT (PORTA)
#define BAUD_RATE (115200)

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
}

void test_usart()
{
    UsartId u = USART0;
    interrupt_disable();
    usart_enable_clock(u);
    usart_set_format(u, USART_FORMAT_8N1);
    usart_set_baudrate(u, BAUD_RATE);
    usart_set_mode(u, USART_MODE_ASYNC);
    usart_enable_interrupt(u);
    usart_enable(u);
    interrupt_enable();

    if (usart_data_available())
    {
        uint8_t data_rx = usart_read_byte(u);
        uint8_t data_tx = data_rx + 5;
        usart_write_byte(u, data_tx);
    }
}

int main(void)
{
    systick_init();
    // test_interrupt();
    // test_timer();
    while (1)
    {
        test_usart();
    }
}
