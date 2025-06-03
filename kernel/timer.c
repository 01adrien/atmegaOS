#include "timer.h"
#include <libatmega/systick.h>
#include <stddef.h>
#include <stdlib.h>

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

Timer timers[8];
static Timer *head = NULL;

void timer_setup(void)
{
    systick_register_hook(timer_tick);
    systick_init();
}

void timer_start(Timer *t, uint32_t ms, TimerType type, TimerCallback callback, void *args)
{

    t->state = TIMER_ACTIVE;
    t->type = type;
    t->duration_ms = ms;
    t->remaining_ms = ms;
    t->callback = callback;
    t->args = args;
    t->next = head;
    head = t;
}

Timer *timer_alloc(void)
{
    for (int i = 0; i < MAX_TIMERS; ++i)
    {
        if (timers[i].state == TIMER_IDLE)
        {
            return &timers[i];
        }
    }
    return NULL; // Pas de timer disponible
}

const Timer *timer_get()
{
    return head;
}

/*
les timer ne peuvent pas se decaler car ce code est executer a chaque ms
et le cpu peut faire 16000 operation par ms et timer_tick ne fait
qu'incrementer les timers, le callback et appellé hors interrupt
*/
void timer_tick(void) // executer dans l'ISR 18 (timer0 ovf)
{
    Timer *t = head;
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
    Timer *t = head;
    Timer *p = NULL;
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
        p = t;
        t = t->next;
    }
}
