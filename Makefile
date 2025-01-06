CC=avr-gcc
MMCU=atmega328p
CSTD=c23
CFLAGS=-mmcu=$(MMCU) -std=$(CSTD) -Wall -pedantic -O1

SRC_DIR=src
BUILD_DIR=build

SRC=$(wildcard $(SRC_DIR)/*.c)
OBJ=$(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRC))

ELF=$(BUILD_DIR)/morse.elf
HEX=$(BUILD_DIR)/morse.hex
PORT=/dev/ttyACM0

all: $(ELF)

$(ELF): $(OBJ)
	$(CC) $(OBJ) -o $(ELF)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

upload: $(ELF)
	avr-objcopy -O ihex $(ELF) $(HEX)
	avrdude -c arduino -p $(MMCU) -U flash:w:$(HEX):i -P $(PORT)

clean:
	rm -f $(OBJ) $(ELF) $(HEX)

.PHONY: all upload clean
