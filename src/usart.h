#ifndef USART_H
#define USART_H

#include <stdint.h>

// Initalize USART. After initialization you can use normal stdio.h functions to write output over serial.
void usart_init(uint32_t baud_rate, uint64_t cpu_clock);

#endif
