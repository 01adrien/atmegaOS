CC := gcc
CFLAGS := -g -I../libatmega -I../kernel -I..

OUT := tests.elf

KERNEL_DIR  := ../kernel

SRC   := $(wildcard $(KERNEL_DIR)/*.c) $(wildcard *.c) 


all: $(OUT)

$(OUT): $(SRC)
	$(CC) $(CFLAGS) $^ -o $@

run: $(OUT)
	./$(OUT)

clean:
	rm -f $(OUT)