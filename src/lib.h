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

int roundf_fast(float x);

void usart_init(uint32_t baud_rate, uint64_t cpu_clock);
void usart_send(uint8_t data);
void usart_print(const char* s);
void usart_println(const char* s);

#endif // LIB_H
