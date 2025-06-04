#if !defined(_UART_H_)
#define _UART_H_

#include "memory_map.h"

#endif // _UART_H_

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