#include "counter.h"

#define TOIE (0)
#define WGM0 (0)
#define WGM1 (1)
#define WGM2 (3)
#define CS0 (0)
#define CS1 (1)
#define CS2 (2)

static Counter8 counters[] = {
    [COUNTER0] = {
        .tccra = TCCR0A,
        .tccrb = TCCR0B,
        .timsk = TIMSK0,
        .tcnt = TCNT0,
        .pr_bit = PRTIM0,
    },
    [COUNTER2] = {
        .tccra = TCCR2A,
        .tccrb = TCCR2B,
        .timsk = TIMSK2,
        .tcnt = TCNT2,
        .pr_bit = PRTIM2,
    },
};

void counter_enable_clock(CounterId id)
{
    Counter8 *c = &counters[id];
    MMIO8(PRR0) &= ~(1 << c->pr_bit);
}

void counter_reset(CounterId id)
{
    Counter8 *c = &counters[id];
    MMIO8(c->tcnt) = 0;
}

void counter_set_mode(CounterId id, CounterMode mode)
{
    Counter8 *c = &counters[id];
    switch (mode)
    {
    case COUNTER_MODE_NORMAL:
        MMIO8(c->tccra) &= ~((1 << WGM0) | (1 << WGM1));
        MMIO8(c->tccrb) &= ~(1 << WGM2);
        break;

    case COUNTER_MODE_CTC:
        // TODO
        break;

    case COUNTER_MODE_PHASE_PWM:
        // TODO
        break;

    case COUNTER_MODE_FAST_PWM:
        // TODO
        break;

    default:
        break;
    }
}

void counter_enable_interrupt(CounterId id, CounterMode mode)
{
    // pour l’instant, seulement overflow en mode normal
    Counter8 *c = &counters[id];
    if (mode == COUNTER_MODE_NORMAL)
        MMIO8(c->timsk) |= (1 << TOIE);
}

void counter_set_prescaler(CounterId id, CounterPrescaler prescaler)
{
    Counter8 *c = &counters[id];
    // Remise à zéro des bits CSxx
    MMIO8(c->tccrb) &= ~((1 << CS0) | (1 << CS1) | (1 << CS2));

    switch (prescaler)
    {
    case COUNTER_PRESCALER_1:
        MMIO8(c->tccrb) |= (1 << CS0); // 001
        break;
    case COUNTER_PRESCALER_8:
        MMIO8(c->tccrb) |= (1 << CS1); // 010
        break;
    case COUNTER_PRESCALER_64:
        MMIO8(c->tccrb) |= (1 << CS0) | (1 << CS1); // 011
        break;
    case COUNTER_PRESCALER_256:
        MMIO8(c->tccrb) |= (1 << CS2); // 100
        break;
    case COUNTER_PRESCALER_1024:
        MMIO8(c->tccrb) |= (1 << CS0) | (1 << CS2); // 101
        break;
    default:
        // Aucune horloge — arrêt du timer
        break;
    }
}
