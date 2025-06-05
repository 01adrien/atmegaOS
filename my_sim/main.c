#include <stdio.h>
#include <assert.h>
#include "sim_avr.h"
#include "sim_elf.h"
#include "sim_gdb.h"
#include "sim_vcd_file.h"
#include "avr_twi.h"
#include "i2c_eeprom.h"
#include "avr_uart.h"
#include "uart_pty.h"
#include <termios.h> // cfmakeraw
#include <pthread.h> // pthread_t, pthread_kill, pthread_create
#include <signal.h>  // SIGINT
#include <unistd.h>  // symlink, close, write, etc.
#include <string.h>  // memset, strerror
#include <stdlib.h>

avr_t *avr = NULL;
avr_vcd_t vcd_file;
i2c_eeprom_t ee;

// picocom /dev/pts/7 --baud 115200 --echo

int main(int argc, char const *argv[])
{
    elf_firmware_t f = {0};
    elf_read_firmware("../firmware.elf", &f);

    puts("Launching simulation...\n");

    avr = avr_make_mcu_by_name("atmega1284p");
    assert(avr != NULL);

    avr_init(avr);
    avr_load_firmware(avr, &f);

    i2c_eeprom_init(avr, &ee, 0xA0, 0xfe, NULL, 1024);
    i2c_eeprom_attach(avr, &ee, AVR_IOCTL_TWI_GETIRQ(0));

    avr->gdb_port = 1234;
    avr->state = cpu_Stopped;
    avr_gdb_init(avr);

    avr_vcd_init(
        avr,
        "gtkwave_output.vcd ",
        &vcd_file,
        100000 /* usec */);

    avr_vcd_add_signal(
        &vcd_file,
        avr_io_getirq(avr, AVR_IOCTL_TWI_GETIRQ(0), TWI_IRQ_STATUS),
        8 /* bits */,
        " TWSR ");

    // Lien vers UART0 → terminal PTY
    uart_pty_t uart;
    uart_pty_init(avr, &uart);
    uart_pty_connect(&uart, '0');

    int state = cpu_Running;
    while ((state != cpu_Done) && (state != cpu_Crashed))
    {
        state = avr_run(avr);
    }

    return 0;
}
