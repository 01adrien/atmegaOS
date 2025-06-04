#include "usart.h"

void usart0_rx_handler(void) {}
void usart0_udre_handler(void) {}
void usart0_tx_handler(void) {}
void usart1_rx_handler(void) {}
void usart1_udre_handler(void) {}
void usart1_tx_handler(void) {}

static Usart *usarts[] = {
    [USART0] = (Usart *)USART0_BASE,
    [USART1] = (Usart *)USART1_BASE,
};

void usart_enable_clock(UsartId id)
{
    switch (id)
    {
    case USART0:
        MMIO8(PRR0) &= ~(1 << PRUSART0);
        break;
    case USART1:
        MMIO8(PRR0) &= ~(1 << PRUSART1);
        break;
    default:
        break;
    }
}

void usart_set_databits(UsartId id, UsartDataBits bits)
{
    Usart *u = usarts[id];

    // reset data bits
    u->ucsrb &= ~(1 << UCSZ2);
    u->ucsrc &= ~((1 << UCSZ1) | (1 << UCSZ0));

    if (bits & (1 << 2))
        u->ucsrb |= (1 << UCSZ2);
    if (bits & (1 << 1))
        u->ucsrc |= (1 << UCSZ1);
    if (bits & (1 << 0))
        u->ucsrc |= (1 << UCSZ0);
}

void usart_set_baudrate(UsartId id, uint32_t baudrate)
{
    Usart *u = usarts[id];
    uint16_t ubrr_value = 0;

    // Vérifier si double vitesse (U2X) est activé
    uint8_t double_speed = (u->ucsra & (1 << U2X)) ? 1 : 0;

    if (u->ucsrc & ((1 << UMSEL0) | (1 << UMSEL1)))
    {
        // Mode synchrone maître
        ubrr_value = (FCPU / (2UL * baudrate)) - 1;
    }
    else
    {
        // Mode asynchrone
        if (double_speed)
            ubrr_value = (FCPU / (8UL * baudrate)) - 1;
        else
            ubrr_value = (FCPU / (16UL * baudrate)) - 1;
    }

    // Écriture des bits UBRR (16 bits = UBRRH + UBRRL)
    u->ubrrh = (uint8_t)(ubrr_value >> 8);
    u->ubrrl = (uint8_t)(ubrr_value & 0xFF);
}

void usart_set_mode(UsartId id, UsartMode mode)
{
    Usart *u = usarts[id];
    // reset mode
    u->ucsrc &= ~((1 << UMSEL0) | (1 << UMSEL1));
    u->ucsra &= ~(1 << U2X);
    switch (mode)
    {
    case USART_MODE_ASYNC:
        break;
    case USART_MODE_ASYNC_DOUBLE:
        u->ucsra |= (1 << U2X);
        break;
    case USART_MODE_SYNC:
        u->ucsrc |= (1 << UMSEL0);
        break;
    case USART_MODE_SPI_MASTER:
        u->ucsrc |= ((1 << UMSEL0) | (1 << UMSEL1));
        break;
    default:
        break;
    }
}

void usart_enable_interrupt(UsartId id)
{
    Usart *u = usarts[id];
    u->ucsrb |= ((1 << RXCIE) | (1 << TXCIE) | (1 << UDRIE));
}

void usart_enable(UsartId id)
{
    Usart *usart = usarts[id];
    usart->ucsrb |= ((1 << RXEN) | (1 << TXEN));
}

uint8_t usart_read(UsartId id, uint8_t *data)
{
    // utiliser UDRx
}

void usart_write(UsartId id, uint8_t data)
{
    // utiliser UDRx
}
