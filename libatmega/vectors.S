.section .vectors, "ax", @progbits
.global __vectors

__vectors:
    rjmp reset            ; 0x0000 Reset
    rjmp int0             ; 0x0002 External Interrupt Request 0
    rjmp int1             ; 0x0004 External Interrupt Request 1
    rjmp int2             ; 0x0006 External Interrupt Request 2
    rjmp pcint0           ; 0x0008 Pin Change Interrupt Request 0
    rjmp pcint1           ; 0x000A Pin Change Interrupt Request 1
    rjmp pcint2           ; 0x000C Pin Change Interrupt Request 2
    rjmp pcint3           ; 0x000E Pin Change Interrupt Request 3
    rjmp wdt              ; 0x0010 Watchdog Time-out Interrupt
    rjmp timer2_compa     ; 0x0012 Timer/Counter2 Compare Match A
    rjmp timer2_compb     ; 0x0014 Timer/Counter2 Compare Match B
    rjmp timer2_ovf       ; 0x0016 Timer/Counter2 Overflow
    rjmp timer1_capt      ; 0x0018 Timer/Counter1 Capture Event
    rjmp timer1_compa     ; 0x001A Timer/Counter1 Compare Match A
    rjmp timer1_compb     ; 0x001C Timer/Counter1 Compare Match B
    rjmp timer1_ovf       ; 0x001E Timer/Counter1 Overflow
    rjmp timer0_compa     ; 0x0020 Timer/Counter0 Compare Match A
    rjmp timer0_compb     ; 0x0022 Timer/Counter0 Compare Match B
    rjmp timer0_ovf       ; 0x0024 Timer/Counter0 Overflow
    rjmp spi_stc          ; 0x0026 SPI Serial Transfer Complete
    rjmp usart_rx         ; 0x0028 USART Rx Complete
    rjmp usart_udre       ; 0x002A USART Data Register Empty
    rjmp usart_tx         ; 0x002C USART Tx Complete
    rjmp analog_comp      ; 0x002E Analog Comparator
    rjmp adc              ; 0x0030 ADC Conversion Complete
    rjmp ee_ready         ; 0x0032 EEPROM Ready
    rjmp twi              ; 0x0034 TWI Transfer Complete
    rjmp spm_ready        ; 0x0036 Store Program Memory Ready
    rjmp usart1_rx        ; 0x0038 USART1 Rx Complete
    rjmp usart1_udre      ; 0x003A USART1 Data Register Empty
    rjmp usart1_tx        ; 0x003C USART1 Tx Complete
