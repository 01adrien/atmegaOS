#if !defined(_GPIO_H_)
#define _GPIO_H_

#include "memory_map.h"
/*
Registres de contrôle des périphériques GPIO (8 bits)

Chaque bit d’un registre contrôle une broche de b0 à b7, en partant du LSB.

* PINx (read) :
    - Permet de lire l’état logique des broches (lecture uniquement).
* DDRx :
    - Définit la direction des broches (1 = sortie, 0 = entrée).
* PORTx (write) :
    - Si la broche est en sortie (DDRx = 1) : écrit une valeur logique (0 ou 1) sur la broche.
    - Si la broche est en entrée (DDRx = 0) : active (1) ou désactive (0) la résistance de pull-up interne

volatile informe le compilateur que la valeur du registre peut changer à tout moment (ex. via le matériel),
empêchant toute optimisation qui ignorerait ou réorganiserait les accès mémoire.
*/

typedef enum
{
    GPIO_MODE_DISABLE = 0,
    GPIO_MODE_INPUT,
    GPIO_MODE_OUTPUT,
    GPIO_MODE_INPUT_PULLUP,
    GPIO_MODE_AF,
} GpioMode;

typedef enum
{
    GPIO_PUPD_ENABLE = 0,
    GPIO_PUPD_DISABLE,
} GpioPupd;

void gpio_mode_setup(uint8_t gpio_port, GpioMode mode, uint8_t pin);
void gpio_set(uint8_t gpio_port, uint8_t pin);
void gpio_clear(uint8_t gpio_port, uint8_t pin);
uint8_t gpio_get(uint8_t gpio_port, uint8_t pin);
void gpio_toggle(uint8_t gpio_port, uint8_t pin);
uint8_t gpio_pins_read(uint8_t gpio_port);
void gpio_port_write(uint8_t gpio_port, uint8_t data);

#endif // _GPIO_H_
