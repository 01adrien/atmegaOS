#include "systick.h"
#include "interrupt.h"

// TCCR0A
#define WGM00 (0)
#define WGM01 (1)
#define COM0B0 (4)
#define COM0B1 (5)
#define COM0A0 (6)
#define COM0A1 (7)
// TCCR0B
#define CS00 (0)
#define CS01 (1)
#define CS02 (2)
#define WGM02 (3)
// TIMSK0
#define TOIE0 (0)
#define OCIEA (1)
#define OCIEB (2)

/*
Calcul du prescaler
prescaler = (Tinterrupt​ × FCPU) / Ncounts​​ + 1
FCPU = 16.000.000
Tinterrupt = 0.001s
Ncounts = 256 (max 8bit + 1)
prescaler (clk / 64), compte de 0 => 255 en 1.24ms

pour plus de precision dans le timer changer en mode CTC (Clear Timer on Compare Match)
*/

void systick_init(void)
{
    // active timer 0 (pas utile pour simulide)
    MMIO(PRR0) &= ~(1 << PRTIM0);
    // config mode normal sur timer overflow a 255
    MMIO(TCCR0A) &= ~((1 << WGM00) | (1 << WGM01));
    MMIO(TCCR0B) &= ~(1 << WGM02);
    // config du prescaler 64
    MMIO(TCCR0B) &= ~((1 << CS02) | (1 << CS01) | (1 << CS00)); // clear prescaler bits
    MMIO(TCCR0B) |= (1 << CS01) | (1 << CS00);                  // prescaler 64
    // activation interruption sur l'overflow
    MMIO(TIMSK0) |= (1 << TOIE0);
    interrupt_enable();
}

static volatile uint64_t tick = 0;

uint64_t get_tick(void)
{
    // desactiver les interruptions globales pour lire tick
    // car si plus de 8 bits il faut plusieurs operations
    // il pourrait y avoir une autre interrupt
    interrupt_disable();
    uint64_t t = tick;
    interrupt_enable();
    return t;
}

inline void systick_increment(void)
{
    tick++;
}