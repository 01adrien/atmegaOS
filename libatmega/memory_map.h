/*
 * memory_map.h
 *
 * Définition des adresses mémoire des registres matériels (IO)
 * pour les périphériques du microcontrôleur (Timers, GPIO, etc.).
 *
 * Ce fichier fournit également la macro MMIO pour un accès type-safe
 * aux registres mémoire-mappés.
 */

#if !defined(_MEMORY_MAP_H_)
#define _MEMORY_MAP_H_

#include <stdint.h>

#define MMIO(addr) (*(volatile uint8_t *)(uintptr_t)(addr))

// Power Reduction Register 0
#define PRR0 (0x64)
#define PRTIM0 (6)

// Timer / Counter 0
#define TIFR0 (0x35)
#define TCCR0A (0x44)
#define TCCR0B (0x45)
#define TCNT0 (0x46)
#define OCROB (0x47)
#define OCROA (0x48)
#define TIMSK0 (0x6E)

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

#endif // _MEMORY_MAP_H_
