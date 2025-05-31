#include <libatmega/gpio.h>
#include <libatmega/systick.h>

#define FCPU (16000000)

#define PIN (2)

#define PORT (PORTA)
uint64_t sec = 0;

void test_interrupt()
{
    systick_init();
    gpio_mode_setup(PORT, GPIO_MODE_OUTPUT, PIN);
    uint64_t last = 0;
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

int main(void)
{
    test_interrupt();
}
