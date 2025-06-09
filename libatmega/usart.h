#if !defined(USART_H)
#define USART_H

#include "memory_map.h"

/*
Le baud rate (ou débit en bauds) est la vitesse à laquelle les bits sont transmis
en communication série, soit le nombre de bits envoyés par seconde.
Il est défini comme l’inverse du temps nécessaire pour transmettre un bit :
baud rate = 1 / temps par bit (en secondes)
Par exemple, si chaque bit prend 0,001 seconde (1 milliseconde), alors le baud rate est :
1 / 0,001 = 1000 bauds

+------------------------------+---------------------------- -------+
|        Mode USART            |     Calcul du UBRRn                |
+------------------------------+------------------------------------+
| Asynchrone (U2X = 0)         | UBRRn = (FCPU / (16 × Baud)) - 1   |
| Asynchrone Double (U2X = 1)  | UBRRn = (FCPU / (8 × Baud)) - 1    |
| Synchrone                    | UBRRn = (FCPU / (2 × Baud)) - 1    |
+------------------------------------+------------------------------+

*/
#define FCPU (16000000UL)

// UCSRxA
#define RXC (7)
#define TXC (6)
#define UDRE (5)
#define U2X (1)

// UCSRxB
#define RXCIE (7)
#define TXCIE (6)
#define UDRIE (5)
#define RXEN (4)
#define TXEN (3)
#define UCSZ2 (2)

// UCSRxC
#define UMSEL1 (7)
#define UMSEL0 (6)
#define UPM1 (5)
#define UPM0 (4)
#define USBS (3)
#define UCSZ1 (2)
#define UCSZ0 (1)

typedef enum
{
    USART0,
    USART1
} UsartId;

typedef enum
{
    USART_MODE_ASYNC,
    USART_MODE_ASYNC_DOUBLE,
    USART_MODE_SYNC,
    USART_MODE_SPI_MASTER
} UsartMode;

typedef struct
{
    volatile uint8_t ucsra;
    volatile uint8_t ucsrb;
    volatile uint8_t ucsrc;
    volatile const uint8_t _reserved;
    volatile uint8_t ubrrl;
    volatile uint8_t ubrrh;
    volatile uint8_t udr;
} Usart;

typedef enum
{
    USART_FORMAT_5N1,
    USART_FORMAT_6N1,
    USART_FORMAT_7N1,
    USART_FORMAT_8N1, // standart 8 data, 0 parity, 1 stop
    USART_FORMAT_7E1,
    USART_FORMAT_8E1,
    USART_FORMAT_7O1,
    USART_FORMAT_8O1,
    USART_FORMAT_8N2,
    USART_FORMAT_9N1, // pas utile ??
} UsartFrameFormat;

void usart_enable_clock(UsartId id);
void usart_set_format(UsartId id, UsartFrameFormat format);
void usart_set_baudrate(UsartId id, uint32_t baudrate);
void usart_set_mode(UsartId id, UsartMode mode);
void usart_enable_interrupt(UsartId id);
void usart_enable_udre_interrupt(UsartId id);
void usart_disable_udre_interrupt(UsartId id);
void usart_enable(UsartId id);
uint8_t usart_read_byte(UsartId id);
void usart_write_byte(UsartId id, uint8_t byte);
uint8_t usart_data_available();

#endif // USART_H
