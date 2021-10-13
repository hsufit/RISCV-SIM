CROSS_COMPILE ?= riscv32-unknown-elf-
CC= $(CROSS_COMPILE)gcc
CFLAGS = -Wall -I. -O0 -nostdlib -march=rv32i -mabi=ilp32 --entry main

SRC= test
TARGET= binary

export PATH:=/home/user/Desktop/code/rv32i-ilp32-gnu-toolchain/bin:${PATH}

all: $(addsuffix .o, $(SRC))
	$(CROSS_COMPILE)objcopy -Oihex $< $(TARGET).hex
	readelf -a $<

%.o: %.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	-rm *.o *.hex

