#ifndef IO_H
#define IO_H

// Don't change the name, this is a configuration define for util/delay.h
#define F_CPU 16000000UL
#define BAUD 115200

#include <stdint.h>

#define OUTPUT 1
#define INPUT 0

#define WRITE_BIT(reg, num, val)                                                                   \
    if (val == 0) {                                                                                \
        reg &= ~(1 << num);                                                                        \
    } else {                                                                                       \
        reg |= 1 << num;                                                                           \
    }

#define READ_BIT(reg, num) ((reg & (1 << num)) >> num)

// Initalize USART. After initialization you can use normal stdio.h functions to write output over serial.
void usart_init();

typedef uint32_t time;

// Initializes timer to measure each ms elapsed
void timer_init();
// Returns ms elapsed from start of program
time timer_ms();

#endif
