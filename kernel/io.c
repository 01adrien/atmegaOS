#include "io.h"
#include "libatmega/usart.h"

static FILE usart_output;
static FILE usart_input;

void io_init(void)
{
    fdev_setup_stream(&usart_output, io_putc, NULL, _FDEV_SETUP_WRITE);
    stdout = &usart_output;

    fdev_setup_stream(&usart_input, NULL, io_getc, _FDEV_SETUP_READ);
    stdin = &usart_input;
}

int io_putc(char c, FILE *stream)
{
    usart_write_byte(USART0, c);
    return 0;
}

int io_getc(FILE *stream)
{
    while (!usart_data_available())
        ;
    return usart_read_byte(USART0);
}