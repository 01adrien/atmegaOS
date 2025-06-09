#if !defined(MEMORY_MAP_H)
#define MEMORY_MAP_H

#include <stdint.h>
#include <stddef.h>
/*
memory_map.h

Définition des adresses mémoire des registres matériels (IO)
pour les périphériques du microcontrôleur (Timers, GPIO, etc.).

Ce fichier fournit également la macro MMIO8 et MMIO16 pour un accès type-safe
aux registres mémoire-mappés.

La mémoire mappée (Memory-Mapped I/O) est une technique où les périphériques
sont accessibles via des adresses mémoire normales.
Le processeur lit et écrit ces adresses comme de la mémoire,
mais les données sont interprétées comme des commandes ou
des informations spécifiques aux périphériques.
*/

/*
La macro MMIOX(addr) retourne une lvalue (référence mémoire modifiable)
pointant vers l’adresse addr. Cela permet de lire ou modifier directement
un registre matériel comme une variable classique.
*/
#define MMIO8(addr) (*(volatile uint8_t *)(uintptr_t)(addr))
#define MMIO16(addr) (*(volatile uint16_t *)(uintptr_t)(addr))

// Power Reduction Register 0
#define PRR0 (0x64)
#define PRTIM2 (6)
#define PRTIM0 (5)
#define PRUSART1 (4)
#define PRUSART0 (1)

// Timer / Counter 0
#define TIFR0 (0x35)
#define TCCR0A (0x44)
#define TCCR0B (0x45)
#define TCNT0 (0x46)
#define OCR0A (0x47)
#define OCR0B (0x48)
#define TIMSK0 (0x6E)

// Timer / Counter 2
#define TIFR2 (0x37)
#define TCCR2A (0xB0)
#define TCCR2B (0xB1)
#define TCNT2 (0xB2)
#define OCR2A (0xB3)
#define OCR2B (0xB4)
#define TIMSK2 (0x70)

// GPIO
#define PINA (0x20)
#define DDRA (0x21)
#define PORTA (0x22)
#define PINB (0x23)
#define DDRB (0x24)
#define PORTB (0x25)
#define PINC (0x26)
#define DDRC (0x27)
#define PORTC (0x28)
#define PIND (0x29)
#define DDRD (0x2A)
#define PORTD (0x2B)

// Status Register
#define SREG (0x5f)
#define I (7)

// USART 0
#define USART0_BASE (0xC0)

// USART 1
#define USART1_BASE (0xC8)

#endif // MEMORY_MAP_H
