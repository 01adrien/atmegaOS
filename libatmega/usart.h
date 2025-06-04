#if !defined(_USART_H_)
#define _USART_H_

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

Exemple avec FCPU = 16 000 000 Hz, Baud = 9600 :
- Mode Asynchrone       → UBRRn = 103   → Baud ≈ 9600
- Mode Double Vitesse   → UBRRn = 207   → Baud ≈ 9600
- Mode Synchrone        → UBRRn = 832   → Baud ≈ 9600
*/
#define BAUD_RATE (9600)
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
#define UCSZ1 (2)
#define UCSZ0 (1)

typedef enum
{
    USART0,
    USART1
} UsartId;

typedef enum
{
    USART_MODE_ASYNC,        // UMSEL = 00, U2X = 0
    USART_MODE_ASYNC_DOUBLE, // UMSEL = 00, U2X = 1
    USART_MODE_SYNC,         // UMSEL = 01
    USART_MODE_SPI_MASTER    // UMSEL = 11 (MSPIM)
} UsartMode;

typedef enum
{
    USART_MODE_TX_RX,
} UsartMode;

typedef enum
{
    USART_DATA_BITS_5 = 0b000,
    USART_DATA_BITS_6 = 0b001,
    USART_DATA_BITS_7 = 0b010,
    USART_DATA_BITS_8 = 0b011,
    USART_DATA_BITS_9 = 0b111
} UsartDataBits;

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

void usart_enable_clock(UsartId id);
void usart_set_databits(UsartId id, UsartDataBits bits);
void usart_set_baudrate(UsartId id, uint32_t baudrate);
void usart_set_mode(UsartId id, UsartMode mode);
void usart_enable_interrupt(UsartId id);
void usart_enable(UsartId id);

#endif // _USART_H_

/*
Exemple : configurer sim-avr pour l’USART
Avec sim-avr, tu peux utiliser l’option -u pour connecter l’USART1 à un pseudo-terminal.
Par exemple, lancer sim-avr avec :
simavr -m atmega328p -f 16000000 -u /dev/pts/3 your_program.elf
Cela redirige l’USART vers /dev/pts/3 (un pseudo-terminal).
Comment trouver ou créer ce port ?
    Tu peux créer une paire de pseudo-terminaux avec socat :
    socat -d -d PTY,raw,echo=0 PTY,raw,echo=0
Cette commande affiche deux ports virtuels, par exemple /dev/pts/3 et /dev/pts/4.
    Tu passes un des deux à sim-avr en -u (USART), et tu connectes l’autre avec screen ou un autre terminal.
Résumé
    /dev/ttyUSB0 est juste un exemple d’un port série physique ou virtuel sur ton PC.
    Avec sim-avr, tu peux simuler un port série virtuel (pseudo-terminal) vers lequel rediriger l’USART.
    Ensuite, tu ouvres ce port avec screen ou autre pour communiquer.
*/