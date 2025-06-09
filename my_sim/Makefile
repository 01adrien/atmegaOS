CC := gcc
CFLAGS := -I../simavr/simavr/sim -I../simavr/examples/parts -Wall -O2 -std=c99
LDFLAGS := ../simavr/simavr/obj-x86_64-linux-gnu/libsimavr.a -lm -lelf -lpthread

SRC := main.c \
	   ../simavr/examples/parts/i2c_eeprom.c \
	   ../simavr/examples/parts/uart_pty.c


OBJ := $(SRC:.c=.o)
TARGET := my_sim

all: $(TARGET)

.PHONY: $(TARGET)

$(TARGET): $(OBJ)
	@$(CC) $(OBJ) -o $@ $(LDFLAGS)

debug:
	@echo "Starting GDB..."
	avr-gdb -nx --nh ../firmware.elf -ex "target remote localhost:1234"

sim: $(TARGET)
	@echo "Launching simulation..."
	./$(TARGET)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJ) $(TARGET)
