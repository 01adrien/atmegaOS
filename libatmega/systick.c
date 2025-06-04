#include "systick.h"
#include "interrupt.h"
#include "counter.h"

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

void timer0_ovf_handler(void)
{
    systick_increment();
}

void timer2_ovf_handler(void)
{
    systick_increment();
}

void timer0_compb_handler(void)
{
    systick_increment();
}

void timer0_compa_handler(void)
{
    systick_increment();
}

void timer2_compa_handler(void)
{
    systick_increment();
}

void timer2_compb_handler(void)
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
    interrupt_disable();
    uint64_t t = tick;
    interrupt_enable();
    return t;
}

static void (*systick_hook)(void) = NULL;

void systick_register_hook(void (*callback)(void))
{
    systick_hook = callback;
}

inline void systick_increment(void)
{
    tick++;
    if (systick_hook)
        systick_hook();
}

/*
===========================
 EXEMPLE DE CALCUL TIMER
===========================

Microcontrôleur : générique (8 bits)
Fréquence d’horloge (F_CPU) : 6 MHz
Prescaler utilisé : 8
Timer : 8 bits → Max_count = 256
Délai souhaité : 300 microsecondes (µs)

---------------------------
 ÉTAPE 1 : Calcul du tick
---------------------------

Tick_duration = Prescaler / F_CPU
               = 8 / 6 000 000
               = 1.33 µs

Chaque tick du timer dure 1.33 microseconde.

-------------------------------
 ÉTAPE 2 : Nombre de ticks requis
-------------------------------

Counts_needed = Delay_time / Tick_duration
               = 300 µs / 1.33 µs
               ≈ 225 ticks

Il faut compter 225 ticks pour atteindre 300 µs.

-------------------------------
 ÉTAPE 3 : Calcul de la valeur de rechargement
-------------------------------

Reload_value = Max_count – Counts_needed
             = 256 – 225
             = 31

Il faut charger le timer avec la valeur 31.
Ainsi, il comptera de 31 jusqu'à 256 → soit 225 ticks → soit 300 µs.

--------------------------------
 UTILISATION DANS UNE ROUTINE
--------------------------------

- Initialiser le timer à 31 dans l'ISR.
- À chaque débordement (= 300 µs), incrémenter une variable globale.
- Quand cette variable atteint 1666 :
    1666 × 300 µs = 499.8 ms ≈ 500 ms
    → effectuer l’action (ex. : changer état d’une LED).

--------------------------------
 FORMULE GÉNÉRALE
--------------------------------

Reload_value = Max_count – (Delay_time / (Prescaler / F_CPU))

Ou, en microsecondes :

Reload_value = Max_count – (Delay_µs / (Prescaler / (F_CPU / 1_000_000)))

--------------------------------
 EXEMPLE RAPIDE POUR RÉUTILISATION
--------------------------------

- F_CPU = 12 MHz
- Prescaler = 64
- Delay = 500 µs

→ Tick = 64 / 12 000 000 = 5.33 µs
→ Counts_needed = 500 / 5.33 ≈ 94
→ Reload_value = 256 – 94 = 162
*/