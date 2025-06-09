#include "systick.h"
#include "interrupt.h"
#include "counter.h"
#include "kernel/timer.h"

/*
Calcul du prescaler
prescaler = (Tinterrupt​ × FCPU) / Ncounts​​ + 1
FCPU = 16.000.000
Tinterrupt = 0.001s
Ncounts = 256 (max 8bit + 1)
prescaler (clk / 64), compte de 0 => 255 en 1.24ms

pour plus de precision dans le timer changer en mode CTC (Clear Timer on Compare Match)
ou utiliser une reload value
*/

void timer0_compb_handler(void)
{
    systick_increment();
}

void systick_init(void)
{
    CounterId c = COUNTER0;
    counter_enable_clock(c);
    counter_reset(c);
    counter_set_mode(c, COUNTER_MODE_CTC);
    counter_set_ctc_top(c, 249);
    counter_enable_interrupt(c, COUNTER_INT_OCB);
    counter_set_prescaler(c, COUNTER_PRESCALER_64);
    interrupt_enable();
}

static volatile uint64_t tick = 0;

uint64_t get_tick(void)
{
    // desactiver les interruptions globales pour lire tick
    // car si plus de 8 bits il faut plusieurs operations
    // il pourrait y avoir une autre interrupt
    uint64_t t;
    ATOMIC_BLOCK({
        t = tick;
    });
    return t;
}

inline void systick_increment(void)
{
    tick++;
    timer_tick();
}
