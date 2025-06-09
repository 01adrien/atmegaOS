#if !defined(IO_H)
#define IO_H

#include "common.h"

#ifndef _FDEV_SETUP_WRITE
#define _FDEV_SETUP_WRITE 0x02
#endif

#ifndef _FDEV_SETUP_READ
#define _FDEV_SETUP_READ 0x01
#endif

void io_init();
int io_putc(char c, FILE *stream);
int io_getc(FILE *stream);

#endif // IO_H
