#include "interrupt.h"
#include "interrupt_handlers.h"
// TODO fonction dispatching pour les interrupts

// __vector_ = reset (pas touche!)

// Interruption externe 0 : déclenchée par un front sur la broche INT0
void __vector_1(void)
{
    null_handler();
}

// Interruption externe 1 : déclenchée par un front sur la broche INT1
void __vector_2(void)
{
    null_handler();
}

// Interruption externe 2 : déclenchée par un front sur la broche INT2
void __vector_3(void)
{
    null_handler();
}

// Pin Change Interrupt Request 0 : changement d’état sur broches du groupe 0
void __vector_4(void)
{
    null_handler();
}

// Pin Change Interrupt Request 1 : changement d’état sur broches du groupe 1
void __vector_5(void)
{
    null_handler();
}

// Pin Change Interrupt Request 2 : changement d’état sur broches du groupe 2
void __vector_6(void)
{
    null_handler();
}

// Pin Change Interrupt Request 3 : changement d’état sur broches du groupe 3
void __vector_7(void)
{
    null_handler();
}

// Watchdog Timer Timeout : déclenchée par le watchdog
void __vector_8(void)
{
    null_handler();
}

// Timer/Counter2 Compare Match A : correspondance avec OCR2A
void __vector_9(void)
{
    timer2_compa_handler();
}

// Timer/Counter2 Compare Match B : correspondance avec OCR2B
void __vector_10(void)
{
    timer2_compb_handler();
}

// Timer/Counter2 Overflow : dépassement de valeur maximale du timer 2
void __vector_11(void)
{
    timer2_ovf_handler();
}

// Timer/Counter1 Capture Event : capture d’un signal sur ICP1
void __vector_12(void)
{
    null_handler();
}

// Timer/Counter1 Compare Match A : correspondance avec OCR1A
void __vector_13(void)
{
    null_handler();
}

// Timer/Counter1 Compare Match B : correspondance avec OCR1B
void __vector_14(void)
{
    null_handler();
}

// Timer/Counter1 Overflow : dépassement de valeur maximale du timer 1
void __vector_15(void)
{
    null_handler();
}

// Timer/Counter0 Compare Match A : correspondance avec OCR0A
void __vector_16(void)
{
    timer0_compa_handler();
}

// Timer/Counter0 Compare Match B : correspondance avec OCR0B
void __vector_17(void)
{
    timer0_compb_handler();
}

// Timer/Counter0 Overflow : dépassement de valeur maximale du timer 0
void __vector_18(void)
{
    timer0_ovf_handler();
}

// SPI Serial Transfer Complete : fin de transmission SPI
void __vector_19(void)
{
    null_handler();
}

// USART Rx Complete : réception d’un octet via USART0
void __vector_20(void)
{
    usart0_rx_handler();
}

// USART Data Register Empty : registre prêt à transmettre un octet
void __vector_21(void)
{
    usart0_udre_handler();
}

// USART Tx Complete : transmission complète via USART0
void __vector_22(void)
{
    usart0_tx_handler();
}

// Analog Comparator : déclenché lors du changement de sortie du comparateur
void __vector_23(void)
{
    null_handler();
}

// ADC Conversion Complete : conversion analogique-numérique terminée
void __vector_24(void)
{
    null_handler();
}

// EEPROM Ready : EEPROM prête pour lecture/écriture
void __vector_25(void)
{
    null_handler();
}

// TWI (I2C) Transfer Complete : fin d’une transaction I2C
void __vector_26(void)
{
    null_handler();
}

// Store Program Memory Ready : mémoire Flash prête à être écrite
void __vector_27(void)
{
    null_handler();
}

// USART1 Rx Complete : réception d’un octet via USART1
void __vector_28(void)
{
    usart1_rx_handler();
}

// USART1 Data Register Empty : USART1 prêt à transmettre un octet
void __vector_29(void)
{
    usart1_udre_handler();
}

// USART1 Tx Complete : transmission complète via USART1
void __vector_30(void)
{
    usart1_tx_handler();
}
