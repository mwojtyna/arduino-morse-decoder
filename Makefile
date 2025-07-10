CC=avr-gcc
MCU=atmega328p
CSTD=c23
CFLAGS=-mmcu=$(MCU) -std=$(CSTD) -Wall -pedantic -Os -flto
LFLAGS=-Wl,-u,vfprintf -lprintf_min

SRC_DIR=src
BUILD_DIR=build

# Input files
# Force src/main.c to always be first, otherwise the main function isn't ran by the device
SRC=$(SRC_DIR)/main.c $(filter-out $(SRC_DIR)/main.c, $(wildcard $(SRC_DIR)/*.c))
OBJ=$(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRC))
LIB=$(SRC_DIR)/lib.h

# Output files
ELF=$(BUILD_DIR)/morse.elf
HEX=$(BUILD_DIR)/morse.hex
PORT=/dev/ttyACM0
BAUD=115200

all: $(ELF)

$(ELF): $(OBJ)
	$(CC) $(CFLAGS) $(LFLAGS) $(OBJ) -o $(ELF)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c $(LIB)
	$(CC) $(CFLAGS) $(LFLAGS) -c $< -o $@

upload: $(ELF) size
	avr-objcopy -O ihex $(ELF) $(HEX)
	avrdude -c arduino -p $(MCU) -U flash:w:$(HEX):i -P $(PORT)

listen:
	tio $(PORT) --baudrate $(BAUD)

size: $(ELF)
	avr-size -C --mcu=$(MCU) $(ELF)

clean:
	rm -f $(OBJ) $(ELF) $(HEX)

.PHONY: all upload listen size clean
