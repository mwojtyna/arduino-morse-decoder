#include "io.h"
#include "math.h"
#include <avr/io.h>
#include <stdint.h>
#include <stdio.h>

static int usart_putchar(char data, FILE* stream) {
    // Wait until buffer is empty
    while (READ_BIT(UCSR0A, UDRE0) == 0) {
    }
    UDR0 = data;
    return 0;
}

static FILE mystdout =
    FDEV_SETUP_STREAM(usart_putchar, NULL, _FDEV_SETUP_WRITE);

void usart_init(uint32_t baud_rate, uint64_t cpu_clock) {
    stdout = &mystdout;

    // Table 19-1, ATmega328P data sheet
    const uint16_t UBRR =
        roundf_fast((cpu_clock / (16 * (float)baud_rate)) - 1);
    UBRR0H = (uint8_t)(UBRR >> 8); // 4 most significant bits
    UBRR0L = (uint8_t)UBRR;        // 8 least significant bits

    WRITE_BIT(UCSR0A, U2X0, 0); // Don't double USART transmission speed

    WRITE_BIT(UCSR0B, RXEN0, 1);  // Enable receiver
    WRITE_BIT(UCSR0B, TXEN0, 1);  // Enable transmitter
    WRITE_BIT(UCSR0B, UCSZ02, 0); // 8-bit character size

    // clang-format off
    UCSR0C = (0 << UMSEL01) | (0 << UMSEL00) |    // Set asynchronous mode
             (0 << UPM01) | (0 << UPM00) |        // Disable parity
             (0 << USBS0) |                       // 1-bit stop bit
             (1 << UCSZ01) | (1 << UCSZ00) |      // 8-bit character size
             (0 << UCPOL0);                       // clock polarity = 0 because asynchronous mode
    // clang-format on
}
