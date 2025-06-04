#ifndef _COUNTER_H_
#define _COUNTER_H_

#include "memory_map.h"

// TIMSKx
#define TOIE (0)
#define OCIEA (1)
#define OCIEB (2)
// TCCRxA
#define WGM0 (0)
#define WGM1 (1)
// TCCRxB
#define WGM2 (3)
#define CS0 (0)
#define CS1 (1)
#define CS2 (2)

typedef enum
{
    COUNTER0,
    COUNTER2,
    COUNTER_MAX
} CounterId;

typedef enum
{
    COUNTER_MODE_NORMAL,
    COUNTER_MODE_CTC,
    COUNTER_MODE_FAST_PWM,
    COUNTER_MODE_PHASE_PWM,
} CounterMode;

typedef enum
{
    COUNTER_OCA,
    COUNTER_OCB,
} CounterCompare;

typedef enum
{
    COUNTER_PRESCALER_1 = 1,
    COUNTER_PRESCALER_8 = 8,
    COUNTER_PRESCALER_64 = 64,
    COUNTER_PRESCALER_256 = 256,
    COUNTER_PRESCALER_1024 = 1024
} CounterPrescaler;

typedef enum
{
    COUNTER_INT_OVF = (1 << TOIE),
    COUNTER_INT_OCA = (1 << OCIEA),
    COUNTER_INT_OCB = (1 << OCIEB),
} CounterInterrupt;

typedef struct
{
    uint8_t tccra;
    uint8_t tccrb;
    uint8_t timsk;
    uint8_t tcnt;
    uint8_t ocra;
    uint8_t orcb;
    uint8_t pr_bit;
} Counter8;

void counter_enable_clock(CounterId id);
void counter_reset(CounterId id);
void counter_set_mode(CounterId id, CounterMode mode);
void counter_enable_interrupt(CounterId id, uint8_t mask);
void counter_disable_interrupt(CounterId id, uint8_t mask);
void counter_set_prescaler(CounterId id, CounterPrescaler prescaler);
void counter_set_oc_value(CounterId id, uint8_t value, CounterCompare cmp);
void counter_set_ctc_top(CounterId id, uint8_t value);

#endif // _COUNTER_H_
