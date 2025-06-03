#ifndef _COUNTER_H_
#define _COUNTER_H_

#include "memory_map.h"

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
    COUNTER_PRESCALER_1 = 1,
    COUNTER_PRESCALER_8 = 8,
    COUNTER_PRESCALER_64 = 64,
    COUNTER_PRESCALER_256 = 256,
    COUNTER_PRESCALER_1024 = 1024
} CounterPrescaler;

typedef struct
{
    uint8_t tccra;
    uint8_t tccrb;
    uint8_t timsk;
    uint8_t tcnt;
    uint8_t pr_bit;
} Counter8;

void counter_enable_clock(CounterId id);
void counter_reset(CounterId id);
void counter_set_mode(CounterId id, CounterMode mode);
void counter_set_prescaler(CounterId id, CounterPrescaler prescaler);
void counter_enable_interrupt(CounterId id, CounterMode mode);

#endif // _COUNTER_H_
