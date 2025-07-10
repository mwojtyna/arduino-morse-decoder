#ifndef LIB_H
#define LIB_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#define OUTPUT 1
#define INPUT 0

#define WRITE_BIT(reg, num, val)                                               \
    if (val == 0) {                                                            \
        reg &= ~(1 << num);                                                    \
    } else {                                                                   \
        reg |= 1 << num;                                                       \
    }

#define READ_BIT(reg, num) ((reg & (1 << num)) >> num)

// Initalize USART. After initialization you can use normal stdio.h functions to write output over serial.
void usart_init(uint32_t baud_rate, uint64_t cpu_clock);

int roundf_fast(float x);

#endif // LIB_H
