#include "gpio.h"
#include <stdio.h>
// selectionne mode pour la <pin> du <reg> DDRx
// TODO :
// pull-up mode dans les params
// set mode sur plusieurs pin d'un coup
// l'idee c'est de lire la config (mode + pupd) pour le port complet
// et de set la nouvelle conf pour les bits concernés

void gpio_set_af(uint8_t gpio_port, GpioAf afmode, uint8_t pin)
{
    // TODO
}

void gpio_mode_setup(uint8_t reg, GpioMode mode, uint8_t pin)
{
    volatile uint8_t *ddr = (volatile uint8_t *)(uintptr_t)reg;
    volatile uint8_t *port = (volatile uint8_t *)(uintptr_t)(reg + 1);

    switch (mode)
    {
    case GPIO_MODE_DISABLE:
        *ddr &= ~(1 << pin);  // Entrée
        *port &= ~(1 << pin); // Pull-up désactivé
        break;

    case GPIO_MODE_INPUT:
        *ddr &= ~(1 << pin);  // Entrée
        *port &= ~(1 << pin); // Pull-up désactivé
        break;

    case GPIO_MODE_OUTPUT:
        *ddr |= (1 << pin); // Sortie
        break;

    case GPIO_MODE_INPUT_PULLUP:
        *ddr &= ~(1 << pin); // Entrée
        *port |= (1 << pin); // Pull-up activé
        break;

    case GPIO_MODE_AF:
        // TODO
        break;

    default:
        break; // mode inconnu → ne rien faire
    }
}

// active la <pin> du <reg> PORTx
void gpio_set(uint8_t reg, uint8_t pin)
{
    MMIO8(reg) |= (1 << pin);
}

// desactive la <pin> du <reg> PORTx
void gpio_clear(uint8_t reg, uint8_t pin)
{
    MMIO8(reg) &= ~(1 << pin);
}

/*
La lecture d’une broche via PINx passe par un latch de synchronisation
pour éviter des erreurs dues aux changements de signal proches des bords d’horloge,
ce qui introduit un délai de 0.5 à 1.5 cycles d’horloge.
Si on viens d’écrire sur une broche et qu'on veux relire sa valeur immédiatement,
il faut insérer un NOP pour garantir que la lecture reflète bien la dernière écriture.
*/
// retourne la valeur logique de la <pin> du <reg> PINx
uint8_t gpio_get(uint8_t reg, uint8_t pin)
{
    return (MMIO8(reg) & (1 << pin)) ? 1 : 0;
}

// toggle la valeur logique de la <pin> du <reg> PORTx
void gpio_toggle(uint8_t reg, uint8_t pin)
{
    MMIO8(reg) ^= (1 << pin);
}

// retourne un entier de 8 bits où chaque bit représente
// l’état logique des pins du <reg> PINx
uint8_t gpio_pins_read(uint8_t reg)
{
    return MMIO8(reg);
}

// ecrit d'un coup sur toutes les broches du <reg> PORTx
void gpio_port_write(uint8_t reg, uint8_t data)
{
    MMIO8(reg) = data;
}