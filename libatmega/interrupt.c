#include "interrupt.h"
#include "systick.h"
#include "gpio.h"

// TODO fonction dispatching pour les interrupts

// Interruption externe 0 : déclenchée par un front sur la broche INT0
void __vector_1(void)
{
}

// Interruption externe 1 : déclenchée par un front sur la broche INT1
void __vector_2(void)
{
}

// Interruption externe 2 : déclenchée par un front sur la broche INT2
void __vector_3(void)
{
}

// Pin Change Interrupt Request 0 : changement d’état sur broches du groupe 0
void __vector_4(void)
{
}

// Pin Change Interrupt Request 1 : changement d’état sur broches du groupe 1
void __vector_5(void)
{
}

// Pin Change Interrupt Request 2 : changement d’état sur broches du groupe 2
void __vector_6(void)
{
}

// Pin Change Interrupt Request 3 : changement d’état sur broches du groupe 3
void __vector_7(void)
{
}

// Watchdog Timer Timeout : déclenchée par le watchdog
void __vector_8(void)
{
}

// Timer/Counter2 Compare Match A : correspondance avec OCR2A
void __vector_9(void)
{
}

// Timer/Counter2 Compare Match B : correspondance avec OCR2B
void __vector_10(void)
{
}

// Timer/Counter2 Overflow : dépassement de valeur maximale du timer 2
void __vector_11(void)
{
}

// Timer/Counter1 Capture Event : capture d’un signal sur ICP1
void __vector_12(void)
{
}

// Timer/Counter1 Compare Match A : correspondance avec OCR1A
void __vector_13(void)
{
}

// Timer/Counter1 Compare Match B : correspondance avec OCR1B
void __vector_14(void)
{
}

// Timer/Counter1 Overflow : dépassement de valeur maximale du timer 1
void __vector_15(void)
{
}

// Timer/Counter0 Compare Match A : correspondance avec OCR0A
void __vector_16(void)
{
}

// Timer/Counter0 Compare Match B : correspondance avec OCR0B
void __vector_17(void)
{
}

// Timer/Counter0 Overflow : dépassement de valeur maximale du timer 0
void __vector_18(void)
{
    systick_increment();
}

// SPI Serial Transfer Complete : fin de transmission SPI
void __vector_19(void)
{
}

// USART Rx Complete : réception d’un octet via USART0
void __vector_20(void)
{
}

// USART Data Register Empty : registre prêt à transmettre un octet
void __vector_21(void)
{
}

// USART Tx Complete : transmission complète via USART0
void __vector_22(void)
{
}

// Analog Comparator : déclenché lors du changement de sortie du comparateur
void __vector_23(void)
{
}

// ADC Conversion Complete : conversion analogique-numérique terminée
void __vector_24(void)
{
}

// EEPROM Ready : EEPROM prête pour lecture/écriture
void __vector_25(void)
{
}

// TWI (I2C) Transfer Complete : fin d’une transaction I2C
void __vector_26(void)
{
}

// Store Program Memory Ready : mémoire Flash prête à être écrite
void __vector_27(void)
{
}

// USART1 Rx Complete : réception d’un octet via USART1
void __vector_28(void)
{
}

// USART1 Data Register Empty : USART1 prêt à transmettre un octet
void __vector_29(void)
{
}

// USART1 Tx Complete : transmission complète via USART1
void __vector_30(void)
{
}
