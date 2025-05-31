#if !defined(_SYSTICK_H_)
#define _SYSTICK_H_

#include "memory_map.h"

/*
Un seul timer pour l'instant (timer 0 => TC0)

L’activation de TC0 dépend du registre de réduction de puissance (PPR0):
    Le bit PRTIM0 du PPR doit être mis à 0 pour activer TC0.

TCNT0 (Timer/Counter Register 0):
    pour acceder a la valeur du timer 0

OCR0B et OCR0A (Output Compare Register A/B):
    registre de comparaison pour declenchement interupt ou autre pwm, uart ...

TCCR0A et TCCR0B (Timer/Counter Control Register A/B):
    controle du signal du timer sur chaque temps d'horloge:
        - count => incremente ou decremente de 1
        - direction => selectione entre inc et dec
        - clear => remet a zero
        - clk => clock generale ??
        - top => signale que le compteur et au max
        - bottom => signale que le compteur est au min

TIFR0 (Timer Interrupt Flag Register 0):
    Contient les drapeaux (flags) d’interruptions pour TC0 :
        TOV0 : Overflow
        OCF0A : Compare Match A
        OCF0B : Compare Match B
    Ces flags sont levés par le matériel lors d’un événement (compare match)
    et réinitialisés par le logiciel en écrivant un 1.

TIMSK0 (Timer/Counter Interrupt Mask Register 0):
    active ou désactive les interruptions associées au TC0


PWM et signaux:
    Les broches OC0A et OC0B sont des fonctions alternatives sur des broches GPIO,
    contrôlées par le Timer0 pour générer des signaux PWM ou impulsions synchronisées.
    Les bits COM0x dans TCCR0A définissent leur comportement lors d’une comparaison avec OCR0x.
    La broche doit être configurée en sortie dans le DDR pour que le signal soit visible.
    Cela permet de produire des signaux modulés automatiquement, sans charge CPU.

*/

void systick_init(void);
uint64_t get_tick(void);
void systick_increment(void);

#endif // _SYSTICK_H_
