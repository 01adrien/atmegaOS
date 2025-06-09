#include "timer.h"
#include "libatmega/systick.h"

/*
Passez a une delta liste plus tard
Une delta list est une liste chaînée où chaque timer stocke le temps
restant par rapport au précédent. Seul le premier timer de la liste
est décrémenté à chaque tick ; quand il expire, le suivant devient
le nouveau head et son count est ajusté automatiquement.
Ce mécanisme permet de gérer efficacement de nombreux timers avec
un minimum d’opérations à chaque interruption (juste décrémenter le premier),
au lieu de tous les parcourir.

Lors de l’insertion d’un timer, son champ remaining_ms doit représenter le temps
relatif après le précédent timer de la liste.
Si le nouveau timer est inséré avant un autre,
il faut réduire le count du suivant pour maintenir la synchronisation.
attention au timer périodique, le retirer de la liste et le reinserer
a la bonne position.
*/

static uint8_t timers_count = 0;
static Timer *timers = NULL;
static Timer timers_pool[MAX_TIMERS] = {0};

Timer *timer_alloc(void)
{
    return timers_count == MAX_TIMERS
               ? NULL
               : timers_pool + (timers_count++);
}

bool timer_start(uint32_t ms, TimerType type, TimerCallback callback, void *args)
{
    Timer *t = timer_alloc();
    if (t)
    {
        t->state = TIMER_ACTIVE;
        t->type = type;
        t->duration_ms = ms;
        t->remaining_ms = ms;
        t->callback = callback;
        t->args = args;
        t->next = timers;
        timers = t;
        return true;
    }
    return false;
}

const Timer *timer_get(void)
{
    return timers;
}

/*
les timer ne peuvent pas se decaler car ce code est executer a chaque ms
et le cpu peut faire 16000 operation par ms et timer_tick ne fait
qu'incrementer les timers, le callback et appellé hors interrupt (polling)
*/
void timer_tick(void)
{
    Timer *t = timers;
    while (t)
    {
        if (t->state == TIMER_ACTIVE && t->remaining_ms > 0)
        {
            t->remaining_ms--;
            if (t->remaining_ms == 0)
            {
                t->state = TIMER_DONE;
            }
        }
        t = t->next;
    }
}

void timer_poll(void)
{
    Timer *t = timers;
    while (t)
    {
        if (t->state == TIMER_DONE && t->callback)
        {
            t->callback(t->args);
            if (t->type == TIMER_ONESHOT)
            {
                t->state = TIMER_IDLE;
                t->callback = NULL;
            }
            else
            {
                t->remaining_ms = t->duration_ms;
                t->state = TIMER_ACTIVE;
            }
        }
        t = t->next;
    }
}
