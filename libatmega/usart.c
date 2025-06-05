#include "usart.h"
#include "interrupt.h"
/*
USART_RX_vect (RX Complete Interrupt Flag – RXC):
Déclenchée dès qu’un octet est reçu dans le registre UDRn. Le matériel a déjà transféré
l’octet reçu dans UDRn et mis à 1 le bit RXCn dans UCSRnA.

USART_UDRE_vect (Data Register Empty Interrupt Flag – UDRE):
Déclenchée quand le buffer d’émission (UDRn) est vide et prêt à recevoir un nouveau octet.
Le bit UDREn dans UCSRnA passe à 1 dès qu’on a vidé UDRn vers le décalage d’émission.

USART_TX_vect (Transmission Complete Interrupt Flag – TXC):
Déclenchée quand la transmission du dernier bit d’un octet vient de se terminer
(tous les bits ont été envoyés sur la ligne). Le bit TXCn dans UCSRnA passe à 1.

Dans les fonctions usart_read et usart_write
On désactive les interruptions pour éviter qu'une ISR modifie rx_byte ou rx_ready
pendant qu'on les lit ou qu'on les modifie ici.
Exemple : si une interruption RX survient juste après qu'on ait lu rx_ready,
rx_byte pourrait être remplacé avant qu'on l'utilise → bug.
On réactive les interruptions juste après la lecture sécurisée.
TODO Le buffer circulaire regle le probleme
*/

static Usart *usarts[] = {
    [USART0] = (Usart *)USART0_BASE,
    [USART1] = (Usart *)USART1_BASE,
};

static volatile uint8_t rx_byte;  // buffer de réception (1 octet)
static volatile uint8_t rx_ready; // drapeau = 1 si rx_byte contient un octet non lu

static volatile uint8_t tx_byte; // buffer d’émission (1 octet)
static volatile uint8_t tx_busy; // drapeau = 1 si un envoi est en cours

void usart0_rx_handler(void)
{
    // check pour erreur
    uint8_t data = usarts[USART0]->udr; // lit UDR0 → efface RXC0
    rx_byte = data;
    rx_ready = 1;
}
void usart0_udre_handler(void)
{
    Usart *u = usarts[USART0];
    u->udr = tx_byte;
    usart_disable_udre_interrupt(USART0);
    tx_busy = 0;
}

void usart1_rx_handler(void) {}
void usart1_udre_handler(void) {}

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

void usart_set_format(UsartId id, UsartFrameFormat format)
{
    Usart *u = usarts[id];

    // Reset config
    u->ucsrb &= ~(1 << UCSZ2);
    u->ucsrc &= ~((1 << UCSZ1) | (1 << UCSZ0) | (1 << UPM1) | (1 << UPM0) | (1 << USBS));

    switch (format)
    {
    case USART_FORMAT_5N1:
        break;
    case USART_FORMAT_6N1:
        u->ucsrc |= (1 << UCSZ0);
        break;
    case USART_FORMAT_7N1:
        u->ucsrc |= (1 << UCSZ1);
        break;
    case USART_FORMAT_8N1:
        u->ucsrc |= (1 << UCSZ1) | (1 << UCSZ0);
        break;
    case USART_FORMAT_9N1:
        u->ucsrb |= (1 << UCSZ2);
        u->ucsrc |= (1 << UCSZ1) | (1 << UCSZ0);
        break;
    case USART_FORMAT_7E1:
        u->ucsrc |= (1 << UCSZ1);
        u->ucsrc |= (1 << UPM1);
        break;
    case USART_FORMAT_8E1:
        u->ucsrc |= (1 << UCSZ1) | (1 << UCSZ0);
        u->ucsrc |= (1 << UPM1);
        break;
    case USART_FORMAT_7O1:
        u->ucsrc |= (1 << UCSZ1);
        u->ucsrc |= (1 << UPM1) | (1 << UPM0);
        break;
    case USART_FORMAT_8O1:
        u->ucsrc |= (1 << UCSZ1) | (1 << UCSZ0);
        u->ucsrc |= (1 << UPM1) | (1 << UPM0);
        break;
    case USART_FORMAT_8N2:
        u->ucsrc |= (1 << UCSZ1) | (1 << UCSZ0);
        u->ucsrc |= (1 << USBS);
        break;
    default:
        break;
    }
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

void usart_enable_udre_interrupt(UsartId id)
{
    Usart *u = usarts[id];
    u->ucsrb |= (1 << UDRIE);
}

void usart_disable_udre_interrupt(UsartId id)
{
    Usart *u = usarts[id];
    u->ucsrb &= ~(1 << UDRIE);
}

void usart_enable(UsartId id)
{
    // Le CPU configure automatiquement les pins GPIO pour les fonctions alternatives
    Usart *usart = usarts[id];
    usart->ucsrb |= ((1 << RXEN) | (1 << TXEN));
}

uint8_t usart_read_byte(UsartId id)
{
    Usart *u = usarts[id];
    if (!rx_ready)
        return 0;
    interrupt_disable();
    uint8_t data = rx_byte;
    rx_ready = 0;
    interrupt_enable();
    return data;
}

void usart_write_byte(UsartId id, uint8_t data)
{
    while (tx_busy)
        __asm__("nop");
    interrupt_disable();
    tx_byte = data;
    tx_busy = 1;
    usart_enable_udre_interrupt(id);
    interrupt_enable();
}

uint8_t usart_data_available()
{
    return rx_ready;
}