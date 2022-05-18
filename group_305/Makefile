# File:   Makefile
# Author: Rohan Mathias. Zhenyuan He
# Date:   20 Oct 2021
# Descr:  Makefile for game

# Definitions.
CC = avr-gcc
CFLAGS = -mmcu=atmega32u2 -Os -Wall -Wstrict-prototypes -Wextra -g -I. -I../../utils -I../../fonts -I../../drivers -I../../drivers/avr
OBJCOPY = avr-objcopy
SIZE = avr-size
DEL = rm


# Default target.
all: game.out


# Compile: create object files from C source files.
game.o: game.c player.h map.h ../../drivers/avr/system.h ../../drivers/navswitch.h ../../utils/tinygl.h ../../utils/pacer.h ../../drivers/avr/pio.h ../../drivers/ledmat.h 
	$(CC) -c $(CFLAGS) $< -o $@

pacer.o: ../../utils/pacer.c ../../drivers/avr/system.h ../../utils/pacer.h ../../drivers/avr/timer.h
	$(CC) -c $(CFLAGS) $< -o $@

tinygl.o: ../../utils/tinygl.c ../../drivers/avr/system.h ../../utils/tinygl.h ../../drivers/display.h ../../utils/font.h
	$(CC) -c $(CFLAGS) $< -o $@

navswitch.o: ../../drivers/navswitch.c ../../drivers/avr/system.h ../../drivers/navswitch.h ../../drivers/avr/delay.h ../../drivers/avr/pio.h
	$(CC) -c $(CFLAGS) $< -o $@

system.o: ../../drivers/avr/system.c ../../drivers/avr/system.h
	$(CC) -c $(CFLAGS) $< -o $@

timer.o: ../../drivers/avr/timer.c ../../drivers/avr/timer.h ../../drivers/avr/system.h
	$(CC) -c $(CFLAGS) $< -o $@

pio.o: ../../drivers/avr/pio.c ../../drivers/avr/pio.h ../../drivers/avr/system.h
	$(CC) -c $(CFLAGS) $< -o $@

display.o: ../../drivers/display.c ../../drivers/display.h ../../drivers/avr/system.h ../../drivers/led.h
	$(CC) -c $(CFLAGS) $< -o $@

ledmat.o: ../../drivers/ledmat.c ../../drivers/ledmat.h ../../drivers/avr/system.h ../../drivers/avr/pio.h
	$(CC) -c $(CFLAGS) $< -o $@

font.o: ../../utils/font.c ../../drivers/avr/system.h ../../utils/font.h
	$(CC) -c $(CFLAGS) $< -o $@ 

player.o: player.c player.h ../../drivers/avr/system.h ../../drivers/navswitch.h ../../utils/tinygl.h
	$(CC) -c $(CFLAGS) $< -o $@ 

map.o: map.c map.h ../../drivers/avr/system.h ../../drivers/ledmat.h ../../drivers/avr/pio.h ../../utils/pacer.h
	$(CC) -c $(CFLAGS) $< -o $@ 

# Link: create ELF output file from object files.
game.out: game.o pacer.o tinygl.o navswitch.o system.o pio.o display.o timer.o ledmat.o font.o player.o map.o
	$(CC) $(CFLAGS) $^ -o $@ -lm
	$(SIZE) $@


# Target: clean project.
.PHONY: clean
clean: 
	-$(DEL) *.o *.out *.hex


# Target: program project.
.PHONY: program
program: game.out
	$(OBJCOPY) -O ihex game.out game.hex
	dfu-programmer atmega32u2 erase; dfu-programmer atmega32u2 flash game.hex; dfu-programmer atmega32u2 start


