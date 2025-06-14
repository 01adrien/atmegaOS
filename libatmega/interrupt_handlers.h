#ifndef INTERRUPT_HANDLERS_H
#define INTERRUPT_HANDLERS_H

static inline void blocking_handler(void)
{
    while (1)
        ;
}

static inline void null_handler(void)
{
    __asm__("nop");
}

// TIMER0
__attribute__((weak)) void timer0_ovf_handler(void) { null_handler(); }
__attribute__((weak)) void timer0_compa_handler(void) { null_handler(); }
__attribute__((weak)) void timer0_compb_handler(void) { null_handler(); }

// TIMER2
__attribute__((weak)) void timer2_ovf_handler(void) { null_handler(); }
__attribute__((weak)) void timer2_compa_handler(void) { null_handler(); }
__attribute__((weak)) void timer2_compb_handler(void) { null_handler(); }

// USART0
__attribute__((weak)) void usart0_rx_handler(void) { null_handler(); }
__attribute__((weak)) void usart0_udre_handler(void) { null_handler(); }
__attribute__((weak)) void usart0_tx_handler(void) { null_handler(); }

// USART1
__attribute__((weak)) void usart1_rx_handler(void) { null_handler(); }
__attribute__((weak)) void usart1_udre_handler(void) { null_handler(); }
__attribute__((weak)) void usart1_tx_handler(void) { null_handler(); }

#endif // INTERRUPT_HANDLERS_H