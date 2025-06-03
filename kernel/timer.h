#if !defined(_TIMER_H_)
#define _TIMER_H_

#include <stdint.h>

#define MAX_TIMERS (8)

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
    void *args; // pointeur vers les argument(s) du callback
    struct Timer *next;
} Timer;

void timer_setup(void);
void timer_start(Timer *t, uint32_t ms, TimerType type, TimerCallback cb, void *ctx);
Timer *timer_alloc();
const Timer *timer_get();
void timer_tick(void); // à appeler dans l'ISR
void timer_poll(void); // à appeler dans la boucle principale pour ne pas surcharger ISR

#endif // _TIMER_H_
