#if !defined(TIMER_H)
#define TIMER_H

#include "common.h"

typedef enum
{
    TIMER_IDLE,
    TIMER_ACTIVE,
    TIMER_DONE
} TimerState;

typedef enum
{
    TIMER_ONESHOT,
    TIMER_PERIODIC
} TimerType;

typedef void (*TimerCallback)(void *ctx);

typedef struct Timer
{
    TimerState state;
    TimerType type;
    uint32_t duration_ms;  // durée totale
    uint32_t remaining_ms; // temps restant
    TimerCallback callback;
    void *args; // pointeur vers argument(s) du callback
    struct Timer *next;
} Timer;

bool timer_start(uint32_t ms, TimerType type, TimerCallback cb, void *ctx);
Timer *timer_alloc(void);
const Timer *timer_get(void);
void timer_tick(void); // à appeler dans l'ISR
void timer_poll(void); // à appeler dans la boucle principale pour ne pas surcharger ISR

#endif // TIMER_H
