CC=avr-gcc
MCU=atmega328p
CSTD=c23
CFLAGS=-mmcu=$(MCU) -std=$(CSTD) -Wall -pedantic -Os -flto
# Light-weight implementation of printf
LFLAGS=-Wl,-u,vfprintf -lprintf_min

SRCS_DIR=src
BUILD_DIR=build

# Input files
SRCS=$(wildcard $(SRCS_DIR)/*.c)
OBJS=$(patsubst $(SRCS_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRCS))
HEADERS=$(wildcard $(SRCS_DIR)/*.h)

# Output files
ELF=$(BUILD_DIR)/morse.elf
HEX=$(BUILD_DIR)/morse.hex
PORT=/dev/ttyACM0
BAUD=115200

all: $(ELF)

# Linking
$(ELF): $(OBJS)
	$(CC) $(CFLAGS) $(LFLAGS) $(OBJS) -o $(ELF)

# Compiling
$(BUILD_DIR)/%.o: $(SRCS_DIR)/%.c $(HEADERS)
	$(CC) $(CFLAGS) $(LFLAGS) -c $< -o $@

upload: $(ELF) size
	avr-objcopy -O ihex $(ELF) $(HEX)
	avrdude -c arduino -p $(MCU) -U flash:w:$(HEX):i -P $(PORT)

listen:
	tio $(PORT) --baudrate $(BAUD)

size: $(ELF)
	avr-size -C --mcu=$(MCU) $(ELF)

clean:
	rm -f $(OBJS) $(ELF) $(HEX)

.PHONY: all upload listen size clean
