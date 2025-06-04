#include "counter.h"

static Counter8 counters[] = {
    [COUNTER0] = {
        .tccra = TCCR0A,
        .tccrb = TCCR0B,
        .timsk = TIMSK0,
        .tcnt = TCNT0,
        .ocra = OCR0A,
        .orcb = OCR0B,
        .pr_bit = PRTIM0,
    },
    [COUNTER2] = {
        .tccra = TCCR2A,
        .tccrb = TCCR2B,
        .timsk = TIMSK2,
        .tcnt = TCNT2,
        .ocra = OCR2A,
        .orcb = OCR2B,
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
    // remise a zero des bits (not safe ??)
    MMIO8(c->tccra) &= ~((1 << WGM0) | (1 << WGM1));
    MMIO8(c->tccrb) &= ~(1 << WGM2);

    switch (mode)
    {
    case COUNTER_MODE_NORMAL: // 000
        break;

    case COUNTER_MODE_CTC: // 010
        MMIO8(c->tccra) |= (1 << WGM1);
        break;

    case COUNTER_MODE_PHASE_PWM: // 101 || 001
        // TODO
        break;

    case COUNTER_MODE_FAST_PWM: // 011 || 111
        // TODO
        break;

    default:
        break;
    }
}

void counter_enable_interrupt(CounterId id, uint8_t mask)
{
    Counter8 *c = &counters[id];
    // MMIO8(c->timsk) |= ((1 << TOIE) | (1 << OCIEA) | (1 << OCIEB));
    MMIO8(c->timsk) |= mask;
}

void counter_disable_interrupt(CounterId id, uint8_t mask)
{
    Counter8 *c = &counters[id];
    MMIO8(c->timsk) &= ~(mask);
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

void counter_set_oc_value(CounterId id, uint8_t value, CounterCompare cmp)
{
    Counter8 *c = &counters[id];
    switch (cmp)
    {
    case COUNTER_OCA:
        MMIO8(c->ocra) = value;
        break;
    case COUNTER_OCB:
        MMIO8(c->orcb) = value;
        break;
    default:
        break;
    }
}

void counter_set_ctc_top(CounterId id, uint8_t value)
{
    Counter8 *c = &counters[id];
    MMIO8(c->ocra) = value;
}